#pragma once
#include "Wagon.h"

class SleepingWagon : public Wagon 
{
    double pricePer100km;

public:
    SleepingWagon(const String& id, double basePrice, double pricePer100km);

    double calculatePrice(size_t seatIndex, double distance) const override;

    void printLayout() const override;
};