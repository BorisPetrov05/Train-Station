/*
* commands:
print-stations
print-schedule <station>
print-schedule - destination <station> <destination>
print-schedule - time <station> <date> <time>
print-train <trainID>
print-wagon <trainID> <wagonID>
buy-ticket <trainID> <wagonID> <seatID> <ticketFileName>[extra params according to type of wagon]
buy-ticket - discount <trainID> <wagonID> <seatID> <ticketFileName> <cardFile>[extra params accoring to type of wagon]

login <username> <password>
add-station <name>
add-train <station> <destination> <distance> <speed> <departuredate> <departuretime>
remove-train <trainID>
add-wagon <trainID> <wagonType> <baseprice>[extra params]
remove-wagon <trainID> <wagonID>
move-wagon <sourceTrainID> <wagonID> <destinationTrainID>
create-discount-card <cardType> <userName> <fileName>[extra params according to type of card]
validate-discount-card <cardID>
*/

#include "Administrator.h"
#include "User.h"
#include "Station.h"
#include "Train.h"
#include "DiscountCard.h"
#include "FileManager.h"
#include <cstdlib>
#pragma warning(disable:4996)

Vector<Station*> stations;
Vector<Train*> trains;
Vector<User*> users;
Vector<DiscountCard*> discountCards;
User* currentUser = nullptr;
Admin* currentAdmin = nullptr;

Vector<String> parseCommand(const String& input)
{
    Vector<String> tokens;
    const char* str = input.c_str();
    const char* start = str;
    const char* current = str;

    while (*current != '\0')
    {
        while (*current == ' ' || *current == '\t')
        {
            current++;
        }

        if (*current == '\0') break;

        start = current;

        while (*current != '\0' && *current != ' ' && *current != '\t')
        {
            current++;
        }

        size_t length = current - start;
        char* token = new char[length + 1];
        for (size_t i = 0; i < length; i++)
        {
            token[i] = start[i];
        }
        token[length] = '\0';

        tokens.push_back(String(token));
        delete[] token;
    }

    return tokens;
}

Station* findStation(const String& name)
{
    for (size_t i = 0; i < stations.size(); ++i)
    {
        if (stations[i]->getName() == name)
        {
            return stations[i];
        }
    }
    return nullptr;
}

Train* findTrain(const String& trainId)
{
    for (size_t i = 0; i < trains.size(); ++i)
    {
        if (trains[i]->getID() == trainId)
        {
            return trains[i];
        }
    }
    return nullptr;
}

double stringToDouble(const String& str)
{
    double result = 0.0;
    double fraction = 0.0;
    bool decimal = false;
    double divisor = 10.0;
    const char* s = str.c_str();

    while (*s)
    {
        if (*s >= '0' && *s <= '9')
        {
            if (!decimal)
            {
                result = result * 10.0 + (*s - '0');
            }
            else
            {
                fraction += (*s - '0') / divisor;
                divisor *= 10.0;
            }
        }
        else if (*s == '.')
        {
            decimal = true;
        }
        s++;
    }

    return result + fraction;
}

int stringToInt(const String& str)
{
    int result = 0;
    const char* s = str.c_str();

    while (*s)
    {
        if (*s >= '0' && *s <= '9')
        {
            result = result * 10 + (*s - '0');
        }
        s++;
    }

    return result;
}

DiscountCard* findDiscountCard(int cardId)
{
    for (size_t i = 0; i < discountCards.size(); ++i)
    {
        if (discountCards[i]->getCardId() == cardId)
        {
            return discountCards[i];
        }
    }
    return nullptr;
}


//Command implementations
void printStations()
{
    std::cout << "Available Stations:\n";
    for (size_t i = 0; i < stations.size(); ++i)
    {
        std::cout << "- " << stations[i]->getName() << "\n";
    }
}

void printSchedule(const String& stationName)
{
    Station* station = findStation(stationName);
    if (!station)
    {
        std::cout << "Station not found: " << stationName << "\n";
        return;
    }

    std::cout << "Schedule for station " << stationName << ":\n";
    std::cout << "Departures:\n";
    const Vector<Train*>& departures = station->getDepartures();
    for (size_t i = 0; i < departures.size(); ++i)
    {
        std::cout << "  Train " << departures[i]->getID()
            << " to " << departures[i]->getDestination()
            << " at " << departures[i]->getDepartureTime() << "\n";
    }

    std::cout << "Arrivals:\n";
    const Vector<Train*>& arrivals = station->getArrivals();
    for (size_t i = 0; i < arrivals.size(); ++i)
    {
        std::cout << "  Train " << arrivals[i]->getID()
            << " from " << arrivals[i]->getStartingStation()
            << " at " << arrivals[i]->getArrivalTime() << "\n";
    }
}

