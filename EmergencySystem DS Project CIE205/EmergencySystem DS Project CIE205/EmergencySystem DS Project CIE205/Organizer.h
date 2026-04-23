#pragma once
#include "LinkedQueue.h"
#include "priQueue.h"
#include "Request.h"
#include "Car.h"
#include "Hospital.h"
#include <random>
#include "UI.h"

class Hospital;
class Request;
struct Speed;
class UI;
class Organizer
{
	int timestep = 0;
	int numRequests;
	int numCancelledRequests;
	int numHospitals;
	int numCars = 0;
	int numScars = 0;
	int numNcars = 0;
	int NumOutcars = 0;
	int NumBackCars = 0;
	int NumFinish = 0;
	vector <vector <int>> distanceMatrix;
	//int numHospitals;
	enum { Max_Hospitals_Number = 50 };
	Hospital* Hospitals[Max_Hospitals_Number];
	CancelationQueue <Car*> outCars;
	priQueue <Car*> backCars;
	LinkedQueue <Request*> requestList;
	priQueue <Request*> cancelledList;
	LinkedQueue <Request*> FinishedRequestd;
	priQueue<Request*> waitingList;
	Speed* speed;
	UI* ui;

public:
	Organizer();
	void Run();
	void FileLoad();
	void createfile();
	void Simulator();
	int getCurrentTimestep() const;
	int getHospitalsCount() const;
	void cancelRequest(Request* request);
	void assignRequests();
	Car* findCar(Request* request);
	int getPickUpTimestep(Request* req, Car* car);
	priQueue <Car*>& Getoutcars();
	priQueue <Car*>& Getbackcars();
	LinkedQueue <Request*>& GetFinishedRequestd();
	void OutToBack();
	void FreeToOut();
	void BackToFree();
	void AddPatientToFinishList(Request* patient);
	Hospital*& GetHospital(int id);
	void checkForCancellations();
	void HandleEPBonus(int i, Request* temp, int pri);
	void AssignEP(Car* car , int HospitalId);
	void AssignSP(Car* car, int HospitalId);
	void AssignNP(Car* car, int HospitalId);


	//void calculateDistance(Hospital* h, Request* req); // Calculate the relative distance between the hospital and patient
	~Organizer();

};

