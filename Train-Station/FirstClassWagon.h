#pragma once
#include "Wagon.h"

class FirstClassWagon : public Wagon 
{
    double comfortFactor;
    bool foodIncluded;

public:
    FirstClassWagon(const String& id, int seatCount, double basePrice, double comfortFactor, bool foodIncluded);
    FirstClassWagon(const FirstClassWagon& other);
    FirstClassWagon& operator=(const FirstClassWagon& other);
    FirstClassWagon(FirstClassWagon&& other) noexcept;
    FirstClassWagon& operator=(FirstClassWagon&& other) noexcept;
    virtual ~FirstClassWagon();

    double getComfortFactor() const;
    bool isFoodIncluded() const;

    virtual double calculatePrice(size_t seatIndex, double extra = 0) const override;

    virtual void printLayout() const override;
};