#include "Train.h"
#include "Wagon.h"

Train::Train(const String& id, const String& dest, const String& dep,
    const String& arr, double dist, double speed)
    : trainID(id), destination(dest), departureTime(dep), arrivalTime(arr),
    distance(dist), speed(speed)
{
}

Train::Train(const Train& other)
    : trainID(other.trainID), destination(other.destination),
    departureTime(other.departureTime), arrivalTime(other.arrivalTime),
    distance(other.distance), speed(other.speed), wagons(other.wagons)
{

}

Train& Train::operator=(const Train& other)
{
    if (this != &other)
    {
        trainID = other.trainID;
        destination = other.destination;
        departureTime = other.departureTime;
        arrivalTime = other.arrivalTime;
        distance = other.distance;
        speed = other.speed;
        wagons = other.wagons;
    }
    return *this;
}

Train::Train(Train&& other) noexcept
    : trainID(std::move(other.trainID)), destination(std::move(other.destination)),
    departureTime(std::move(other.departureTime)), arrivalTime(std::move(other.arrivalTime)),
    distance(other.distance), speed(other.speed), wagons(std::move(other.wagons))
{
    other.distance = 0.0;
    other.speed = 0.0;
}

Train& Train::operator=(Train&& other) noexcept
{
    if (this != &other)
    {
        trainID = std::move(other.trainID);
        destination = std::move(other.destination);
        departureTime = std::move(other.departureTime);
        arrivalTime = std::move(other.arrivalTime);
        distance = other.distance;
        speed = other.speed;
        wagons = std::move(other.wagons);

        other.distance = 0.0;
        other.speed = 0.0;
    }
    return *this;
}

Train::~Train()
{

}

const String& Train::getID() const
{
    return trainID;
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
    for (size_t i = 0; i < wagons.size(); i++)
    {
        if (wagons[i] && wagons[i]->getID() == wagonId)
        {
            wagons.erase(i);
            break;
        }
    }
}

Wagon* Train::findWagon(const String& wagonId)
{
    for (size_t i = 0; i < wagons.size(); i++)
    {
        if (wagons[i] && wagons[i]->getID() == wagonId)
        {
            return wagons[i];
        }
    }
    return nullptr;
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