void printScheduleDestination(const String& stationName, const String& destination)
{
    Station* station = findStation(stationName);
    if (!station)
    {
        std::cout << "Station not found: " << stationName << "\n";
        return;
    }

    std::cout << "Trains from " << stationName << " to " << destination << ":\n";
    const Vector<Train*>& departures = station->getDepartures();
    for (size_t i = 0; i < departures.size(); ++i)
    {
        if (departures[i]->getDestination() == destination)
        {
            std::cout << "  Train " << departures[i]->getID()
                << " at " << departures[i]->getDepartureTime() << "\n";
        }
    }
}

void printScheduleTime(const String& stationName, const String& date, const String& time)
{
    Station* station = findStation(stationName);
    if (!station)
    {
        std::cout << "Station not found: " << stationName << "\n";
        return;
    }

    std::cout << "Trains from " << stationName << " on " << date << " at " << time << ":\n";
    const Vector<Train*>& departures = station->getDepartures();
    for (size_t i = 0; i < departures.size(); ++i)
    {
        if (departures[i]->getDepartureTime() == time)
        {
            std::cout << "  Train " << departures[i]->getID()
                << " to " << departures[i]->getDestination() << "\n";
        }
    }
}

void printTrain(const String& trainId)
{
    Train* train = findTrain(trainId);
    if (!train)
    {
        std::cout << "Train not found: " << trainId << "\n";
        return;
    }

    train->print();
}

void printWagon(const String& trainId, const String& wagonId)
{
    Train* train = findTrain(trainId);
    if (!train)
    {
        std::cout << "Train not found: " << trainId << "\n";
        return;
    }

    Wagon* wagon = train->findWagon(wagonId);
    if (!wagon)
    {
        std::cout << "Wagon not found: " << wagonId << "\n";
        return;
    }

    wagon->print();
}

void buyTicket(const Vector<String>& args, bool useDiscount = false)
{
    if (!currentUser)
    {
        std::cout << "Please login first.\n";
        return;
    }

    if (args.size() < 4)
    {
        std::cout << "Invalid arguments for buy-ticket command.\n";
        return;
    }

    String trainId = args[0];
    String wagonId = args[1];
    String seatIdStr = args[2];
    String ticketFileName = args[3];

    Train* train = findTrain(trainId);
    if (!train)
    {
        std::cout << "Train not found: " << trainId << "\n";
        return;
    }

    Wagon* wagon = train->findWagon(wagonId);
    if (!wagon)
    {
        std::cout << "Wagon not found: " << wagonId << "\n";
        return;
    }

    size_t seatId = 0;
    const char* seatStr = seatIdStr.c_str();
    while (*seatStr)
    {
        if (*seatStr >= '0' && *seatStr <= '9')
        {
            seatId = seatId * 10 + (*seatStr - '0');
        }
        seatStr++;
    }

    FirstClassWagon* firstClass = dynamic_cast<FirstClassWagon*>(wagon);
    SecondClassWagon* secondClass = dynamic_cast<SecondClassWagon*>(wagon);
    SleepingWagon* sleeping = dynamic_cast<SleepingWagon*>(wagon);

    double price = 0;

    if (firstClass)
    {
        price = firstClass->calculatePrice(seatId);
        currentUser->buyTicket(*train, *firstClass, seatIdStr, ticketFileName);
    }
    else if (secondClass)
    {
        int luggageKg = 0;
        if (args.size() > 4)
        {
            const char* luggageStr = args[4].c_str();
            while (*luggageStr)
            {
                if (*luggageStr >= '0' && *luggageStr <= '9')
                {
                    luggageKg = luggageKg * 10 + (*luggageStr - '0');
                }
                luggageStr++;
            }
        }
        price = secondClass->calculatePrice(seatId, luggageKg);
        currentUser->buyTicket(*train, *secondClass, seatIdStr, ticketFileName, luggageKg);
    }
    else if (sleeping)
    {
        price = sleeping->calculatePrice(seatId, train->getDistance());
        currentUser->buyTicket(*train, *sleeping, seatIdStr, ticketFileName);
    }

    if (useDiscount && args.size() > 4)
    {
        String cardFile = args[4];

        std::cout << "Discount applied from card file: " << cardFile << "\n";
    }

    std::cout << "Ticket purchased successfully. Price: " << price << "\n";
}

void login(const String& username, const String& password)
{
    if (!currentAdmin)
    {
        currentAdmin = new Admin();
        if (currentAdmin->login(username, password))
        {
            std::cout << "Admin logged in successfully.\n";
            return;
        }
        delete currentAdmin;
        currentAdmin = nullptr;
    }

    for (size_t i = 0; i < users.size(); ++i)
    {
        if (users[i]->login(username, password))
        {
            currentUser = users[i];
            std::cout << "User logged in successfully.\n";
            return;
        }
    }

    std::cout << "Invalid credentials.\n";
}

