#include "User.h"
#include <iostream>
#include <string> //only for std::stoi

User::User() : isLoggedIn(false)
{

}

User::User(const String& username, const String& password)
	: username(username), password(password), isLoggedIn(false)
{

}

User::User(const User& other)
	: username(other.username), password(other.password), isLoggedIn(other.isLoggedIn), tickets(other.tickets)
{

}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		username = other.username;
		password = other.password;
		isLoggedIn = other.isLoggedIn;
		tickets = other.tickets;
	}
	return *this;
}

User::User(User&& other) noexcept
	: username(std::move(other.username)), password(std::move(other.password)), isLoggedIn(other.isLoggedIn), tickets(std::move(other.tickets))
{
	other.isLoggedIn = false;
}

User& User::operator=(User&& other) noexcept
{
	if (this != &other)
	{
		username = std::move(other.username);
		password = std::move(other.password);
		isLoggedIn = other.isLoggedIn;
		tickets = std::move(other.tickets);

		other.isLoggedIn = false;
	}
	return *this;
}

User::~User()
{

}

const String& User::getName() const
{
	return username;
}

const String& User::getUsername() const
{
	return username;
}

bool User::getIsLoggedIn() const
{
	return isLoggedIn;
}

void User::setLoggedIn(bool status)
{
	isLoggedIn = status;
}

void User::setPassword(const String& newPassword)
{
	password = newPassword;
}

void User::addTicket(const Ticket& ticket)
{
	tickets.push_back(ticket);
}

const Vector<Ticket>& User::getTicket() const
{
	return tickets;
}

void User::printTickets() const
{
	if (tickets.empty())
	{
		std::cout << "No tickets found." << std::endl;
		return;
	}

	std::cout << "Your tickets: " << std::endl;
	for (size_t i = 0; i < tickets.size(); i++)
	{
		std::cout << "Ticket " << (i + 1) << std::endl;
		tickets[i].print();
		std::cout << std::endl;
	}
}

void User::printStations(const Vector<Station> stations) const
{
	std::cout << "Available stations: " << std::endl;
	for (size_t i = 0; i < stations.size(); i++)
	{
		std::cout << (i + 1) << ". ";
		std::cout << stations[i].getName() << std::endl;
	}
}

