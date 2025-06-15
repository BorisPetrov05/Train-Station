#pragma once
#include "Wagon.h"

class SecondClassWagon : public Wagon
{
private:
    double baggagePricePerKg;

public:
    SecondClassWagon();
    SecondClassWagon(const SecondClassWagon& other);
    SecondClassWagon& operator=(const SecondClassWagon& other);
    SecondClassWagon(SecondClassWagon&& other) noexcept;
    SecondClassWagon& operator=(SecondClassWagon&& other) noexcept;
    ~SecondClassWagon();

    SecondClassWagon(const String& wagonId, double basePrice, double baggagePricePerKg);

    double getBaggagePricePerKg() const;

    double calculatePrice(size_t seatIndex, double weight = 0) const override;
    void print() const;
};