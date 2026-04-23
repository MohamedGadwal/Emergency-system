#pragma once
//#include "Organizer.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "Request.h"
#include"Hospital.h"

// Another Hamada passed from here
class Hospital;
enum carStatus 
{
	Ready,
	Assigned,
	Loaded,
	UnknownStatus
}; 

struct Speed {
	int ncSpeed;
	int scSpeed;
};

class Request;
class Car
{
protected:
	static int globalID;
	int id;
	double carSpeed;
	Request* assignedRequest;
	carStatus status;
	int car_HospitalID;
	int pickuptime;
	int finishTime;
public:
	Car(int HospitalID, double CarSpeed = -1, Request* AssignedRequest = nullptr);
	//Hospital* GetHospital()const;
	void changeCarStatus(carStatus Status);
	carStatus getStatus() const;
	int getCarID() const;
	double getCarSpeed() const;
	bool isAssigned(Request*& request) const;
	int getRelatedHospitalID() const;
	void assignToHospital(int HospitalID);
	Request* GetAssignedRequest();
	char getCarType();
	void assignRequest(Request* req);
	void setpickuptime(int time);
	int getpickuptime();
	void setFinishTime(int time);
	int getFinishTime();
	void deleteRequest();
	
	friend ostream& operator <<(ostream& os, const Car& car);
	// this function tells you if this car is assigned or not
	// you should pass a pointer to request to it will work as follows
	// if this car is assigned, it will return true and give you the request you're seeking for
	// if it's not assigned it will return false and your request will equal null
	// so request = nullptr; ..
	// do we really need this? Idk
	// why did you made it then? because I wanted to.
	virtual ~Car();
};

class SpecialCar : public Car {

public:
	SpecialCar(int HospitalID, double CarSpeed, Request* AssignedRequest);
};

class NormalCar : public Car {

public:
	NormalCar(int HospitalID, double CarSpeed, Request* AssignedRequest);
};


