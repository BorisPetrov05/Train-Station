#include "SecondClassWagon.h"
#include <iostream>

SecondClassWagon::SecondClassWagon() : Wagon(String(""), 20, 0.0), baggagePricePerKg(0.0)
{
}

SecondClassWagon::SecondClassWagon(const SecondClassWagon& other)
    : Wagon(other), baggagePricePerKg(other.baggagePricePerKg)
{
}

SecondClassWagon& SecondClassWagon::operator=(const SecondClassWagon& other)
{
    if (this != &other)
    {
        Wagon::operator=(other);
        baggagePricePerKg = other.baggagePricePerKg;
    }
    return *this;
}

SecondClassWagon::SecondClassWagon(SecondClassWagon&& other) noexcept
    : Wagon(std::move(other)), baggagePricePerKg(other.baggagePricePerKg)
{
    other.baggagePricePerKg = 0.0;
}

SecondClassWagon& SecondClassWagon::operator=(SecondClassWagon&& other) noexcept
{
    if (this != &other)
    {
        Wagon::operator=(std::move(other));
        baggagePricePerKg = other.baggagePricePerKg;
        other.baggagePricePerKg = 0.0;
    }
    return *this;
}

SecondClassWagon::~SecondClassWagon()
{
}

SecondClassWagon::SecondClassWagon(const String& wagonId, int seatcount, double basePrice, double baggagePricePerKg)
    : Wagon(wagonId, 20, basePrice), baggagePricePerKg(baggagePricePerKg)
{
}

double SecondClassWagon::getBaggagePricePerKg() const
{
    return baggagePricePerKg;
}

double SecondClassWagon::calculatePrice(size_t seatIndex, double weight) const
{
    return basePrice + (baggagePricePerKg * weight);
}

void SecondClassWagon::print() const
{
    Wagon::print();
    std::cout << "Baggage Price per Kg: $" << baggagePricePerKg << std::endl;
    std::cout << "|01 02 03 04|" << std::endl;
    std::cout << "|05 06 07 08|" << std::endl;
    std::cout << "|09 10 11 12|" << std::endl;
    std::cout << "|13 14 15 16|" << std::endl;
    std::cout << "|17 18 19 20|" << std::endl;
}