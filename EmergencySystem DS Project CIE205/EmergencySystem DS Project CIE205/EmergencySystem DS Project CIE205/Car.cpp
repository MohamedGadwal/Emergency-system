#include "Car.h"

int Car::globalID = 1;


ostream& operator<<(ostream& os, const Car& car) // overload "<<" operator to cout any car details directly.
{
	os << car.id;
	return os;
}

Car::Car(int HospitalID, double CarSpeed, Request* AssignedRequest)
{
	
	carSpeed = CarSpeed;
	assignedRequest = AssignedRequest;
	car_HospitalID = HospitalID;
	id = globalID++;
	status = UnknownStatus;
}

void Car::assignToHospital(int HospitalID) {
	car_HospitalID = HospitalID;
}

int Car::getRelatedHospitalID() const {
	return car_HospitalID; // return -1 if null
}

void Car::setpickuptime(int time) {
	pickuptime = time;
}
int Car::getpickuptime() {
	return pickuptime;
}

void Car::setFinishTime(int time) {
	finishTime = time;
}
int Car::getFinishTime() {
	return finishTime;
}

void Car::deleteRequest() {
	delete assignedRequest;
	assignedRequest = nullptr;
}


//Hospital* Car::GetHospital() const { return hospital; }

char Car::getCarType() {
	if (dynamic_cast<SpecialCar*> (this))
		return 'S';
	else if (dynamic_cast<NormalCar*> (this))
		return 'N';
	else
		return 'X';


}
Request* Car::GetAssignedRequest() {
	return assignedRequest;
}

void Car::changeCarStatus(carStatus Status) { status = Status;}

void Car::assignRequest(Request* req) { assignedRequest = req; }

carStatus Car::getStatus() const { return status; }


int Car::getCarID() const { return id; }


double Car::getCarSpeed() const { return carSpeed; }


bool Car::isAssigned(Request*& request) const {
	if (assignedRequest) {
		request = assignedRequest;
		return true;
	}
	else {
		request = nullptr;
		return false;
	}
}

Car::~Car() { delete assignedRequest; };

SpecialCar::SpecialCar(int HospitalID, double CarSpeed, Request* AssignedRequest) : Car(HospitalID, CarSpeed, AssignedRequest){}


NormalCar::NormalCar(int HospitalID, double CarSpeed, Request* AssignedRequest) : Car(HospitalID, CarSpeed, AssignedRequest) {}


