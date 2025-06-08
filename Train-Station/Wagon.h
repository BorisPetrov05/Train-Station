#pragma once
#include "String.h"

class Wagon 
{
protected:
    String wagonId;
    int seatCount;
    double basePrice;

public:
    Wagon(const String& id, int seatCount, double basePrice);
    virtual ~Wagon();

    const String& getID() const;
    size_t getSeatCount() const;
    double getBasePrice() const;

    virtual double calculatePrice(size_t seatIndex, double extra = 0) const = 0;
    virtual void printLayout() const = 0;
};