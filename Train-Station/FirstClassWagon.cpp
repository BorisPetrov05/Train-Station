#include "FirstClassWagon.h"

FirstClassWagon::FirstClassWagon(const String& id, int seatCount, double basePrice, double comfortFactor, bool foodIncluded)
	: Wagon(id, seatCount, basePrice), comfortFactor(comfortFactor), foodIncluded(foodIncluded)
{

}

FirstClassWagon::FirstClassWagon(const FirstClassWagon& other)
	: Wagon(other), comfortFactor(other.comfortFactor), foodIncluded(other.foodIncluded)
{

}

FirstClassWagon& FirstClassWagon::operator=(const FirstClassWagon& other)
{
    if (this != &other) {
        Wagon::operator=(other);
        comfortFactor = other.comfortFactor;
        foodIncluded = other.foodIncluded;
    }
    return *this;
}

FirstClassWagon::FirstClassWagon(FirstClassWagon&& other) noexcept
    : Wagon(std::move(other)), comfortFactor(other.comfortFactor), foodIncluded(other.foodIncluded)
{
    other.comfortFactor = 0.0;
    other.foodIncluded = false;
}

FirstClassWagon& FirstClassWagon::operator=(FirstClassWagon&& other) noexcept
{
    if (this != &other) {
        Wagon::operator=(std::move(other));
        comfortFactor = other.comfortFactor;
        foodIncluded = other.foodIncluded;

        other.comfortFactor = 0.0;
        other.foodIncluded = false;
    }

    return *this;
}

FirstClassWagon::~FirstClassWagon()
{

}

double FirstClassWagon::getComfortFactor() const
{
    return comfortFactor;
}

bool FirstClassWagon::isFoodIncluded() const
{
    return foodIncluded;
}

double FirstClassWagon::calculatePrice(size_t seatIndex, double extra) const
{
    double price = getBasePrice() * comfortFactor;
    if (foodIncluded)
    {
        price += 50.0;
    }
    return price + extra;
}

void FirstClassWagon::print() const
{
    Wagon::print();
    std::cout << "Comfort Factor: " << comfortFactor << std::endl;
    std::cout << "Food Included: " << (foodIncluded ? "Yes" : "No") << std::endl;
    std::cout << "|01 02|" << std::endl;
    std::cout << "|03 04|" << std::endl;
    std::cout << "|05 06|" << std::endl;
    std::cout << "|07 08|" << std::endl;
    std::cout << "|09 10|" << std::endl;
}