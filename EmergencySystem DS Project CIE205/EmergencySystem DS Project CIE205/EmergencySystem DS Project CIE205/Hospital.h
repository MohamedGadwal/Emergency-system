#pragma once

#include "LinkedQueue.h"
#include "priQueue.h"
#include "Request.h"
#include "Car.h"
#include "Organizer.h"

class Car;
class Request;
//struct position;
struct position {
	int x, y;
};



class Hospital
{
	static int globalID;
	int id;
	int requestCount;
	//Organizer *organizer;

	LinkedQueue <Request*> SpecialRequests;
	priQueue <Request*> EmergencyRequest;
	LinkedQueue <Request*> NormalRequest;

	// Queue with cancellation functionallity for normal requests.
	LinkedQueue <Car*> SpecialCars;
	LinkedQueue <Car*> NormalCars;
	friend ostream& operator <<(ostream& os, const Hospital& hospital);
	
public:
	Hospital();
	//Hospital(const Hospital& H); // Copy Constructor
	void addCar(Car* car);
	void addRequest(Request* request, int severity = NULL);
	int getHospitalID() const;
	void calculateRequiredTime(); // Could be moved to be in another class, or still here
	void assignCarToRequest(Car* car, Request* req);
	LinkedQueue <Request*>& GetSP() ;
	priQueue <Request*>& GetEP() ;
	LinkedQueue <Request*>& GetNP() ;
	LinkedQueue <Car*>& GetSpecialCars();
	LinkedQueue <Car*>& GetNormalCars();
	bool shouldTerminate(Request* request);
	//void FreeToOut();
	//int getRequestCount();
	int getRequestCount();
	
	//void PrintHospital() const;

};





