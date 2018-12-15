
#include <fstream>
#include <iostream>
#include "FlyData.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyPlane.h"
#include "MyReservation.h"
#include "MyFlight.h"

string jobToStr(Jobs job){
    switch (job){
        case MANAGER:
            return "Manager";
        case NAVIGATOR:
            return "Navigator";
        case FLY_ATTENDANT:
            return "Fly_Attendant";
        case PILOT:
            return "Pilot";
        default:
            return "Other";
    }
}

Jobs strToJob(const string &str) {
    if (str == "Manager") { return MANAGER; }
    if (str == "Navigator") { return NAVIGATOR; }
    if (str == "Fly_Attendant") { return FLY_ATTENDANT; }
    if (str == "Pilot") { return PILOT; }
    return OTHER;
}

void FlyData::parseEmployee(const string& line) {
    int i = 0;
    while (line[i++] != '\t');
    // find id
    string id;
    while (line[i] != '\t') { id += line[i++]; }
    i++;
    // find boss
    string boss;
    while (line[i] != '\t') { boss += line[i++]; }
    i++;
    // find birth
    int birth = 0;
    while (line[i] != '\t') {
        birth *= 10;
        birth += line[i++] - '0';
    }
    i++;
    // find job
    string job;
    while (line[i] != '\t') { job += line[i++]; }
    i++;
    // find seniority
    int seniority = 0;
    while (i < line.length()) {
        seniority *= 10;
        seniority += line[i++] - '0';
    }

    this->employees.push_back(new MyEmployee(id, seniority, birth, boss, strToJob(job), this));
}

void FlyData::parsePlane(const string& line) {
    int i = 0;
    while (line[i++] != '\t');
    // find id
    string id;
    while (line[i] != '\t') { id += line[i++]; }
    i++;
    // find model number
    int modelNumber = 0;
    while (line[i] != '\t') {
        modelNumber *= 10;
        modelNumber += line[i++] - '0';
    }
    i++;
    // find map class to num passengers
    map<Classes, int> maxClasses;
    int maxFirst = 0;
    while (line[i] != '\t') {
        maxFirst *= 10;
        maxFirst += line[i++] - '0';
    }
    maxClasses.insert(std::pair<Classes, int>(FIRST_CLASS, maxFirst));
    i++;
    int maxEconomy = 0;
    while (line[i] != '\t') {
        maxEconomy *= 10;
        maxEconomy += line[i++] - '0';
    }
    maxClasses.insert(std::pair<Classes, int>(SECOND_CLASS, maxEconomy));
    i++;
    // find map job to num crew needed
    string job;
    int numJobs;
    map<Jobs, int> crewNeeded;
    while (i < line.length()) {
        job = "";
        while (line[i] != ':') { job += line[i++]; }
        i++;
        numJobs = 0;
        while (line[i] != '.') {
            numJobs *= 10;
            numJobs += line[i++] - '0';
        }
        i++;
        crewNeeded.insert(std::pair<Jobs, int>(strToJob(job), numJobs));
    }
    this->planes.push_back(new MyPlane(id, modelNumber, crewNeeded, maxClasses, this));
}

void FlyData::parseCustomer(const string& line) {
    int i = 0;
    while (line[i++] != '\t');
    // find id
    string id;
    while (line[i] != '\t') {id += line[i++];}
    i++;
    // find name
    string name;
    while (line[i] != '\t') {name += line[i++];}
    i++;
    // find priority
    int priority = 0;
    while (i < line.length()) {
        priority *= 10;
        priority += line[i++] - '0';
    }
    this->customers.push_back(new MyCustomer(id, name, priority, this));
}

void FlyData::parseFlight(const string& line) {
    int i=0;
    while (line[i++]!='\t');
    // find id
    string id;
    while (line[i]!='\t'){id+=line[i++];}
    i++;
    // find date
    string date;
    while (line[i]!='\t'){date+=line[i++];}
    i++;
    // find model number
    int modelNumber = 0;
    while (line[i] != '\t') {
        modelNumber *= 10;
        modelNumber += line[i++] - '0';
    }
    i++;
    // find source
    string source;
    while (line[i]!='\t'){source+=line[i++];}
    i++;
    // find destination
    string destination;
    while (i<line.length()){destination+=line[i++];}

    this->flights.push_back(new MyFlight(id, modelNumber, Date(date), source, destination, this));
}

