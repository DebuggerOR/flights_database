
#ifndef MY_PLANE_H
#define MY_PLANE_H

#include "interface.h"
#include "FlyData.h"

class MyPlane: public Plane {
    string id;
    int modelNumber;
    map<Jobs, int> crewNeeded;
    map<Classes, int> maxPassengers;
    FlyData *flyData;

public:
    MyPlane(int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassengers, FlyData *flyData);

    MyPlane(string id, int model_number, map<Jobs, int> crewNeeded, map<Classes, int> maxPassengers,
            FlyData *flyData);

    ~MyPlane() override;

    int getModelNumber() override;

    map<Jobs, int> getCrewNeeded() override;

    int getMaxFirstClass() override;

    int getMaxEconomyClass() override;

    string getID() override;
};

#endif