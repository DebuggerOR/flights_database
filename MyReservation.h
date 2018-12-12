
#ifndef MY_RESERVATION_H
#define MY_RESERVATION_H

#include "interface.h"
#include "FlyData.h"

class MyReservation : public Reservation {
    string id;
    string customerID;
    string flightID;
    Classes cls;
    int maxBaggage;
    FlyData *flyData;

public:
    MyReservation(const string& customerId, const string& flightID, Classes cls, int maxBaggage, FlyData *flyData);

    MyReservation(const string& id, const string& customerID, const string& flightID, Classes cls, int maxBaggage, FlyData *flyData);

    ~MyReservation() override;

    Customer *getCustomer() override;

    Flight *getFlight() override;

    Classes getClass() override;

    int getMaxBaggage() override;

    string getID() override;
};

#endif