#pragma once
#include "String.h"

class Ticket
{
private:
    String trainID;
    String wagonID;
    size_t seatID;
    double price;

public:
    Ticket();
    Ticket(const String& trainID, const String& wagonID, size_t seatID, double price);
    Ticket(const Ticket& other);
    Ticket& operator=(const Ticket& other);
    Ticket(Ticket&& other) noexcept;
    Ticket& operator=(Ticket&& other) noexcept;
    ~Ticket();

    const String& getTrainID() const;
    const String& getWagonID() const;
    size_t getSeatID() const;
    double getPrice() const;

    void setPrice(double newPrice);

    void print() const;
    double applyDiscount(double discountPercent) const;
};