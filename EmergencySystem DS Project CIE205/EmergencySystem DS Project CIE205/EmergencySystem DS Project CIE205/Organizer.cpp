#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include "Organizer.h"
#include "Hospital.h"
#include "Car.h"
#include "Request.h"
#include <vector>


//<<<<<<< Updated upstream




Organizer::Organizer() {
    // Initialize 
    for (int i = 0; i < Max_Hospitals_Number; i++) {
        Hospitals[i] = nullptr;
    }
    // FileLoad();
    speed = new Speed();
    numRequests = 0;
    numHospitals = 0;
    //ui = new UI(Interactive, this);
}

void Organizer::HandleEPBonus(int i, Request* temp, int pri) {
   
    int originalDistance = temp->getDistance(); // to know the distance between the patient and its first assigned hospital
    int smallestEPQ = Hospitals[i]->GetEP().getSize(); // to get the least Emergency requests length
    int smallestEPQHospitaldID = 1; // search for the hospitalID with the least number of emergency requests
    int countHospitals = 0; // count the hospitals that has the same number of emergency requests (least number)
    int smallestDistance = distanceMatrix[i][0];
    for (int j = 0; j < numHospitals - 1; j++) {
        if (Hospitals[j]->GetEP().getSize() >= Hospitals[j + 1]->GetEP().getSize()) {
            smallestEPQ = Hospitals[j + 1]->GetEP().getSize();
            smallestEPQHospitaldID = j + 1;

        }
    }
    for (int j = 0; j < numHospitals; j++) {
        if (Hospitals[j]->getHospitalID() == Hospitals[i]->getHospitalID()) continue;
        if (Hospitals[i]->GetEP().getSize() == smallestEPQ)
            countHospitals++;
    }
    if (countHospitals > 1) {
        for (int j = 0; j < numHospitals; j++) {
            if (Hospitals[j]->getHospitalID() == Hospitals[i]->getHospitalID()) continue; // to avoid comparing the hospital by itself
            else if(smallestDistance > distanceMatrix[i][j]) { // second condition because the distance betw
                smallestDistance = distanceMatrix[i][j];
                smallestEPQHospitaldID = j;
            }
        }
        Hospitals[smallestEPQHospitaldID - 1]->GetEP().enqueue(temp, pri);
    }
    else if (countHospitals == 1) {
        Hospitals[smallestEPQHospitaldID]->GetEP().enqueue(temp, pri);
        int distance = distanceMatrix[i][smallestEPQHospitaldID];
        temp->setRequestDistance(distance + temp->getDistance());

    }
}


Hospital*& Organizer::GetHospital(int id) {
    return Hospitals[id];
}


void Organizer::AssignEP(Car* car, int HospitalId)
{
    Request* temp;
    int pri;
    int timepri;
    int pickuptime;
    Hospitals[HospitalId]->GetEP().dequeue(temp, pri);
    car->assignRequest(temp);
    timepri = timestep + 2 * (temp->getDistance() / car->getCarSpeed());  // reach time 
    pickuptime = timestep + (temp->getDistance() / car->getCarSpeed());
    temp->setfinishtime(timepri);
    temp->setpickupTime(pickuptime);
    temp->setwaiting(pickuptime - temp->getRequestTime());
    car->setFinishTime(timepri);
    car->setpickuptime(pickuptime);

}
void Organizer::AssignSP(Car* car, int HospitalId)
{
    Request* temp;
    int timepri;
    int pickuptime;
    Hospitals[HospitalId]->GetSP().dequeue(temp);
    car->assignRequest(temp);
    timepri = timestep + 2 * (temp->getDistance() / car->getCarSpeed());  // reach time 
    pickuptime = timestep + (temp->getDistance() / car->getCarSpeed());
    temp->setfinishtime(timepri);
    temp->setpickupTime(pickuptime);
    temp->setwaiting(pickuptime - temp->getRequestTime());
    car->setFinishTime(timepri);
    car->setpickuptime(pickuptime);
}
void Organizer::AssignNP(Car* car, int HospitalId)
{
    Request* temp;
    int timepri;
    int pickuptime;
    Hospitals[HospitalId]->GetNP().dequeue(temp);
    car->assignRequest(temp);
    timepri = timestep + 2 * (temp->getDistance() / car->getCarSpeed());  // reach time 
    pickuptime = timestep + (temp->getDistance() / car->getCarSpeed());
    temp->setfinishtime(timepri);
    temp->setpickupTime(pickuptime);
    temp->setwaiting(pickuptime - temp->getRequestTime());
    car->setFinishTime(timepri);
    car->setpickuptime(pickuptime);

}

