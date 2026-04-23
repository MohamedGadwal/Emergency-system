#include "Hospital.h"

int Hospital::globalID = 1;





ostream& operator<<(ostream& os, const Hospital& hospital) // overload "<<" operator to cout any request directly.
{
	os << hospital.id;
	return os;
}


Hospital::Hospital() {
	id = globalID++;
	requestCount = 0;
}




int Hospital::getHospitalID() const { return id; }

int Hospital::getRequestCount() { return requestCount; }

void Hospital::addCar(Car* car) {
	if (dynamic_cast<NormalCar*> (car)) // dynamic casting --> if this car object is a special car
		// include it in special cars queue.
		NormalCars.enqueue(car);
	else if (dynamic_cast<SpecialCar*> (car)) {
		SpecialCars.enqueue(car);
		
	}
	else return;
}



void Hospital::addRequest(Request* request, int severity) {
	switch (request->getRequestType())
	{
	case Special:
		SpecialRequests.enqueue(request);
		requestCount++;
		break;
	case Emergency:
		EmergencyRequest.enqueue(request, severity); // Remember to edit this
		requestCount++;
		break;
	case Normal:
		NormalRequest.enqueue(request);
		requestCount++;
	default:
		return;
		break;
	}
}
 LinkedQueue<Request*>& Hospital::GetNP() {
	return NormalRequest;
}
 priQueue<Request*>& Hospital::GetEP(){
	return EmergencyRequest;
}
 LinkedQueue<Request*>& Hospital::GetSP() {
	 return SpecialRequests;
 }

 LinkedQueue<Car*>& Hospital:: GetSpecialCars() {
	 return SpecialCars;
 }
 LinkedQueue<Car*>& Hospital::GetNormalCars() {
	 return NormalCars;
 }
 

 void Hospital::calculateRequiredTime(){} // No implementation yet
 void Hospital::assignCarToRequest(Car* car, Request* req){
 // 
	 //if(car->isAssigned(req))
	 car->assignRequest(req);
 }

 bool Hospital::shouldTerminate(Request* request) {
	 //LinkedQueue<Request> temp;
	 //Request Clone = { UnknownRequest,-1 };
	 //while (Clone.getID() != request->getID()) {
		// switch (request->getRequestType())
		// {
		// case Normal: // Error
		//	 if (request->getID() == Clone.getID()) {
		//		 
		//	 }
		// default:
		//	 break;
		// }
	 //}
	 return false;
 }

 // moves cars from free to out 
 //void Hospital::FreeToOut() 
 //{
	// Request* temp;
	// int pri;
	// Car* tempcar;
	// int timepri;
	// int pickuptime;
	// // handle the emergency requests 
	// while (!EmergencyRequest.isEmpty()  && EmergencyRequest.peek(temp,pri) && temp->getRequestTime()<= organizer->getCurrentTimestep())
	// {

	//	 if (!NormalCars.isEmpty()) 
	//	 {
	//		 EmergencyRequest.dequeue(temp,pri);
	//		 NormalCars.dequeue(tempcar);
	//		 tempcar->assignRequest(temp);
	//		 timepri = organizer->getCurrentTimestep() + 2 * (temp->getDistance() / tempcar->getCarSpeed());  // reach time 
	//		 pickuptime = organizer->getCurrentTimestep() + (temp->getDistance() / tempcar->getCarSpeed());
	//		 tempcar->setreachtime(timepri);
	//		 tempcar->setpickuptime(pickuptime);
	//		 organizer->Getoutcars().enqueue(tempcar , -1*timepri);

	//	 }
	//	 else if (!SpecialCars.isEmpty()) 
	//	 {
	//		 EmergencyRequest.dequeue(temp, pri);
	//		 SpecialCars.dequeue(tempcar);
	//		 tempcar->assignRequest(temp);
	//		 timepri = organizer->getCurrentTimestep() + 2 * (temp->getDistance() / tempcar->getCarSpeed());
	//		 pickuptime = organizer->getCurrentTimestep() + (temp->getDistance() / tempcar->getCarSpeed());
	//		 tempcar->setreachtime(timepri);
	//		 tempcar->setpickuptime(pickuptime);
	//		 organizer->Getoutcars().enqueue(tempcar, -1 * timepri);
	//	 }
	// }
	// // handle special requests 
	// while (!SpecialRequests.isEmpty() && SpecialRequests.peek(temp) && temp->getRequestTime() <= organizer->getCurrentTimestep())
	// {
	//	 if (!SpecialCars.isEmpty())
	//	 {
	//		 SpecialRequests.dequeue(temp);
	//		 SpecialCars.dequeue(tempcar);
	//		 tempcar->assignRequest(temp);
	//		 timepri = organizer->getCurrentTimestep() + 2 * (temp->getDistance() / tempcar->getCarSpeed());
	//		 pickuptime = organizer->getCurrentTimestep() + (temp->getDistance() / tempcar->getCarSpeed());
	//		 tempcar->setreachtime(timepri);
	//		 tempcar->setpickuptime(pickuptime);
	//		 organizer->Getoutcars().enqueue(tempcar, -1 * timepri);
	//	 }
	// }
	// 
	// // handle normal cars 
	// while (!NormalRequest.isEmpty() && NormalRequest.peek(temp) && temp->getRequestTime() <= organizer->getCurrentTimestep()) 
	// {

	//	 if (!NormalCars.isEmpty())
	//	 {
	//		 NormalRequest.dequeue(temp);
	//		 NormalCars.dequeue(tempcar);
	//		 tempcar->assignRequest(temp);
	//		 timepri = organizer->getCurrentTimestep() + 2 * (temp->getDistance() / tempcar->getCarSpeed());
	//		 pickuptime = organizer->getCurrentTimestep() + (temp->getDistance() / tempcar->getCarSpeed());
	//		 tempcar->setreachtime(timepri);
	//		 tempcar->setpickuptime(pickuptime);
	//		 organizer->Getoutcars().enqueue(tempcar, -1 * timepri);
	//	 }
	// }
 //}