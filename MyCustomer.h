
#ifndef MY_CUSTOMER_H
#define MY_CUSTOMER_H

#include "FlyData.h"

class MyCustomer : public Customer {
    string id;
    int priority;
    string name;
    FlyData *flyData;

public:
    MyCustomer(const string& name, int priority, FlyData *flyData);

    MyCustomer(const string& id, const string& name, int priority, FlyData *flyData);

    ~MyCustomer() override;

    string getFullName() override;

    int getPriority() override;

    list<Reservation *> getReservations() override;

    string getID() override;
};

#endif