void Organizer::FreeToOut()

{
    Request* temp;
    int pri;
    Car* tempcar;
    //int timepri;
    int pickuptime;
   
    for (int i = 0; i < numHospitals; i++) 
    {
        // handle the emergency requests 
        while (!Hospitals[i]->GetEP().isEmpty() && Hospitals[i]->GetEP().peek(temp, pri) && temp->getRequestTime() <= timestep)
        {
            
            if (!Hospitals[i]->GetNormalCars().isEmpty()) // if the hospital has normal cars
            {
                Hospitals[i]->GetNormalCars().dequeue(tempcar);
                AssignEP(tempcar, i);
                pickuptime = tempcar->getpickuptime();
                outCars.enqueue(tempcar, -1 * pickuptime);


            }

            else if (!Hospitals[i]->GetSpecialCars().isEmpty()) // if it hasn't normal cars, but has special cars
            {
                Hospitals[i]->GetSpecialCars().dequeue(tempcar);
                AssignEP(tempcar, i);
                pickuptime = tempcar->getpickuptime();
                outCars.enqueue(tempcar, -1 * pickuptime);

            }

            else {

                Hospitals[i]->GetEP().dequeue(temp, pri);
                HandleEPBonus(i, temp, pri);
            }
            
        }
        // handle special requests 
        while (!Hospitals[i]->GetSP().isEmpty() && Hospitals[i]->GetSP().peek(temp) && temp->getRequestTime() <= timestep)
        {
            if (!Hospitals[i]->GetSpecialCars().isEmpty())
            {
                Hospitals[i]->GetSpecialCars().dequeue(tempcar);
                AssignSP(tempcar, i);
                pickuptime = tempcar->getpickuptime();
                outCars.enqueue(tempcar, -1 * pickuptime);

            }
            else {
                break;
            }
        }

        // handle normal cars 
        while (!Hospitals[i]->GetNP().isEmpty() && Hospitals[i]->GetNP().peek(temp) && temp->getRequestTime() <= timestep)
        {

            

                if (!Hospitals[i]->GetNormalCars().isEmpty())
                {
                    Hospitals[i]->GetNormalCars().dequeue(tempcar);
                    AssignNP(tempcar, i);
                    pickuptime = tempcar->getpickuptime();
                    outCars.enqueue(tempcar, -1 * pickuptime);

                }
                else {
                    break;
                }    
        }

    }
   
}

void Organizer::OutToBack()
{
    Car* tempcar;
    int pri; // this should store the pickUp time
    int newPri; // this should store the finish time
    while (!outCars.isEmpty() && outCars.peek(tempcar, pri) && tempcar->getpickuptime() == timestep)
    {
        outCars.dequeue(tempcar, pri);
        newPri = tempcar->getFinishTime();
        backCars.enqueue(tempcar, -1 * newPri);
    }

}

void Organizer::BackToFree()
{
    Car* tempcar;
    int pri;
    int relatedHospitalID;
    Request* patient;
    while (!backCars.isEmpty() && backCars.peek(tempcar, pri) && tempcar->getFinishTime() == timestep) 
    {
         backCars.dequeue(tempcar,pri);
         patient = tempcar->GetAssignedRequest();
         AddPatientToFinishList(patient);
         relatedHospitalID = tempcar->getRelatedHospitalID();
         Hospitals[relatedHospitalID - 1]->addCar(tempcar);
    }
}

void Organizer::AddPatientToFinishList(Request* patient)
{
    if (patient->getRequestType() != Cancelled) { // Don't add any cancelled request to the finish list.
        FinishedRequestd.enqueue(patient);
        NumFinish++;
    }
}

Car* Organizer::findCar(Request* request) {
    Car* car;
    int pri;
    int count = 0;
    LinkedQueue<Car*> ClonedQ1;
    CancelationQueue<Car*> ClonedQ2 = outCars;
    while (ClonedQ2.dequeue(car, pri)) ClonedQ1.enqueue(car);
    if (request) {
        while (ClonedQ1.dequeue(car)) {
            
            if (car->GetAssignedRequest()->getID() == request->getID())
                return car;
            else {
                ClonedQ1.enqueue(car);
                count++;
            }
            if (count == outCars.getSize()) return nullptr;
        }
    }
}

