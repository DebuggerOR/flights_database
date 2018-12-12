
#include <iostream>
#include "MyCustomer.h"
#include "IDGenerator.h"

string MyCustomer::getID(){
    return this->id;
}

string MyCustomer::getFullName() {
    return this->name;
}

int MyCustomer::getPriority() {
    return this->priority;
}

list<Reservation *> MyCustomer::getReservations() {
    return this->flyData->getReservationsOfCustomer(this->id);
}

MyCustomer::MyCustomer(const string& name, int priority, FlyData* flyData) {
    this->id = IDGenerator::generate();
    this->name = name;
    this->priority = priority;
    this->flyData = flyData;
}

MyCustomer::MyCustomer(const string& id, const string& name, int priority, FlyData *flyData) {
    this->id = id;
    this->name = name;
    this->priority = priority;
    this->flyData = flyData;
}

MyCustomer::~MyCustomer() {
}