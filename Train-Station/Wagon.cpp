#include "Wagon.h"

Wagon::Wagon(const String& id, int seatCount, double basePrice) : wagonId(id), seatCount(seatCount), basePrice(basePrice) 
{

}

Wagon::Wagon(const Wagon& other) : wagonId(other.wagonId), seatCount(other.seatCount), basePrice(other.basePrice)
{

}

Wagon& Wagon::operator=(const Wagon& other)
{
	if (this != &other)
	{
		this->wagonId = other.wagonId;
		this->basePrice = other.basePrice;
		this->seatCount = other.seatCount;
	}
	return *this;
}

Wagon::Wagon(Wagon&& other) noexcept : wagonId(std::move(other.wagonId)), seatCount(other.seatCount), basePrice(other.basePrice)
{
	other.seatCount = 0;
	other.basePrice = 0.00;
}

Wagon& Wagon::operator=(Wagon&& other) noexcept
{
	if (this != &other)
	{
		this->wagonId = std::move(other.wagonId);
		this->basePrice = other.basePrice;
		this->seatCount = other.seatCount;
		other.seatCount = 0;
		other.basePrice = 0.00;
	}

	return *this;
}

Wagon::~Wagon() 
{

}

const String& Wagon::getID() const
{
	return wagonId;
}
size_t Wagon::getSeatCount() const
{
	return seatCount;
}
double Wagon::getBasePrice() const
{
	return basePrice;
}

void Wagon::print() const
{
	std::cout << "Wagon ID: " << wagonId.c_str() << std::endl;
	std::cout << "Seat Count: " << seatCount << std::endl;
	std::cout << "Base Price: $" << basePrice << std::endl;
}