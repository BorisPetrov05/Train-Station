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

    const String& getName() const;

    const Vector<Train*>& getDepartures();
    const Vector<Train*>& getArrivals();
};
