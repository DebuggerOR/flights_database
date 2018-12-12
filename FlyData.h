
#ifndef FLY_DATA_H
#define FLY_DATA_H

#include "interface.h"

class FlyData {
    list<Reservation *> reservations;
    list<Employee *> employees;
    list<Flight *> flights;
    list<Plane *> planes;
    list<Customer *> customers;
    map<string, Plane *> mapFlightsPlanes;

public:
    ~FlyData();

    void addReservation(Reservation *reservation);

    void addEmployee(Employee *reservation);

    void addPlane(Plane *reservation);

    void addFlight(Flight *reservation);

    void addCustomer(Customer *reservation);

    list<Reservation *> getReservationsOfFlight(const string &flightID);

    list<Reservation *> getReservationsOfCustomer(const string &customerID);

    Employee *getEmployee(const string& id);

    Reservation *getReservation(const string& id);

    Flight *getFlight(const string& id);

    Plane *getPlane(const string& id);

    Customer *getCustomer(const string& id);

    Plane *getAvailablePlane(const string& flightID, int modelNum, Date &date);

    bool isEmployeeBusy(Employee *employee, Date date);

    bool isPlaneBusy(int planeModel, Date date);

    void checkFull(const string& flightID, Classes cls);

    list<Employee *> assignCrew(Flight *flight);

    void addFlightPlane(const string& flightID, Plane *plane);

    void saveData();

    void loadData();

private:
    void parseEmployee(const string& line);

    void parseReservation(const string& line);

    void parseFlight(const string& line);

    void parsePlane(const string& line);

    void parseCustomer(const string& line);
};

#endif
