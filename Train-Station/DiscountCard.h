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
    DiscountCard(const DiscountCard& other);
    DiscountCard& operator=(const DiscountCard& other);
    DiscountCard(DiscountCard&& other) noexcept;
    DiscountCard& operator=(DiscountCard&& other) noexcept;
    ~DiscountCard();

    const String& getType() const;
    const String& getHolderName() const;
    int getCardId() const;
    double getDiscountPercent() const;

    void setDiscountPercent(double newDiscount);

    void print() const;
    bool isValid() const;
    double calculateDiscountAmount(double originalPrice) const;
};