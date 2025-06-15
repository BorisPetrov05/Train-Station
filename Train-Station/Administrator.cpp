#include "Administrator.h"
#include "FirstClassWagon.h"
#include "SecondClassWagon.h"
#include "SleepingWagon.h"
#include <iostream>
#include <cstdlib>
#include <string> //only for std::to_string()

Admin::Admin() : User(), isAdmin(true)
{

}

Admin::Admin(const String& username, const String& password)
    : User(username, password), isAdmin(true)
{

}

bool Admin::login(const String& username, const String& password)
{
    if (User::login(username, password))
    {
        isAdmin = true;
        std::cout << "Admin login successful! Welcome, " << username.c_str() << "!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error: Invalid admin credentials!" << std::endl;
        isAdmin = false;
        return false;
    }
}

void Admin::logout()
{
    if (isAuthenticated())
    {
        User::logout();
        isAdmin = false;
        std::cout << "Admin logged out successfully." << std::endl;
    }
    else
    {
        std::cout << "Admin is not currently logged in." << std::endl;
    }
}

void Admin::addTrain(Vector<Station*>& stations, const String& stationName,
    const String& destination, double distance, double speed,
    const String& departureDate, const String& departureTime)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return;
    }

    Station* startStation = nullptr;
    Station* destStation = nullptr;

    for (size_t i = 0; i < stations.size(); i++)
    {
        if (stations[i]->getName() == stationName)
            startStation = stations[i];
        if (stations[i]->getName() == destination)
            destStation = stations[i];
    }

    if (!startStation || !destStation)
    {
        std::cout << "Error: One or both stations do not exist." << std::endl;
        return;
    }

    static int trainCounter = 1000;
    String newTrainId = String("T") + String(std::to_string(trainCounter++).c_str());

    double travelTimeHours = distance / speed;
    int travelHours = (int)travelTimeHours;
    int travelMinutes = (int)((travelTimeHours - travelHours) * 60);

    const char* depTimeStr = departureTime.c_str();
    int depHour = 0;
    int depMinute = 0;

    char* endPtr;
    depHour = std::strtol(depTimeStr, &endPtr, 10);
    if (*endPtr == ':')
    {
        depMinute = std::strtol(endPtr + 1, nullptr, 10);
    }

    int arrHour = depHour + travelHours;
    int arrMinute = depMinute + travelMinutes;

    if (arrMinute >= 60)
    {
        arrHour++;
        arrMinute -= 60;
    }

    char arrTimeBuffer[10];
    std::sprintf(arrTimeBuffer, "%02d:%02d", arrHour, arrMinute);
    String arrivalTime(arrTimeBuffer);

    Train* newTrain = new Train(newTrainId, stationName, destination,
        departureTime, arrivalTime, distance, speed, 1);

    startStation->addDeparture(newTrain);
    destStation->addArrival(newTrain);

    std::cout << "Train added successfully!" << std::endl;
    std::cout << "Train ID: " << newTrainId.c_str() << std::endl;
    std::cout << "Route: " << stationName.c_str() << " -> " << destination.c_str() << std::endl;
    std::cout << "Departure: " << departureTime.c_str() << std::endl;
    std::cout << "Arrival: " << arrivalTime.c_str() << std::endl;
}

void Admin::removeTrain(String& trainId)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return;
    }

}

void Admin::addWagon(String& trainId, String& wagonType, double basePrice)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return;
    }

    //need global train system
    static int wagonCounter = 1;
    String newWagonId = String("W") + String(std::to_string(wagonCounter++).c_str());
    Wagon* wagon = nullptr;

    if (wagonType == String("first") || wagonType == String("FirstClass"))
    {
        wagon = new FirstClassWagon(newWagonId, 50, basePrice, 1.5, true);
        std::cout << "First Class wagon created successfully!" << std::endl;
    }
    else if (wagonType == String("second") || wagonType == String("SecondClass"))
    {
        wagon = new SecondClassWagon(newWagonId, basePrice, 2.0);
        std::cout << "Second Class wagon created successfully!" << std::endl;
    }
    else if (wagonType == String("sleeping") || wagonType == String("Sleeping"))
    {
        wagon = new SleepingWagon(newWagonId, 30, basePrice, 5.0);
        std::cout << "Sleeping wagon created successfully!" << std::endl;
    }
    else
    {
        std::cout << "Error: Invalid wagon type. Use 'first', 'second', or 'sleeping'." << std::endl;
        return;
    }

    std::cout << "Wagon ID: " << newWagonId.c_str() << std::endl;
    std::cout << "Base Price: " << basePrice << " lv." << std::endl;
    //Note: Wagon created but needs to be added to train "

    delete wagon;
}

void Admin::removeWagon(String& trainId, String& wagonId)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return;
    }

    //need global wagon storage system
}

void Admin::moveWagon(String& sourceTrainId, String& wagonId, String& destinationTrainId)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return;
    }

    
    //need global train system
}

void Admin::createDiscountCard(String& discountType, String& name, int cardId, double discountPercent)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return;
    }

    //need global discountcard system
}

bool Admin::validateDiscountCard(int cardId)
{
    if (!isAuthenticated())
    {
        std::cout << "Error: Admin authentication required." << std::endl;
        return false;
    }

    //Need global storage system
    return false;
}

bool Admin::isAuthenticated() const
{
    return isAdmin && getIsLoggedIn();
}

String Admin::getUsername() const
{
    return User::getUsername();
}