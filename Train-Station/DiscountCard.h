#pragma once
#include "String.h"

class DiscountCard
{
private:
    String cardType;
    String holderName;
    int cardId;
    double discountPercent;

public:
    DiscountCard(const String& type, const String& name, int id, double discount);
    String getType() const { return cardType; }
    String getHolderName() const { return holderName; }
    int getCardId() const { return cardId; }
    double getDiscountPercent() const { return discountPercent; }

    void print() const;
};