#pragma once
#include "String.h"

class Wagon 
{
protected:
    String wagonId;
    int seatCount;
    double basePrice;

public:
    Wagon(const String& id, int seatCount, double basePrice);
    Wagon(const Wagon& other);
    Wagon& operator=(const Wagon& other);
    Wagon(Wagon&& other) noexcept;
    Wagon& operator=(Wagon&& other) noexcept;
    virtual ~Wagon();

    const String& getID() const;
    size_t getSeatCount() const;
    double getBasePrice() const;

    virtual double calculatePrice(size_t seatIndex, double extra = 0) const = 0;
    virtual void printLayout() const = 0;
};