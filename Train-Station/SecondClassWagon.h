#pragma once
#include "Wagon.h"

class SecondClassWagon : public Wagon 
{
    double baggagePricePerKg;

public:
    SecondClassWagon(const String& id, double basePrice, double baggagePricePerKg);

    double calculatePrice(size_t seatIndex, double baggageKg) const override;

    void printLayout() const override;
};
