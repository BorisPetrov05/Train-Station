#pragma once
#include "String.h"
#include "Vector.h"
#include "Wagon.h"

class Train
{
private:
    String trainID;
    String startingStation;
    String destination;
    String departureTime;
    String arrivalTime;
    double distance;
    double speed;
    int departurePlatform;
    Vector<Wagon*> wagons;

public:
    Train(const String& id, const String& startStation, const String& dest,
        const String& dep, const String& arr, double dist, double speed, int platform = 1);
    Train(const Train& other);
    Train& operator=(const Train& other);
    Train(Train&& other) noexcept;
    Train& operator=(Train&& other) noexcept;
    ~Train();

    const String& getID() const;
    const String& getStartingStation() const;
    const String& getDestination() const;
    const String& getDepartureTime() const;
    const String& getArrivalTime() const;
    double getDistance() const;
    double getSpeed() const;
    int getDeparturePlatform() const;

    const Vector<Wagon*>& getWagons() const;
    void addWagon(Wagon* wagon);
    void removeWagon(const String& wagonId);
    Wagon* findWagon(const String& wagonId);

    void print() const;
    double calculateTotalPrice() const;
    size_t getTotalSeats() const;
};