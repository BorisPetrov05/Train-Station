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
    Ticket(const String& trainID, const String& wagonID, size_t seatID, double price);

    void print() const;
};

