#include "Ticket.h"
#include <iostream>

Ticket::Ticket() : trainID(0), wagonID(0), seatID(0), price(0.0) 
{

}

Ticket::Ticket(const String& trainID, const String& wagonID, size_t seatID, double price)
    : trainID(trainID), wagonID(wagonID), seatID(seatID), price(price)
{

}

Ticket::Ticket(const Ticket& other)
    : trainID(other.trainID), wagonID(other.wagonID), seatID(other.seatID), price(other.price)
{

}

Ticket& Ticket::operator=(const Ticket& other)
{
    if (this != &other)
    {
        trainID = other.trainID;
        wagonID = other.wagonID;
        seatID = other.seatID;
        price = other.price;
    }
    return *this;
}

Ticket::Ticket(Ticket&& other) noexcept
    : trainID(std::move(other.trainID)), wagonID(std::move(other.wagonID)), seatID(other.seatID), price(other.price)
{
    other.seatID = 0;
    other.price = 0.0;
}

Ticket& Ticket::operator=(Ticket&& other) noexcept
{
    if (this != &other)
    {
        trainID = std::move(other.trainID);
        wagonID = std::move(other.wagonID);
        seatID = other.seatID;
        price = other.price;

        other.seatID = 0;
        other.price = 0.0;
    }
    return *this;
}

Ticket::~Ticket()
{
}

const String& Ticket::getTrainID() const
{
    return trainID;
}

const String& Ticket::getWagonID() const
{
    return wagonID;
}

size_t Ticket::getSeatID() const
{
    return seatID;
}

double Ticket::getPrice() const
{
    return price;
}

void Ticket::setPrice(double newPrice)
{
    if (newPrice >= 0.0)
    {
        price = newPrice;
    }
}

void Ticket::print() const
{
    std::cout << "Ticket Information:" << std::endl;
    std::cout << "Train ID: " << trainID.c_str() << std::endl;
    std::cout << "Wagon ID: " << wagonID.c_str() << std::endl;
    std::cout << "Seat ID: " << seatID << std::endl;
    std::cout << "Price: $" << price << std::endl;
}

double Ticket::applyDiscount(double discountPercent) const
{
    if (discountPercent < 0.0 || discountPercent > 100.0)
    {
        return price;
    }
    double discountAmount = price * (discountPercent / 100.0);
    return price - discountAmount;
}