void Organizer::cancelRequest(Request* request) {
    Car* assignedCar = findCar(request);
    if (assignedCar == nullptr || assignedCar->getpickuptime() <= timestep) return;
    int assignmentTime = assignedCar->GetAssignedRequest()->getRequestTime();
    int carSpeed = assignedCar->getCarSpeed();
    int currentCarLocation = carSpeed * (timestep - assignmentTime);
    int returnTime = timestep + (currentCarLocation / carSpeed);
    assignedCar->setFinishTime(returnTime);
    outCars.cancel(assignedCar, -1 * assignedCar->getpickuptime());
    assignedCar->GetAssignedRequest()->setRequestType(Cancelled);
    backCars.enqueue(assignedCar, -1 * returnTime);
    numRequests--;
    return;
    //assignedCar->GetAssignedRequest()->~Request();
    //assignedCar->deleteRequest();



}



int Organizer::getCurrentTimestep() const { return timestep; }


void Organizer::FileLoad()
{
    
    ifstream inputFile("scenario_1.txt");
    //ifstream inputFile("scenario_2.txt");
    //ifstream inputFile("scenario_3.txt");
    //ifstream inputFile("scenario_4.txt");
    //ifstream inputFile("scenario_5.txt");
    //ifstream inputFile("scenario_6.txt");
    if (!inputFile.is_open()) {
        cout << "Error! Could not open the file.\n";
        return;
    }
    // read numbre of hosbitals
    int x, y;
    inputFile >> speed->ncSpeed >> speed->scSpeed;
    //inputFile >> speed->scSpeed;
    
    inputFile >> numHospitals;

    // Read distance matrix
    distanceMatrix = vector <vector <int>> (numHospitals, vector<int>(numHospitals));
    for (int i = 0; i < numHospitals; i++) {
        for (int j = 0; j < numHospitals; j++) {
            inputFile >> distanceMatrix[i][j];
        }
    }

    // Print the distance matrix
    cout << "Loaded Distance Matrix:\n";
    for (int i = 0; i < numHospitals; i++) {
        for (int j = 0; j < numHospitals; j++) {
            std::cout << distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "HospitalNUM: " << numHospitals << endl;

    for (int i = 0; i < numHospitals; i++) {
        Hospitals[i] = new Hospital();
        int scars, ncars;
        inputFile >> scars >> ncars;
        numCars += scars + ncars;
        numScars += scars;
        numNcars += ncars;

       // cout << "Scar = " << scars << ", ncars = " << ncars << endl;
        // Add Special Cars
        for (int j = 0; j < scars; j++) {
            SpecialCar* specialCar = new SpecialCar(Hospitals[i]->getHospitalID(), speed->scSpeed, nullptr);
            specialCar->changeCarStatus(Ready);
            Hospitals[i]->addCar(specialCar);
            specialCar->assignToHospital(Hospitals[i]->getHospitalID());
            cout << "Scar ID: " << *specialCar << ", HID: " << *Hospitals[i] << endl;
        }

        // Add Normal Cars
        for (int j = 0; j < ncars; j++) {
            NormalCar* normalCar = new NormalCar(Hospitals[i]->getHospitalID(), speed->ncSpeed, nullptr);
            normalCar->changeCarStatus(Ready);
            Hospitals[i]->addCar(normalCar);
            normalCar->assignToHospital(Hospitals[i]->getHospitalID());
            cout << "Ncar ID: " << *normalCar << ", HID: " << *Hospitals[i] << endl;

        }
    }
    int count = 0;
    //int numRequests;
    inputFile >> numRequests;
    for (int i = 0; i < numRequests; i++) {
        std::string requestType;
        double time, distance;
        int patientID, hospitalID;

        inputFile >> requestType >> time >> patientID >> hospitalID >> distance;
        //requestType.erase(remove_if(requestType.begin(), requestType.end(), isspace), requestType.end());

        if (requestType == "SP") {

           Request* spRequest = new Request(Special, time, patientID, hospitalID, distance);
            requestList.enqueue(spRequest);
        }
        else if (requestType == "EP") {
            int severity;
            inputFile >> severity;
            Request* epRequest = new Request(Emergency, time, patientID, hospitalID, distance, severity);
            requestList.enqueue(epRequest);
        }
        else if (requestType == "NP") {
            Request* npRequest = new Request(Normal, time, patientID, hospitalID, distance);
            requestList.enqueue(npRequest);
        }
        else {
            cout << "Unknown request type found in file: " << requestType << endl;
        }
        cout << ++count << " - Request Type : " << requestType << ", Req Time: " << time << ", PID: " << patientID << ", HID: " << hospitalID << ", dist: " << distance << endl;
    }
    
    // Read number of canceled requests
    
    inputFile >> numCancelledRequests;
    for (int i = 0; i < numCancelledRequests; i++) {
        int requestID, cancelledTime, hospitalID;
        inputFile >> cancelledTime >> requestID >> hospitalID;
        Request* cancelledRequest = new Request(Cancelled, cancelledTime,requestID,hospitalID);
        cancelledList.enqueue(cancelledRequest, -1 * cancelledTime);
       // cancelRequest(requestID, cancelledTime, hospitalID);
    }


    inputFile.close();
    cout << "File data loaded successfully.\n";
}


void Organizer::checkForCancellations() {

}
void Organizer::createfile()
{
    Request* req;
    
    string filename = "Output File.txt";
    ofstream outfile(filename);
    if (!outfile){
        cerr << "Error: couldnot open the file.";
        return;
        }
    outfile << "FT \t PID \t QT \t WT \n";
    int countNP = 0;
    int countEP = 0;
    int countSP = 0;
    int totalWaitTime = 0;
    int totalPickupTime = 0;
    
    for (int i = 0; i < NumFinish; i++) {
        FinishedRequestd.dequeue(req);
        outfile << req->getfinishedtime() << "\t" << req->getID() << "\t" << req->getRequestTime() << "\t" << (req->getwaitingtime()) << "\n";
        if (req->getRequestType() == Normal) countNP++;
        if (req->getRequestType() == Special) countSP++;
        if (req->getRequestType() == Emergency) countEP++;
        totalWaitTime += req->getwaitingtime();
        totalPickupTime += req->getpickupTime();

    }
    outfile << "Patiants : " << numRequests << "\t[ NP : " << countNP << "  , SP : " << countSP << "  , EP : " << countEP<<" ] \n";
    outfile << "Hospitals : " << numHospitals << "\n";
    outfile << "Cars : " << numCars << "\t [ Scars : "<< numScars << " Ncars : " << numNcars << " ] \n";
    outfile << "Avg Wait Time : " << (totalWaitTime / NumFinish) << "\n";
    outfile << "Avg Busy Time : " << ((2 * totalWaitTime) / NumFinish) << "\n";
    outfile << "Avg utalization : " << (((2.0 * totalWaitTime) / NumFinish) / timestep) * 100 << "% \n";
    cout << "Output File Created Successfully.";
      /* outfile<<*/
    
}


void Organizer::Simulator()
{
    
	FileLoad();
	Request* request;
	Car* car;
	int pri;
    
    bool isFinished = false;
    while (NumFinish != numRequests)
    {
        timestep++;
        
        assignRequests();
        if (ui->GetMode() == Interactive) {
            ui->Print();
        }
        FreeToOut();
        OutToBack();
        BackToFree();
        if (cancelledList.peek(request, pri)) {
            
            if (timestep == -1 * pri) {
                // there could be more than one cancellation at each time step, so I need to handle it
                cancelRequest(request);
                cancelledList.dequeue(request, pri);
            }
        }
        //timestep++;

        
        
       

    }
    if (ui->GetMode() == Interactive) {
        ui->Print();
    }
}
       
      
priQueue <Car*>& Organizer::Getoutcars() 
{
    return outCars;
}
priQueue <Car*>& Organizer::Getbackcars()
{
    return backCars ;
}
LinkedQueue <Request*>& Organizer::GetFinishedRequestd()
{
    return FinishedRequestd;
}



int Organizer::getHospitalsCount() const {
    return numHospitals;
}




void Organizer::Run() {
    cout << "======== Ambulance System is Running ============" << endl;
    cout << "Please Select Program Mode, Enter 1 for Interactive mode, 2 for silent mode" << endl;
    int x;
    cin >> x;
    if (x != 1 && x != 2) {
        bool isValid = false;
        while (!isValid) {
            cout << "Please Enter a valid number 1 or 2: ";
            cin >> x;
            if (x == 1 || x == 2)
                isValid = true;
            cout << endl;
        }
    }
    if (x == 1)
        ui = new UI{ Interactive, this };
    else
        ui = new UI{ Silent, this };
    Simulator();
    
}



Organizer::~Organizer() {
    
}




int Organizer::getPickUpTimestep(Request* req, Car* car) {
    int distance = req->getDistance();
    int carSpeed = car->getCarSpeed();
    int currentTime = timestep;
    int pickUpTime = currentTime + (distance / carSpeed);
    return pickUpTime;
}






void Organizer::assignRequests() {
    Request* tmp;
    while (requestList.peek(tmp) && timestep == tmp->getRequestTime()) { // this goes to infinity when 
        requestList.dequeue(tmp);
        
        int hospitalid = tmp->getHospitalID();

       RequestType reqtype = tmp->getRequestType();
       if (reqtype == Emergency) {
           Hospitals[hospitalid - 1]->addRequest(tmp, tmp->getPriority());
       }

       else
           Hospitals[hospitalid - 1]->addRequest(tmp);
   

    }
}
