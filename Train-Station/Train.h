#pragma once
#include "String.h"
#include "Vector.h"
#include "Wagon.h"

class Train 
{
    String trainID;
    String destination;
    String departureTime;
    String arrivalTime;
    double distance;
    double speed;
    Vector<Wagon*> wagons;

public:
    Train(const String& id, const String& dest, const String& dep, const String& arr, double dist, double speed)
        : trainID(id), destination(dest), departureTime(dep), arrivalTime(arr), distance(dist), speed(speed) {}

    const String& getID() const { return trainID; }
    const String& getDestination() const { return destination; }
    const Vector<Wagon*>& getWagons() const { return wagons; }

    void addWagon(Wagon* w) { wagons.push_back(w); }
    void removeWagon(const String& wagonId);
    Wagon* findWagon(const String& wagonId);
};