#pragma once
#include "User.h"
#include "DiscountCard.h"
#include "Vector.hpp"
#include "Station.h"
#include "Train.h"

class Admin : public User
{
private:
    bool isAdmin = true;

public:
    Admin();
    Admin(const String& user, const String& pass);

    bool login(const String& user, const String& pass);
    void logout();

    void addTrain(Vector<Station*>& stations, const String& stationName,
        const String& destination, double distance, double speed,
        const String& departureDate, const String& departureTime);
    void removeTrain(String& trainId);
    void addWagon(String& trainId, String& wagonType, double basePrice);
    void removeWagon(String& trainId, String& wagonId);
    void moveWagon(String& sourceTrainId, String& wagonId, String& destinationTrainId);
    void createDiscountCard(String& discountType, String& name, int cardId, double discountPercent);
    bool validateDiscountCard(int cardId);

    bool isAuthenticated() const;
    String getUsername() const;
};