void addStation(const String& name)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    Station* newStation = new Station(name);
    stations.push_back(newStation);
    std::cout << "Station added: " << name << "\n";
}

void addTrain(const Vector<String>& args)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    if (args.size() < 6)
    {
        std::cout << "Invalid arguments for add-train command.\n";
        return;
    }

    String stationName = args[0];
    String destination = args[1];
    double distance = stringToDouble(args[2]);
    double speed = stringToDouble(args[3]);
    String departureDate = args[4];
    String departureTime = args[5];

    currentAdmin->addTrain(stations, stationName, destination, distance, speed, departureDate, departureTime);
    std::cout << "Train added successfully.\n";
}

void removeTrain(const String& trainId)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    String trainIdCopy = trainId;
    currentAdmin->removeTrain(trainIdCopy);
    std::cout << "Train removed: " << trainId << "\n";
}

void addWagon(const Vector<String>& args)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    if (args.size() < 3)
    {
        std::cout << "Invalid arguments for add-wagon command.\n";
        return;
    }

    String trainId = args[0];
    String wagonType = args[1];
    double basePrice = stringToDouble(args[2]);

    String trainIdCopy = trainId;
    String wagonTypeCopy = wagonType;
    currentAdmin->addWagon(trainIdCopy, wagonTypeCopy, basePrice);
    std::cout << "Wagon added to train " << trainId << "\n";
}

void removeWagon(const String& trainId, const String& wagonId)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    String trainIdCopy = trainId;
    String wagonIdCopy = wagonId;
    currentAdmin->removeWagon(trainIdCopy, wagonIdCopy);
    std::cout << "Wagon removed from train " << trainId << "\n";
}

void moveWagon(const String& sourceTrainId, const String& wagonId, const String& destTrainId)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    String sourceTrainIdCopy = sourceTrainId;
    String wagonIdCopy = wagonId;
    String destTrainIdCopy = destTrainId;
    currentAdmin->moveWagon(sourceTrainIdCopy, wagonIdCopy, destTrainIdCopy);
    std::cout << "Wagon moved from train " << sourceTrainId << " to train " << destTrainId << "\n";
}

void createDiscountCard(const Vector<String>& args)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    if (args.size() < 3)
    {
        std::cout << "Invalid arguments for create-discount-card command.\n";
        return;
    }

    String cardType = args[0];
    String userName = args[1];
    String fileName = args[2];

    int cardId = discountCards.size() + 1;
    double discountPercent = 10.0;

    if (args.size() > 3)
    {
        discountPercent = stringToDouble(args[3]);
    }

    String cardTypeCopy = cardType;
    String userNameCopy = userName;
    currentAdmin->createDiscountCard(cardTypeCopy, userNameCopy, cardId, discountPercent);

    DiscountCard* newCard = new DiscountCard(cardType, userName, cardId, discountPercent);
    discountCards.push_back(newCard);

    std::cout << "Discount card created with ID: " << cardId << "\n";
}

void validateDiscountCard(int cardId)
{
    if (!currentAdmin || !currentAdmin->isAuthenticated())
    {
        std::cout << "Admin privileges required.\n";
        return;
    }

    bool isValid = currentAdmin->validateDiscountCard(cardId);
    std::cout << "Card " << cardId << " is " << (isValid ? "valid" : "invalid") << "\n";
}

