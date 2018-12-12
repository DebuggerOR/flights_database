
#include "IDGenerator.h"
#include "MyEmployee.h"

int MyEmployee::getBirthYear() {
    return this->birthYear;
}

Employee* MyEmployee::getEmployer() {
    return this->flyData->getEmployee(this->employerID);
}

string MyEmployee::getID() {
    return this->id;
}

int MyEmployee::getSeniority() {
    return this->seniority;
}

Jobs MyEmployee::getTitle() {
    return this->title;
}

MyEmployee::MyEmployee(int seniority, int birthYear, const string& employerID, Jobs title, FlyData* flyData) {
    this->id = IDGenerator::generate();
    this->seniority = seniority;
    this->birthYear = birthYear;
    this->employerID = employerID;
    if (this->employerID.empty()) {
        this->employerID = "no employer";
    }
    this->title = title;
    this->flyData = flyData;
}

MyEmployee::MyEmployee(const string& id, int seniority, int birthYear, const string& employerID, Jobs title, FlyData* flyData) {
    this->id = id;
    this->seniority = seniority;
    this->birthYear = birthYear;
    this->employerID = employerID;
    if (this->employerID.empty()) {
        this->employerID = "no employer";
    }
    this->title = title;
    this->flyData = flyData;
}

MyEmployee::~MyEmployee() {
}
