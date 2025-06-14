#pragma once
#include "String.h"
#include "Vector.h"
#include "Train.h"

class Station
{
private:
    String name;
    Vector<Train*> departures;
    Vector<Train*> arrivals;

public:
    Station(const String& name);

    Station(const Station& other);
    Station& operator=(const Station& other);
    Station(Station&& other) noexcept;
    Station& operator=(Station&& other) noexcept;
    ~Station();

    const String& getName() const;
    const Vector<Train*>& getDepartures() const;
    const Vector<Train*>& getArrivals() const;

    void addDeparture(Train* train);
    void addArrival(Train* train);
    void removeDeparture(const String& trainID);
    void removeArrival(const String& trainID);
};