#include "UI.h"
using namespace std;


UI::UI(Mode mode, Organizer* org)
{
	Currentmode = mode;
	organizer = org;
}


string UI::GetInfile() const{
	return Infile;
}
string UI::GetOutFile() const {
	return Outfile;
}
void UI::SetInFile(string infile) {
	Infile = infile;
}
void UI::SetOutFile(string outfile) {
	Outfile = outfile;
}
Mode UI::GetMode() const {
	if (Currentmode == 1)
		return Interactive;
	else		// Currentmode == 1
		return Silent;
}
void UI::SetMode(int mode) {
	if (mode == 1)
		Currentmode = Interactive;
	else if (mode == 2)
		Currentmode = Silent;


}





//void UI::Print(int timestep, Hospital* hospitals[], int NumOfHospitals, priQueue <Car*> outCars, priQueue <Car*> backCars, LinkedQueue <Request*> FinishedRequestd, int finish, int out, int back) const
void UI::Print()
{

	Request* tmp;
	int pri;
	Car* car;
	cout << "\n\n\n\n";
	cout << "Current Timestep:" << organizer->getCurrentTimestep() <<endl;
	cout << "\n\n\n\n\n";
	for (int i = 0; i < organizer->getHospitalsCount();i++)
	{
		
		cout << "=============    Hospital #" << i + 1 << " data    =============== "<<endl;
		//organizer->GetHospital(i)->GetEP().printQ();
		//priQueue<Request*> test = hospitals[i]->GetEP();
		cout << organizer->GetHospital(i)->GetEP().getSize()  << " EP Request: ";
		//hospitals[i]->GetEP().printQ();
		organizer->GetHospital(i)->GetEP().printQ();
		cout << endl;

		//cout << hospitals[i]->GetSP().getSize() << " SP Request: ";
		cout << organizer->GetHospital(i)->GetSP().getSize() << " SP Request: ";
		organizer->GetHospital(i)->GetSP().printQ();
		cout << endl;

		cout << organizer->GetHospital(i)->GetNP().getSize() << " NP Request: ";
		organizer->GetHospital(i)->GetNP().printQ();
		cout << endl;

		int pri;
		cout << "Free Cars: ";
		LinkedQueue<Car*> ClonedNcars(organizer->GetHospital(i)->GetNormalCars());
			
			ClonedNcars.dequeue(car);
			cout << organizer->GetHospital(i)->GetNormalCars().getSize() << " NCars, ";
		LinkedQueue<Car*> ClonedScars(organizer->GetHospital(i)->GetSpecialCars());
		
		ClonedScars.dequeue(car);
		cout << organizer->GetHospital(i)->GetSpecialCars().getSize() << " SCars, ";
		cout << endl;
		cout << "=============    Hospital #" << i + 1 << " data end  ============= " << endl;
		cout << "------------------------------------------------------------------"<<endl;
		cout << organizer->Getoutcars().getSize() << " ==> Out Cars : "; //outCars.printQ();  ///this not complete 
		//organizer->Getoutcars().printQ();
		
	
		priQueue<Car*> ClonedOut(organizer->Getoutcars());
		int size = ClonedOut.getSize();

		if (ClonedOut.getSize() > 0 && organizer->GetHospital(i)) {
			for (int j = 0; j < size; j++) {
				ClonedOut.dequeue(car, pri);
				cout << car->getCarType() << *car << "_" << "H" << car->getRelatedHospitalID() << "_" << "P" << car->GetAssignedRequest()->getID() << ", ";
			}
		}


		cout << endl;

		cout << organizer->Getbackcars().getSize() << " <== BacK Cars :"; // this also not complete 
		priQueue<Car*> ClonedBack(organizer->Getbackcars());
		int size2 = ClonedBack.getSize();
		
		if (ClonedBack.getSize() > 0 && organizer->GetHospital(i)) {
			for (int j = 0; j < size2; j++) {
				ClonedBack.dequeue(car, pri);
				cout << car->getCarType() << *car << "_" << "H" << car->getRelatedHospitalID() << "_" << "P" << car->GetAssignedRequest()->getID() << ", ";
			}
		}


		cout << endl;

		cout << "------------------------------------------------------------------" << endl;
		//cout << finish << " Finished Patients: "; // wait for the print method of the finish Queue
		cout << organizer->GetFinishedRequestd().getSize() << " Finished Patients: ";
		organizer->GetFinishedRequestd().printQ();
		cout << "Press any key to display next hospital...." << endl;
		std::cin.ignore();
		
	}
	

}


 
 
 
//void UI::Print(Organizer* pO) const
//{
//	cout << "Current Timestep:" << timestep<<endl;
//	for (int i = 0; i < ;i++)
//	{
//		cout << "=============    Hospital #" << i + 1 << " data    =============== "<<endl;
//		
//		cout << "=============    Hospital #" << i + 1 << " data end  ============= " << endl;
//		cout << "------------------------------------------------------------------"<<endl;
//		cout << out<<" ==> Out Cars : "<<""<<endl;  ///this not complete 
//		cout << back << " <== BacK Cars :"; // this also not complete 
//		cout << "------------------------------------------------------------------" << endl;
//		cout << finish << " Finished Patients: "; // wait for the print method of the finish Queue
//		cout << "Press any key to display next hospital...." << endl;
//		std::cin.ignore(); 
//	}
//
//
//}
