#pragma once
#include "Wagon.h"

class FirstClassWagon : public Wagon 
{
    double comfortFactor;
    bool foodIncluded;

public:
    FirstClassWagon(const String& id, double basePrice, double comfortFactor);

    void setFoodIncluded(bool included);

    double calculatePrice(size_t seatIndex, double extra = 0) const override;

    void printLayout() const override;
};