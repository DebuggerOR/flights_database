
#ifndef MY_FLIGHT_H
#define MY_FLIGHT_H

#include "FlyData.h"

class MyFlight : public Flight {
    string id;
    int modelNumber;
    Date date;
    string source;
    string destination;
    FlyData* flyData;
    list<Employee*> assignedCrew;

public:
    MyFlight(int modelNumber, Date date, const string& source, const string& destination, FlyData* flyData);

    MyFlight(const string& id, int modelNumber, Date date, const string& source, const string& destination, FlyData* flyData);

    ~MyFlight() override;

    int getModelNumber() override;

    list<Reservation *> getReservations() override;

    list<Employee *> getAssignedCrew() override;

    Date getDate() override;

    string getSource() override;

    string getDestination() override;

    string getID() override;
};

#endif
