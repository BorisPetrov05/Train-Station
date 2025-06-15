#include "SleepingWagon.h"

SleepingWagon::SleepingWagon(const String& id, int seatCount, double basePrice, double pricePer100km) 
    : Wagon(id, seatCount, basePrice), pricePer100km(pricePer100km)
{

}

SleepingWagon::SleepingWagon(const SleepingWagon& other)
    : Wagon(other), pricePer100km(other.pricePer100km)
{

}

SleepingWagon& SleepingWagon::operator=(const SleepingWagon& other)
{
    if (this != &other) 
    {
        Wagon::operator=(other);
        pricePer100km = other.pricePer100km;
    }
    return *this;
}

SleepingWagon::SleepingWagon(SleepingWagon&& other) noexcept
    : Wagon(std::move(other)), pricePer100km(other.pricePer100km)
{
    other.pricePer100km = 0.0;
}

SleepingWagon& SleepingWagon::operator=(SleepingWagon&& other) noexcept
{
    if (this != &other) 
    {
        Wagon::operator=(std::move(other));
        pricePer100km = other.pricePer100km;

        other.pricePer100km = 0.0;
    }
    return *this;
}

SleepingWagon::~SleepingWagon()
{
    
}

double SleepingWagon::getPricePer100km() const
{
    return pricePer100km;
}

double SleepingWagon::calculatePrice(size_t seatIndex, double extra) const
{
    double distancePrice = (extra / 100.0) * pricePer100km;
    return getBasePrice() + distancePrice;
}

void SleepingWagon::print() const
{
    Wagon::print();
    std::cout << "Price per 100km: $" << pricePer100km << std::endl;
    std::cout << "|Bed 01|" << std::endl;
    std::cout << "|Bed 02|" << std::endl;
    std::cout << "|Bed 03|" << std::endl;
    std::cout << "|Bed 04|" << std::endl;
    std::cout << "|Bed 05|" << std::endl;
}