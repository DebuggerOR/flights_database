
#include "MyPlane.h"
#include "IDGenerator.h"

string MyPlane::getID() {
    return this->id;
}

int MyPlane::getModelNumber() {
    return this->modelNumber;
}

map<Jobs, int> MyPlane::getCrewNeeded() {
    return this->crewNeeded;
}

int MyPlane::getMaxFirstClass() {
    return this->maxPassengers.at(FIRST_CLASS);
}

int MyPlane::getMaxEconomyClass() {
    return this->maxPassengers.at(SECOND_CLASS);
}

MyPlane::MyPlane(int modelNumber, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers, FlyData* flyData) {
    this->id = IDGenerator::generate();
    this->modelNumber = modelNumber;
    this->crewNeeded = move(crewNeeded);
    this->maxPassengers = move(maxPassangers);
    this->flyData = flyData;
}

MyPlane::MyPlane(string id, int modelNumber, map<Jobs, int> crew, map<Classes, int> maxPassengers, FlyData *flyData) {
    this->id = move(id);
    this->modelNumber = modelNumber;
    this->crewNeeded = move(crew);
    this->maxPassengers = move(maxPassengers);
    this->flyData = flyData;
}

MyPlane::~MyPlane() {
}
