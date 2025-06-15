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
	: username(std::move(other.username)), password(std::move(other.password)), isLoggedIn(std::move(other.isLoggedIn)), tickets(std::move(other.tickets))
{
	other.isLoggedIn = false;
}

User& User::operator=(User&& other) noexcept
{
	if (this != &other)
	{
		username = other.username;
		password = other.password;
		isLoggedIn = other.isLoggedIn;
		tickets = other.tickets;

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

//probably to be fixed
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

void User::printSchedule(const Station& station) const
{
	std::cout << "Schedule for station: ";
	//to be made
}

void User::printScheduleDestination(const Vector<Train>& trains, const Station& dest) const
{
	std::cout << "Trains to destination: " << dest.getName() << std::endl;

	for (size_t i = 0; i < trains.size(); ++i)
	{
		//trains[i].print(); //to be made
	}
}

void User::printScheduleAtTime(const Station& station, const String& date, const String& time) const
{
	std::cout << "Schedule for station: ";
	//station.print();
	std::cout << "Date: " << date.c_str() << ", Time: " << time.c_str() << std::endl;
	//to be made
}

void User::printTrain(const Train& train) const
{
	//train.print(); //to be made
}

void User::printWagon(const Train& train, const Wagon& wagon) const
{
	std::cout << "Train: ";
	//train.print();
	std::cout << "Wagon: ";
	//wagon.print();
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
        finalPrice += 50.0;
    }
    
    Ticket newTicket(train.getID(), wagon.getID(), std::stoi(seatId.c_str()), finalPrice);
    addTicket(newTicket);
    
    std::cout << "First Class ticket purchased successfully!" << std::endl;
    std::cout << "Final price: $" << finalPrice << std::endl;
    
    // saveTicketToFile(newTicket, ticketFileName);
}

//SecondClass
void User::buyTicket(const Train& train, const SecondClassWagon& wagon, const String& seatId, const String& ticketFileName)
{
	
}