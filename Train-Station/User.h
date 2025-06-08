#pragma once
#include "Ticket.h"
#include "Vector.h"
#include "String.h"
#include "Station.h"
#include <ctime>
#include <chrono>

class User
{
private:
	String username;
	String password;
	bool isLoggedIn;
	Vector<Ticket> tickets;

public:
	User() = default;
	User(const User& other) : tickets(other.tickets) {}
	~User() = default;
	User& operator=(const User& other);

	const String& getName() const;
	void addTicket(const Ticket& ticket);
	const Vector<Ticket>& getTicket() const;
	void printTickets() const;

	void printStations(Vector<Station> stations) const;
	void printSchedule(Station station) const;
	void printScheduleDestination(const Vector<Train> trains, Station dest) const;
	void printScheduleAtTime(Station station, const String& date, const String& time) const;
	void printTrain(Train train) const;
	void printWagon(Train train, Wagon wagon) const;
	void buyTicket(Train train, Wagon wagon, String seatId, String ticketFileName); //extra params needed for types of wagons
};