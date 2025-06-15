#include "Station.h"
#include "Train.h"

Station::Station(const String& name) : name(name)
{

}

Station::Station(const Station& other)
    : name(other.name), departures(other.departures), arrivals(other.arrivals)
{

}

Station& Station::operator=(const Station& other)
{
    if (this != &other) 
    {
        name = other.name;
        departures = other.departures;
        arrivals = other.arrivals;
    }
    return *this;
}

Station::Station(Station&& other) noexcept
    : name(std::move(other.name)), departures(std::move(other.departures)), arrivals(std::move(other.arrivals))
{

}

Station& Station::operator=(Station&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        departures = std::move(other.departures);
        arrivals = std::move(other.arrivals);
    }
    return *this;
}

Station::~Station()
{
    departures.clear();
    arrivals.clear();
}

const String& Station::getName() const
{
    return name;
}

const Vector<Train*>& Station::getDepartures() const
{
    return departures;
}

const Vector<Train*>& Station::getArrivals() const
{
    return arrivals;
}

void Station::addDeparture(Train* train)
{
    if (train != nullptr)
    {
        departures.push_back(train);
    }
}

void Station::addArrival(Train* train)
{
    if (train != nullptr)
    {
        arrivals.push_back(train);
    }
}

void Station::removeDeparture(const String& trainID)
{
    for (size_t i = 0; i < departures.size(); ++i)
    {
        if (departures[i] && departures[i]->getID() == trainID)
        {
            departures.erase(i);
            break;
        }
    }
}

void Station::removeArrival(const String& trainID)
{
    for (size_t i = 0; i < arrivals.size(); ++i) 
    {
        if (arrivals[i] && arrivals[i]->getID() == trainID) 
        {
            arrivals.erase(i);
            break;
        }
    }
}