void processCommand(const String& input)
{
    Vector<String> args = parseCommand(input);

    if (args.empty())
    {
        return;
    }

    String command = args[0];

    if (command == "print-stations")
    {
        printStations();
    }
    else if (command == "print-schedule")
    {
        if (args.size() >= 2)
        {
            if (args.size() >= 4 && args[1] == "-" && args[2] == "destination")
            {
                printScheduleDestination(args[1], args[3]);
            }
            else if (args.size() >= 5 && args[1] == "-" && args[2] == "time")
            {
                printScheduleTime(args[3], args[4], args[5]);
            }
            else
            {
                printSchedule(args[1]);
            }
        }
    }
    else if (command == "print-train")
    {
        if (args.size() >= 2)
        {
            printTrain(args[1]);
        }
    }
    else if (command == "print-wagon")
    {
        if (args.size() >= 3)
        {
            printWagon(args[1], args[2]);
        }
    }
    else if (command == "buy-ticket")
    {
        Vector<String> ticketArgs;
        bool useDiscount = false;
        size_t startIndex = 1;

        if (args.size() >= 2 && args[1] == "-" && args[2] == "discount")
        {
            useDiscount = true;
            startIndex = 3;
        }

        for (size_t i = startIndex; i < args.size(); ++i)
        {
            ticketArgs.push_back(args[i]);
        }

        buyTicket(ticketArgs, useDiscount);
    }
    else if (command == "login")
    {
        if (args.size() >= 3)
        {
            login(args[1], args[2]);
        }
    }
    else if (command == "add-station")
    {
        if (args.size() >= 2)
        {
            addStation(args[1]);
        }
    }
    else if (command == "add-train")
    {
        Vector<String> trainArgs;
        for (size_t i = 1; i < args.size(); ++i)
        {
            trainArgs.push_back(args[i]);
        }
        addTrain(trainArgs);
    }
    else if (command == "remove-train")
    {
        if (args.size() >= 2)
        {
            removeTrain(args[1]);
        }
    }
    else if (command == "add-wagon")
    {
        Vector<String> wagonArgs;
        for (size_t i = 1; i < args.size(); ++i)
        {
            wagonArgs.push_back(args[i]);
        }
        addWagon(wagonArgs);
    }
    else if (command == "remove-wagon")
    {
        if (args.size() >= 3)
        {
            removeWagon(args[1], args[2]);
        }
    }
    else if (command == "move-wagon")
    {
        if (args.size() >= 4)
        {
            moveWagon(args[1], args[2], args[3]);
        }
    }
    else if (command == "create-discount-card")
    {
        Vector<String> cardArgs;
        for (size_t i = 1; i < args.size(); ++i)
        {
            cardArgs.push_back(args[i]);
        }
        createDiscountCard(cardArgs);
    }
    else if (command == "validate-discount-card")
    {
        if (args.size() >= 2)
        {
            int cardId = stringToInt(args[1]);
            validateDiscountCard(cardId);
        }
    }
    else if (command == "help")
    {
        std::cout << "Available commands:\n";
        std::cout << "login <username> <password>\n";
        std::cout << "print-stations\n";
        std::cout << "print-schedule <station>\n";
        std::cout << "print-schedule - destination <station> <destination>\n";
        std::cout << "print-schedule - time <station> <date> <time>\n";
        std::cout << "print-train <trainID>\n";
        std::cout << "print-wagon <trainID> <wagonID>\n";
        std::cout << "buy-ticket <trainID> <wagonID> <seatID> <ticketFileName> [extra params]\n";
        std::cout << "buy-ticket - discount <trainID> <wagonID> <seatID> <ticketFileName> <cardFile> [extra params]\n";
        std::cout << "login <username> <password>\n";
        std::cout << "add-station <n>\n";
        std::cout << "add-train <station> <destination> <distance> <speed> <departuredate> <departuretime>\n";
        std::cout << "remove-train <trainID>\n";
        std::cout << "add-wagon <trainID> <wagonType> <baseprice> [extra params]\n";
        std::cout << "remove-wagon <trainID> <wagonID>\n";
        std::cout << "move-wagon <sourceTrainID> <wagonID> <destinationTrainID>\n";
        std::cout << "create-discount-card <cardType> <userName> <fileName> [extra params]\n";
        std::cout << "validate-discount-card <cardID>\n";
        std::cout << "exit\n";
    }
    else if (command == "exit")
    {
        std::cout << "Goodbye!\n";
        exit(0);
    }
    else
    {
        std::cout << "Unknown command: " << command << ". Type 'help' for available commands.\n";
    }
}

void cleanup()
{
    for (size_t i = 0; i < stations.size(); ++i)
    {
        delete stations[i];
    }

    for (size_t i = 0; i < trains.size(); ++i)
    {
        delete trains[i];
    }

    for (size_t i = 0; i < users.size(); ++i)
    {
        delete users[i];
    }

    for (size_t i = 0; i < discountCards.size(); ++i)
    {
        delete discountCards[i];
    }

    if (currentAdmin)
    {
        delete currentAdmin;
    }
}

void initializeDefaultData()
{
    FileManager::loadStations(stations);
    FileManager::loadTrains(trains);
    FileManager::loadUsers(users);
    FileManager::loadDiscountCards(discountCards);

    if (stations.empty())
    {
        stations.push_back(new Station("Sofia"));
        stations.push_back(new Station("Plovdiv"));
        stations.push_back(new Station("Varna"));
        stations.push_back(new Station("Burgas"));
    }

    if (users.empty())
    {
        users.push_back(new User("user1", "password1"));
        users.push_back(new User("user2", "password2"));
    }
}

int main()
{
    std::cout << "Welcome to the Train Reservation System!\n";
    std::cout << "Type 'help' for available commands or 'exit' to quit.\n\n";

    initializeDefaultData();

    String input;
    char buffer[1000];

    while (true)
    {
        std::cout << "> ";
        std::cin.getline(buffer, 1000);
        input = String(buffer);

        if (!input.empty())
        {
            processCommand(input);
        }
    }

    cleanup();
    return 0;
}