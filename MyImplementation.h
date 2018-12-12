
#ifndef MY_IMPLEMENTATION_H
#define MY_IMPLEMENTATION_H

#include <iostream>
#include "FlyData.h"

class MyImplementation : public Ex2 {
    bool dataLoaded;
    FlyData flyData;

public:
    MyImplementation();

    ~MyImplementation();

    Employee *addEmployee(int seniority, int birthYear, string employerID, Jobs title) override;

    Employee *getEmployee(string id) override;

    Plane *addPlane(int modelNumber, map<Jobs, int> crewNeeded, map<Classes, int> maxPassangers) override;

    Plane *getPlane(string id) override;

    Flight *addFlight(int modelNumber, Date date, string source, string destination) override;

    Flight *getFlight(string id) override;

    Customer *addCustomer(string fullName, int priority) override;

    Customer *getCustomer(string id) override;

    //typo
    Reservation *addResevation(string customerID, string flightID, Classes cls, int maxBaggage) override;

    Reservation *getReservation(string id) override;

    void exit() override;

private:
    void loadData();
};

#endif