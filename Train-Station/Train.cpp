#include "Train.h"
#include "Wagon.h"
#include <iostream>

Train::Train(const String& id, const String& startStation, const String& dest,
    const String& dep, const String& arr, double dist, double speed, int platform)
    : trainID(id), startingStation(startStation), destination(dest),
    departureTime(dep), arrivalTime(arr), distance(dist), speed(speed),
    departurePlatform(platform)
{
}

Train::Train(const Train& other)
    : trainID(other.trainID), startingStation(other.startingStation),
    destination(other.destination), departureTime(other.departureTime),
    arrivalTime(other.arrivalTime), distance(other.distance),
    speed(other.speed), departurePlatform(other.departurePlatform),
    wagons(other.wagons)
{
}

Train& Train::operator=(const Train& other)
{
    if (this != &other)
    {
        trainID = other.trainID;
        startingStation = other.startingStation;
        destination = other.destination;
        departureTime = other.departureTime;
        arrivalTime = other.arrivalTime;
        distance = other.distance;
        speed = other.speed;
        departurePlatform = other.departurePlatform;
        wagons = other.wagons;
    }
    return *this;
}

Train::Train(Train&& other) noexcept
    : trainID(std::move(other.trainID)), startingStation(std::move(other.startingStation)),
    destination(std::move(other.destination)), departureTime(std::move(other.departureTime)),
    arrivalTime(std::move(other.arrivalTime)), distance(other.distance),
    speed(other.speed), departurePlatform(other.departurePlatform),
    wagons(std::move(other.wagons))
{
    other.distance = 0.0;
    other.speed = 0.0;
    other.departurePlatform = 0;
}

Train& Train::operator=(Train&& other) noexcept
{
    if (this != &other)
    {
        trainID = std::move(other.trainID);
        startingStation = std::move(other.startingStation);
        destination = std::move(other.destination);
        departureTime = std::move(other.departureTime);
        arrivalTime = std::move(other.arrivalTime);
        distance = other.distance;
        speed = other.speed;
        departurePlatform = other.departurePlatform;
        wagons = std::move(other.wagons);

        other.distance = 0.0;
        other.speed = 0.0;
        other.departurePlatform = 0;
    }
    return *this;
}

Train::~Train()
{
    for (size_t i = 0; i < wagons.size(); ++i)
    {
        delete wagons[i];
    }
    wagons.clear();
}

const String& Train::getID() const
{
    return trainID;
}

const String& Train::getStartingStation() const
{
    return startingStation;
}

const String& Train::getDestination() const
{
    return destination;
}

const String& Train::getDepartureTime() const
{
    return departureTime;
}

const String& Train::getArrivalTime() const
{
    return arrivalTime;
}

double Train::getDistance() const
{
    return distance;
}

double Train::getSpeed() const
{
    return speed;
}

int Train::getDeparturePlatform() const
{
    return departurePlatform;
}

const Vector<Wagon*>& Train::getWagons() const
{
    return wagons;
}

void Train::addWagon(Wagon* wagon)
{
    if (wagon != nullptr)
    {
        wagons.push_back(wagon);
    }
}

void Train::removeWagon(const String& wagonId)
{
    for (size_t i = 0; i < wagons.size(); ++i)
    {
        if (wagons[i]->getID() == wagonId)
        {
            delete wagons[i];
            wagons.erase(i);
            return;
        }
    }
}
Wagon* Train::findWagon(const String& wagonId)
{
    for (size_t i = 0; i < wagons.size(); ++i)
    {
        if (wagons[i]->getID() == wagonId)
            return wagons[i];
    }
    return nullptr;
}

void Train::print() const
{
    std::cout << "===Train ID: " << trainID.c_str() << "===" << std::endl;
    std::cout << "Starting Station: " << startingStation.c_str() << std::endl;
    std::cout << "Destination: " << destination.c_str() << std::endl;
    std::cout << "Distance: " << distance << " km" << std::endl;
    std::cout << "Speed: " << speed << " km/h" << std::endl;
    std::cout << "Departure Time: " << departureTime.c_str() << std::endl;
    std::cout << "Arrival Time: " << arrivalTime.c_str() << std::endl;
    std::cout << "Departure Platform: " << departurePlatform << std::endl;
    std::cout << std::endl;
    std::cout << "Wagons:" << std::endl;

    const Vector<Wagon*>& wagons = this->getWagons();
    for (size_t i = 0; i < wagons.size(); i++)
    {
        std::cout << "  Wagon " << (i + 1) << " - ID: " << wagons[i]->getID() << std::endl;
        wagons[i]->print();
        std::cout << std::endl;
    }
}

double Train::calculateTotalPrice() const
{
    double total = 0.0;
    for (size_t i = 0; i < wagons.size(); i++)
    {
        if (wagons[i])
        {
            for (size_t seatIndex = 0; seatIndex < wagons[i]->getSeatCount(); ++seatIndex)
            {
                total += wagons[i]->calculatePrice(seatIndex, distance);
            }
        }
    }
    return total;
}

size_t Train::getTotalSeats() const
{
    size_t totalSeats = 0;
    for (size_t i = 0; i < wagons.size(); i++)
    {
        if (wagons[i])
        {
            totalSeats += wagons[i]->getSeatCount();
        }
    }
    return totalSeats;
}