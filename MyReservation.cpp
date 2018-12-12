
#include "MyReservation.h"
#include "IDGenerator.h"

string MyReservation::getID() {
    return this->id;
}

Customer *MyReservation::getCustomer() {
    return this->flyData->getCustomer(this->customerID);
}

Flight *MyReservation::getFlight() {
    return this->flyData->getFlight(this->flightID);
}

Classes MyReservation::getClass() {
    return this->cls;
}

int MyReservation::getMaxBaggage() {
    return this->maxBaggage;
}

MyReservation::MyReservation(const string& customerID, const string& flightID, Classes cls, int baggage, FlyData* flyData) {
    this->id = IDGenerator::generate();
    this->customerID = customerID;
    this->flightID = flightID;
    this->cls = cls;
    this->maxBaggage = baggage;
    this->flyData = flyData;
    // check if the class is full
    this->flyData->checkFull(flightID, cls);
}

MyReservation::MyReservation(const string& id, const string& customerID, const string& flightID, Classes cls, int bag, FlyData* flyData) {
    this->id = id;
    this->customerID = customerID;
    this->flightID = flightID;
    this->cls = cls;
    this->maxBaggage = bag;
    this->flyData = flyData;
    // check if the class is full
    this->flyData->checkFull(flightID, cls);
}

MyReservation::~MyReservation() {
}