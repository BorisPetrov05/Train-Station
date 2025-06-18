#pragma once
#include "Ticket.h"
#include "Station.h"
#include "FirstClassWagon.h"
#include "SecondClassWagon.h"
#include "SleepingWagon.h"
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
	User();
	User(const String& username, const String& password);
	User(const User& other);
	User& operator=(const User& other);
	User(User&& other) noexcept;
	User& operator=(User&& other) noexcept;
	~User();

	const String& getName() const;
	const String& getUsername() const;
	bool getIsLoggedIn() const;
	void setLoggedIn(bool status);
	void setUsername(const String& Username);
	void setPassword(const String& newPassword);

	void addTicket(const Ticket& ticket);
	const Vector<Ticket>& getTicket() const;
	void printTickets() const;

	void printStations(const Vector<Station> stations) const;
	void printSchedule(const Station& station, const Vector<Train>& trains) const;
	void printScheduleDestination(const Vector<Train>& trains, const Station& dest) const;
	void printScheduleAtTime(const Station& station, const String& date, const String& time, const Vector<Train>& trains) const;
	void printTrain(const Train& train) const;
	void printWagon(const Train& train, const Wagon& wagon) const;
	void buyTicket(const Train& train, const FirstClassWagon& wagon, const String& seatId, const String& ticketFileName);
	void buyTicket(const Train& train, const SecondClassWagon& wagon, const String& seatId, const String& ticketFileName, int luggageKg);
	void buyTicket(const Train& train, const SleepingWagon& wagon, const String& seatId, const String& ticketFileName);

	bool login(const String& username, const String& password);
	void logout();
};