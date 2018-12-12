
#include "MyFlight.h"
#include "IDGenerator.h"
#include <map>
#include <iostream>

string MyFlight::getID() {
    return this->id;
}

int MyFlight::getModelNumber() {
    return this->modelNumber;
}

list<Employee *> MyFlight::getAssignedCrew() {
    return this->assignedCrew;
}

Date MyFlight::getDate() {
    return this->date;
}

string MyFlight::getSource() {
    return this->source;
}

string MyFlight::getDestination() {
    return this->destination;
}

list<Reservation *> MyFlight::getReservations() {
    return this->flyData->getReservationsOfFlight(this->id);
}

MyFlight::MyFlight(int modelNumber, Date date, const string& source, const string& destination, FlyData* flyData) : date(date) {
    this->id=IDGenerator::generate();
    this->modelNumber = modelNumber;
    this->date = date;
    this->source = source;
    this->destination = destination;
    this->flyData = flyData;
    this->assignedCrew=this->flyData->assignCrew(this);
}

MyFlight::MyFlight(const string& id, int model, Date date, const string& source, const string& dest, FlyData* flyData) : date(date) {
    this->id = id;
    this->modelNumber = model;
    this->date = date;
    this->source = source;
    this->destination = dest;
    this->flyData = flyData;
    this->assignedCrew = this->flyData->assignCrew(this);
}

MyFlight::~MyFlight() {
}