void FlyData::parseReservation(const string& line) {
    int i=0;
    while (line[i++]!='\t');
    // find id
    string id;
    while (line[i]!='\t'){id+=line[i++];}
    i++;
    // find flight id
    string flightID;
    while (line[i]!='\t'){flightID+=line[i++];}
    i++;
    // find flight id
    string customerID;
    while (line[i]!='\t'){customerID+=line[i++];}
    i++;
    // find model number
    int baggage = 0;
    while (line[i] != '\t') {
        baggage *= 10;
        baggage += line[i++] - '0';
    }
    i++;
    // find class
    int cls=line[i] - '0';

    this->reservations.push_back(new MyReservation(id, customerID, flightID, Classes(cls), baggage, this));
}

void FlyData::saveData() {
    int rawNum = 1;
    ofstream file("fly_data.txt");

    if (file.is_open()) {
        file << " " << rawNum++ << "========== employees (id, boss, birth, seniority, job) ==========" << endl;
        for (auto &employee : this->employees) {
            file << "e" << rawNum++ << "\t" << employee->getID();
            if (employee->getEmployer() == nullptr) {
                file << "\tno employer";
            } else {
                file << "\t" << employee->getEmployer()->getID();
            }
            file << "\t" << employee->getBirthYear()
                 << "\t" << jobToStr(employee->getTitle())
                 << "\t" << employee->getSeniority() << endl;
        }
        file << " " << rawNum++ << "========== customers (id, name, priority) ==========" << endl;
        // save id, priority, full name (take reservations from other table)
        for (auto &customer : this->customers) {
            file << "c" << rawNum++ << "\t" << customer->getID()
                 << "\t" << customer->getFullName()
                 << "\t" << customer->getPriority() << endl;
        }
        file << " " << rawNum++ << "========== planes (id, model, first class, eco class, crew) ==========" << endl;
        for (auto &plane : this->planes) {
            file << "p" << rawNum++ << "\t" << plane->getID()
                 << "\t" << plane->getModelNumber()
                 << "\t" << plane->getMaxFirstClass()
                 << "\t" << plane->getMaxEconomyClass() << "\t";
            for (auto &x : plane->getCrewNeeded()) {
                file << jobToStr((x.first)) << ":" << x.second << ".";
            }
            file << endl;
        }
        file << " " << rawNum++ << "========== flights (id, date, model, source, destination) ==========" << endl;
        for (auto &flight : this->flights) {
            file << "f" << rawNum++ << "\t" << flight->getID()
                 << "\t" << flight->getDate().getDate()
                 << "\t" << flight->getModelNumber()
                 << "\t" << flight->getSource()
                 << "\t" << flight->getDestination() << endl;
        }
        file << " " << rawNum++ << "========== reservations (id, flight, customer, baggage, class) ==========" << endl;
        for (auto &reservation : this->reservations) {
            file << "r" << rawNum++ << "\t" << reservation->getID()
                 << "\t" << reservation->getFlight()->getID()
                 << "\t" << reservation->getCustomer()->getID()
                 << "\t" << reservation->getMaxBaggage()
                 << "\t" << reservation->getClass() << endl;
        }
        file << "this_is_the_end_of_fly_data";
        file.close();
    } else {
        throw "enable to open file";
    }
}

void FlyData::loadData() {
    string line;
    ifstream file;
    file.open("fly_data.txt", ios::in);

    if (file.is_open()) {
        while (line != "this_is_the_end_of_fly_data" && getline(file, line)) {
            switch (line[0]) {
                case 'e':
                    parseEmployee(line);
                    break;
                case 'c':
                    parseCustomer(line);
                    break;
                case 'r':
                    parseReservation(line);
                    break;
                case 'p':
                    parsePlane(line);
                    break;
                case 'f':
                    parseFlight(line);
                    break;
                default:
                    break;
            }
        }
        file.close();
    }
}

Employee *FlyData::getEmployee(const string& id) {
    for (auto &employee : this->employees) {
        if (employee->getID() == id) {
            return employee;
        }
    }
    return nullptr;
}

Reservation *FlyData::getReservation(const string& id) {
    for (auto &reservation : this->reservations) {
        if (reservation->getID() == id) {
            return reservation;
        }
    }
    return nullptr;
}

Flight *FlyData::getFlight(const string& id) {
    for (auto &flight : this->flights) {
        if (flight->getID() == id) {
            return flight;
        }
    }
    return nullptr;
}

Plane *FlyData::getPlane(const string& id) {
    for (auto &plane : this->planes) {
        if (plane->getID() == id) {
            return plane;
        }
    }
    return nullptr;
}

Customer *FlyData::getCustomer(const string& id) {
    for (auto &customer : this->customers) {
        if (customer->getID() == id) {
            return customer;
        }
    }
    return nullptr;
}

