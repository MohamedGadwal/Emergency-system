#include "Request.h"





Request::Request(RequestType Type, int RequestTime, int PatientID, int HospitalID, int requestDistance, int Priority){
	type = Type;
	priority = Priority;
	requestTime = RequestTime;
	distance = requestDistance;
	this->HospitalID = HospitalID;
	this->PatientID = PatientID;
	
}


int Request::getHospitalID() { return HospitalID; }
void Request::setHospitalID(int id) { HospitalID = id; }

void Request::setRequestDistance(int Distance) { distance = Distance; }

int Request::getDistance() const { return distance; }
int Request::getPriority() { return priority; }
void Request::setPriority(int P) { priority = P; }
int Request::getID() const { return PatientID; }

void Request::setpickupTime(int time)
{
	pickupTime = time;
}

int Request::getpickupTime() const
{
	return pickupTime ;
}

void Request::setfinishtime(int time)
{
	finishedtime = time;
}

void Request::setwaiting(int time)
{
	waitingtime = time;
}

int Request::getfinishedtime() const
{
	return finishedtime;
}



int Request::getwaitingtime() const
{
	return waitingtime;
}

void Request::setRequestType(RequestType Type) { type = Type; }
RequestType Request::getRequestType() const { return type; }


int Request::getRequestTime() const { return requestTime; }

void Request::setRequestTime(int time) { requestTime = time; }

ostream& operator<<(ostream& os, const Request& request) // overload "<<" operator to cout any request directly.
{
	os << request.PatientID;
	return os;
}


Request::~Request() {
	delete this;
}