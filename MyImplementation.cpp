
#include "MyImplementation.h"
#include "MyCustomer.h"
#include "MyEmployee.h"
#include "MyReservation.h"
#include "MyFlight.h"
#include "MyPlane.h"
#include "IDGenerator.h"

Employee* MyImplementation::addEmployee(int seniority, int birthYear, string employerID, Jobs title) {
    if (seniority < 0) {
        throw "illegal seniority";
    }
    this->loadData();
    Employee *employee = new MyEmployee(seniority, birthYear, employerID, title, &this->flyData);
    this->flyData.addEmployee(employee);
    return employee;
}

Employee* MyImplementation::getEmployee(string id) {
    this->loadData();
    return this->flyData.getEmployee(id);
}

Plane* MyImplementation::addPlane(int modelNumber, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers) {
    this->loadData();
    Plane *plane = new MyPlane(modelNumber, crewNeeded, maxPassangers, &this->flyData);
    this->flyData.addPlane(plane);
    return plane;
}

Plane* MyImplementation::getPlane(string id) {
    this->loadData();
    return this->flyData.getPlane(id);
}

Flight* MyImplementation::addFlight(int modelNumber, Date date, string source, string destination) {
    this->loadData();
    Flight *flight = new MyFlight(modelNumber, date, source, destination, &this->flyData);
    this->flyData.addFlight(flight);
    return flight;
}

Flight* MyImplementation::getFlight(string id) {
    this->loadData();
    return this->flyData.getFlight(id);
}

Customer* MyImplementation::addCustomer(string fullName, int priority) {
    if(priority < 1 || priority > 5) {
        throw "illegal priority";
    }
    if(fullName.find(' ')==string::npos){
        throw "illegal full name";
    }
    this->loadData();
    Customer *customer = new MyCustomer(fullName, priority, &this->flyData);
    this->flyData.addCustomer(customer);
    return customer;
}

Customer* MyImplementation::getCustomer(string id) {
    this->loadData();
    return this->flyData.getCustomer(id);
}

Reservation* MyImplementation::addResevation(string customerID, string flightID, Classes cls, int maxBaggage) {
    this->loadData();
    Reservation *reservation = new MyReservation(customerID, flightID, cls, maxBaggage, &this->flyData);
    this->flyData.addReservation(reservation);
    return reservation;
}

Reservation* MyImplementation::getReservation(string id) {
    this->loadData();
    return this->flyData.getReservation(id);
}

void MyImplementation::exit() {
    cout << "so sad you are leaving!" << endl;
    this->flyData.saveData();
}

MyImplementation::MyImplementation() {
    IDGenerator::init();
    this->dataLoaded = false;
}

MyImplementation::~MyImplementation() {
}

void MyImplementation::loadData() {
    if (!this->dataLoaded) {
        this->flyData.loadData();
        this->dataLoaded = true;
    }
}