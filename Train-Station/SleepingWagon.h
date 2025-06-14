#pragma once
#include "Wagon.h"
#include <iostream>

class SleepingWagon : public Wagon
{
private:
    double pricePer100km;

public:
    SleepingWagon(const String& id, int seatCount, double basePrice, double pricePer100km);
    SleepingWagon(const SleepingWagon& other);
    SleepingWagon& operator=(const SleepingWagon& other); 
    SleepingWagon(SleepingWagon&& other) noexcept;
    SleepingWagon& operator=(SleepingWagon&& other) noexcept;
    virtual ~SleepingWagon();

    double getPricePer100km() const;

    virtual double calculatePrice(size_t seatIndex, double extra = 0) const override;
    virtual void printLayout() const override;
};