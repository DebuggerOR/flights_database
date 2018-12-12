
#ifndef MY_EMPLOYEE_H
#define MY_EMPLOYEE_H

#include "interface.h"
#include "FlyData.h"

class MyEmployee : public Employee {
    string id;
    int seniority;
    int birthYear;
    string employerID;
    Jobs title;
    FlyData *flyData;

public:
    MyEmployee(int seniority, int birthYear, const string& employerID, Jobs title, FlyData *flyData);

    MyEmployee(const string& id, int seniority, int birthYear, const string& employerID, Jobs title, FlyData *flyData);

    ~MyEmployee() override;

    int getSeniority() override;

    int getBirthYear() override;

    Employee *getEmployer() override;

    Jobs getTitle() override;

    string getID() override;
};

#endif