Plane *FlyData::getAvailablePlane(const string& flightID, int modelNum, Date &date) {
    for (auto &plane : this->planes) {
        if (plane->getModelNumber() == modelNum && !this->isPlaneBusy(modelNum, date)) {
            this->addFlightPlane(flightID, plane);
            return plane;
        }
    }
    throw "no available plane";
}

list<Reservation *> FlyData::getReservationsOfCustomer(const string &customerID) {
    list<Reservation *> reservations;
    for (auto &reservation : this->reservations) {
        if (customerID == reservation->getCustomer()->getID()) {
            reservations.push_back(reservation);
        }
    }
    return reservations;
}

list<Reservation *> FlyData::getReservationsOfFlight(const string &flightID) {
    list<Reservation *> reservations;
    for (auto &reservation : this->reservations) {
        if (flightID == reservation->getFlight()->getID()) {
            reservations.push_back(reservation);
        }
    }
    return reservations;
}

void FlyData::addReservation(Reservation *reservation) {
    this->reservations.push_back(reservation);
}

void FlyData::addEmployee(Employee *employee) {
    this->employees.push_back(employee);
}

void FlyData::addPlane(Plane *plane) {
    this->planes.push_back(plane);
}

void FlyData::addFlight(Flight *flight) {
    this->flights.push_back(flight);
}

void FlyData::addCustomer(Customer *customer) {
    this->customers.push_back(customer);
}

void FlyData::addFlightPlane(const string& flightID, Plane* plane) {
    this->mapFlightsPlanes.insert(pair<string, Plane*>(flightID, plane));
}

bool FlyData::isEmployeeBusy(Employee *employee, Date date) {
    // check if this employee already exits in other flight in this day
    for (auto &flight : this->flights) {
        if(flight->getDate()==date) {
            for (auto &emp : flight->getAssignedCrew()) {
                if (employee->getID() == emp->getID()) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool FlyData::isPlaneBusy(int planeModel, Date date) {
    int countModel = 0;
    int countBusy = 0;

    // count all the planes of this model
    for (auto &plane : this->planes) {
        if (plane->getModelNumber() == planeModel) {
            countModel++;
        }
    }
    // decrease all the busy planes of this model
    for (auto &flight : this->flights) {
        if (flight->getModelNumber() == planeModel && flight->getDate() == date) {
            countBusy++;
        }
    }
    // return true if all the planes of this model are busy
    return (countModel == countBusy);
}

void FlyData::checkFull(const string& flightID, Classes cls) {
    int numOrdered = 0;
    Flight *flight = this->getFlight(flightID);

    // init capacity according the class
    int capacity = 0;
    if (cls == FIRST_CLASS) {
        capacity = this->mapFlightsPlanes.at(flightID)->getMaxFirstClass();
    } else if (cls == SECOND_CLASS) {
        capacity = this->mapFlightsPlanes.at(flightID)->getMaxEconomyClass();
    }
    // check if ordered less then the max
    for (auto &reservation : flight->getReservations()) {
        if (reservation->getClass() == cls) {
            numOrdered++;
        }
    }
    if (capacity <= numOrdered) {
        throw "no more room";
    }
}

list<Employee*> FlyData::assignCrew(Flight* flight) {
    // id, model and date of flight
    string flightID = flight->getID();
    int flightModel = flight->getModelNumber();
    Date flightDate = flight->getDate();

    // ret assigned crew employees list
    list<Employee *> assignedCrew;

    // num of employees needed at each job
    map<Jobs, int> crewNeeded = this->getAvailablePlane(flightID, flightModel, flightDate)->getCrewNeeded();

    int numOfJob;
    for (auto &c : crewNeeded) {
        numOfJob = c.second;
        // search for enough not busy employees at this job
        for (auto &employee : this->employees) {
            if (numOfJob <= 0) {
                break;
            }
            if (employee->getTitle() == c.first && !this->isEmployeeBusy(employee, flight->getDate())) {
                assignedCrew.push_back(employee);
                numOfJob--;
            }
        }
        // case not enough not busy employees at a job
        if (numOfJob > 0) {
            throw "not enough employees";
        }
    }
    return assignedCrew;
}

FlyData::~FlyData() {
    // free all objects
    for (auto &employee : this->employees) { delete employee; }
    for (auto &plane : this->planes) { delete plane; }
    for (auto &reservation : this->reservations) { delete reservation; }
    for (auto &customer : this->customers) { delete customer; }
    for (auto &flight : this->flights) { delete flight; }
}