void User::printSchedule(const Station& station, const Vector<Train>& trains) const
{
	std::cout << "=== Schedule for station " << station.getName() << " ===" << std::endl;
	std::cout << std::endl;

	// Print Arrivals
	std::cout << "Arrivals:" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "| Arrival Time  | Arrival Platform | Train ID | Starting station | Status |" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	for (size_t i = 0; i < trains.size(); i++)
	{
		if (trains[i].getDestination() == station.getName())
		{
			std::cout << "| " << trains[i].getArrivalTime() << " | "
				<< trains[i].getDeparturePlatform() << " | "
				<< trains[i].getID() << " | "
				<< trains[i].getStartingStation() << " | "
				<< "On Time |" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	// Print Departures
	std::cout << "Departures:" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "| Departure Time | Arrival Time | Destination | Departure Platform | Train ID | Status |" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	for (size_t i = 0; i < trains.size(); i++)
	{
		if (trains[i].getStartingStation() == station.getName())
		{
			std::cout << "| " << trains[i].getDepartureTime() << " | "
				<< trains[i].getArrivalTime() << " | "
				<< trains[i].getDestination() << " | "
				<< trains[i].getDeparturePlatform() << " | "
				<< trains[i].getID() << " | "
				<< "On Time |" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
}

void User::printScheduleDestination(const Vector<Train>& trains, const Station& dest) const
{
	std::cout << "Trains to destination: " << dest.getName() << std::endl;

	for (size_t i = 0; i < trains.size(); ++i)
	{
		trains[i].print();
	}
}

void User::printScheduleAtTime(const Station& station, const String& date, const String& time, const Vector<Train>& trains) const
{
	std::cout << "=== Schedule for station " << station.getName() << " ===" << std::endl;
	std::cout << "Date: " << date.c_str() << ", Time: " << time.c_str() << std::endl;
	std::cout << std::endl;

	// Print Arrivals
	std::cout << "Arrivals:" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "| Arrival Time  | Arrival Platform | Train ID | Starting station | Status |" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	auto isTimeAfterOrEqual = [](const String& trainTime, const String& filterTime) -> bool 
		{
		return strcmp(trainTime.c_str(), filterTime.c_str()) >= 0;
		};

	for (size_t i = 0; i < trains.size(); i++)
	{
		if (trains[i].getDestination() == station.getName() &&
			isTimeAfterOrEqual(trains[i].getArrivalTime(), time))
		{
			std::cout << "| " << trains[i].getArrivalTime() << " | "
				<< trains[i].getDeparturePlatform() << " | "
				<< trains[i].getID() << " | "
				<< trains[i].getStartingStation() << " | "
				<< "On Time |" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	// Print Departures
	std::cout << "Departures:" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "| Departure Time | Arrival Time | Destination | Departure Platform | Train ID | Status |" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;

	for (size_t i = 0; i < trains.size(); i++)
	{
		if (trains[i].getStartingStation() == station.getName() &&
			isTimeAfterOrEqual(trains[i].getDepartureTime(), time))
		{
			std::cout << "| " << trains[i].getDepartureTime() << " | "
				<< trains[i].getArrivalTime() << " | "
				<< trains[i].getDestination() << " | "
				<< trains[i].getDeparturePlatform() << " | "
				<< trains[i].getID() << " | "
				<< "On Time |" << std::endl;
		}
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
}

void User::printWagon(const Train& train, const Wagon& wagon) const
{
	std::cout << "Train: ";
	train.print();
	std::cout << "Wagon: ";
	std::cout << "=== Wagon ID: " << wagon.getID() << " ===" << std::endl;
	wagon.print();
}

//FirstClass
void User::buyTicket(const Train& train, const FirstClassWagon& wagon, const String& seatId, const String& ticketFileName)
{
	if (!isLoggedIn)
	{
		std::cout << "Please log in to buy tickets." << std::endl;
		return;
	}

	double basePrice = wagon.getBasePrice();
	double finalPrice = basePrice * wagon.getComfortFactor();

	if (wagon.isFoodIncluded())
	{
		finalPrice += 10.0;
	}

	Ticket newTicket(train.getID(), wagon.getID(), std::stoi(seatId.c_str()), finalPrice);
	addTicket(newTicket);

	std::cout << "First Class ticket purchased successfully!" << std::endl;
	std::cout << "Final price: " << finalPrice << " lv." << std::endl;

	// saveTicketToFile(newTicket, ticketFileName);
}

//SecondClass
void User::buyTicket(const Train& train, const SecondClassWagon& wagon, const String& seatId, const String& ticketFileName, int luggageKg)
{
	if (!isLoggedIn)
	{
		std::cout << "Please log in to buy tickets." << std::endl;
		return;
	}


	double basePrice = wagon.getBasePrice();
	double luggagePrice = wagon.getBaggagePricePerKg();

	double finalPrice = basePrice + luggagePrice * luggageKg;

	Ticket newTicket(train.getID(), wagon.getID(), std::stoi(seatId.c_str()), finalPrice);
	addTicket(newTicket);

	std::cout << "Second Class ticket purchased successfully!" << std::endl;
	std::cout << "Final price: " << finalPrice << " lv." << std::endl;

	// saveTicketToFile(newTicket, ticketFileName);
}

//SleepingWagon
void User::buyTicket(const Train& train, const SleepingWagon& wagon, const String& seatId, const String& ticketFileName)
{
	if (!isLoggedIn)
	{
		std::cout << "Please log in to buy tickets." << std::endl;
		return;
	}

	double basePrice = wagon.getBasePrice();
	double priceFor100km = wagon.getPricePer100km();
	double distance = train.getDistance();

	double finalPrice = basePrice + (priceFor100km / 100.0) * distance;

	Ticket newTicket(train.getID(), wagon.getID(), std::stoi(seatId.c_str()), finalPrice);
	addTicket(newTicket);

	std::cout << "Sleeping wagon ticket purchased successfully!" << std::endl;
	std::cout << "Final price: " << finalPrice << " lv." << std::endl;

	// saveTicketToFile(newTicket, ticketFileName);
}

bool User::login(const String& username, const String& password)
{
	if (this->username == username && this->password == password)
	{
		isLoggedIn = true;
		std::cout << "Login successful! Welcome back, " << username.c_str() << "!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void User::logout()
{
	if (isLoggedIn)
	{
		isLoggedIn = false;
		std::cout << "You have been logged out successfully." << std::endl;
	}
	else
	{
		std::cout << "You are not currently logged in." << std::endl;
	}
}