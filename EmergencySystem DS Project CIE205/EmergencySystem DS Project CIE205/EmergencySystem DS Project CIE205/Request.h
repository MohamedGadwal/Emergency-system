#pragma once
#include <iostream>
#include "Car.h"
using namespace std;


enum RequestType {
	Normal,
	Special,
	Emergency,
	Cancelled,
	UnknownRequest
};
class Hospital;
class Request
{
	int PatientID;
	RequestType type;
	int requestTime;
	
	//Hospital* relatedHospital;
	int distance;
	int priority;
	int HospitalID;
	int finishedtime;
	int waitingtime;
	int pickupTime;

public:
	Request(RequestType Type, int RequestTime, int PatinetID, int HospitalID, int requestDistance = NULL, int Priority = -1);
	int getRequestTime() const;
	void setRequestTime(int time);
	void setRequestDistance(int Distance);
	int getID() const;
	void setpickupTime(int time);
	int getpickupTime() const;
	void setfinishtime(int time) ;
	void setwaiting(int time);
	int getfinishedtime() const;
	int getwaitingtime() const;
	int getDistance() const;
	void setRequestType(RequestType Type);
	RequestType getRequestType() const;
	friend ostream& operator<<(ostream& os, const Request& request);
	int getHospitalID();
	void setHospitalID(int id);
	int getPriority();
	void setPriority(int P);
	//void setID();
	~Request();
};



