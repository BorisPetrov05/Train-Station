#include "DiscountCard.h"
#include <iostream>

DiscountCard::DiscountCard(const String& type, const String& name, int id, double discount)
    : cardType(type), holderName(name), cardId(id), discountPercent(discount)
{
}

DiscountCard::DiscountCard(const DiscountCard& other)
    : cardType(other.cardType), holderName(other.holderName), cardId(other.cardId), discountPercent(other.discountPercent)
{
}

DiscountCard& DiscountCard::operator=(const DiscountCard& other)
{
    if (this != &other)
    {
        cardType = other.cardType;
        holderName = other.holderName;
        cardId = other.cardId;
        discountPercent = other.discountPercent;
    }
    return *this;
}

DiscountCard::DiscountCard(DiscountCard&& other) noexcept
    : cardType(std::move(other.cardType)), holderName(std::move(other.holderName)),
    cardId(other.cardId), discountPercent(other.discountPercent)
{
    other.cardId = 0;
    other.discountPercent = 0.0;
}

DiscountCard& DiscountCard::operator=(DiscountCard&& other) noexcept
{
    if (this != &other)
    {
        cardType = std::move(other.cardType);
        holderName = std::move(other.holderName);
        cardId = other.cardId;
        discountPercent = other.discountPercent;

        other.cardId = 0;
        other.discountPercent = 0.0;
    }
    return *this;
}

DiscountCard::~DiscountCard()
{
}

const String& DiscountCard::getType() const
{
    return cardType;
}

const String& DiscountCard::getHolderName() const
{
    return holderName;
}

int DiscountCard::getCardId() const
{
    return cardId;
}

double DiscountCard::getDiscountPercent() const
{
    return discountPercent;
}

void DiscountCard::setDiscountPercent(double newDiscount)
{
    if (newDiscount >= 0.0 && newDiscount <= 100.0)
    {
        discountPercent = newDiscount;
    }
}

void DiscountCard::print() const
{
    std::cout << "Discount Card Information:" << std::endl;
    std::cout << "Card Type: " << cardType.c_str() << std::endl;
    std::cout << "Holder Name: " << holderName.c_str() << std::endl;
    std::cout << "Card ID: " << cardId << std::endl;
    std::cout << "Discount Percent: " << discountPercent << "%" << std::endl;
}

bool DiscountCard::isValid() const
{
    return cardId > 0 && discountPercent >= 0.0 && discountPercent <= 100.0
        && cardType.empty() && holderName.empty();
}

double DiscountCard::calculateDiscountAmount(double originalPrice) const
{
    if (originalPrice < 0.0 || !isValid())
    {
        return 0.0;
    }
    return originalPrice * (discountPercent / 100.0);
}