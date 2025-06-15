#include "FileManager.h"
#include <sstream>
#include <ctime>
#include <sys/stat.h>
#include <direct.h>
#include <filesystem>

const String FileManager::STATIONS_FILE = "data/stations.txt";
const String FileManager::TRAINS_FILE = "data/trains.txt";
const String FileManager::USERS_FILE = "data/users.txt";
const String FileManager::CARDS_FILE = "data/cards.txt";
const String FileManager::TICKETS_FILE = "data/tickets/";
const String FileManager::ADMIN_FILE = "data/admin.txt";

Vector<String> FileManager::splitString(const String& str, char delimiter)
{
    Vector<String> result;
    std::stringstream ss(str.c_str());
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        result.push_back(String(token.c_str()));
    }

    return result;
}

String FileManager::trim(const String& str)
{
    const char* start = str.c_str();
    const char* end = start + str.size() - 1;

    while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')
        start++;

    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;

    size_t len = end - start + 1;
    char* trimmed = new char[len + 1];
    std::strncpy(trimmed, start, len);
    trimmed[len] = '\0';

    String result(trimmed);
    delete[] trimmed;
    return result;
}

bool FileManager::fileExists(const String& filename)
{
    std::ifstream file(filename.c_str());
    return file.good();
}

void FileManager::createDirectoryIfNotExists(const String& path)
{
    std::filesystem::create_directory(path.c_str());
}

bool FileManager::saveStations(const Vector<Station*>& stations)
{
    createDirectoryIfNotExists("data");

    std::ofstream file(STATIONS_FILE.c_str());
    if (!file.is_open())
        return false;

    for (size_t i = 0; i < stations.size(); ++i)
    {
        const Station* station = stations[i];
        file << "STATION:" << station->getName().c_str() << std::endl;

        file << "DEPARTURES:";
        const Vector<Train*>& departures = station->getDepartures();
        for (size_t j = 0; j < departures.size(); ++j)
        {
            file << departures[j]->getID().c_str();
            if (j < departures.size() - 1) file << ",";
        }
        file << std::endl;

        file << "ARRIVALS:";
        const Vector<Train*>& arrivals = station->getArrivals();
        for (size_t j = 0; j < arrivals.size(); ++j)
        {
            file << arrivals[j]->getID().c_str();
            if (j < arrivals.size() - 1) file << ",";
        }
        file << std::endl;
        file << "---" << std::endl;
    }

    file.close();
    return true;
}

bool FileManager::loadStations(Vector<Station*>& stations)
{
    if (!fileExists(STATIONS_FILE))
        return false;

    std::ifstream file(STATIONS_FILE.c_str());
    if (!file.is_open())
        return false;

    std::string line;
    String stationName;

    while (std::getline(file, line))
    {
        String strLine(line.c_str());

        if (strLine.c_str()[0] == 'S' && strLine.size() > 8) //STATION:
        {
            stationName = String(strLine.c_str() + 8);
            Station* station = new Station(stationName);
            stations.push_back(station);
        }
    }

    file.close();
    return true;
}

bool FileManager::saveTrains(const Vector<Train*>& trains)
{
    createDirectoryIfNotExists("data");

    std::ofstream file(TRAINS_FILE.c_str());
    if (!file.is_open())
        return false;

    for (size_t i = 0; i < trains.size(); ++i)
    {
        const Train* train = trains[i];
        file << "TRAIN:" << train->getID().c_str() << std::endl;
        file << "START:" << train->getStartingStation().c_str() << std::endl;
        file << "DEST:" << train->getDestination().c_str() << std::endl;
        file << "DEP_TIME:" << train->getDepartureTime().c_str() << std::endl;
        file << "ARR_TIME:" << train->getArrivalTime().c_str() << std::endl;
        file << "DISTANCE:" << train->getDistance() << std::endl;
        file << "SPEED:" << train->getSpeed() << std::endl;
        file << "PLATFORM:" << train->getDeparturePlatform() << std::endl;

        const Vector<Wagon*>& wagons = train->getWagons();
        file << "WAGONS:" << wagons.size() << std::endl;

        for (size_t j = 0; j < wagons.size(); ++j)
        {
            const Wagon* wagon = wagons[j];

            const FirstClassWagon* fcw = dynamic_cast<const FirstClassWagon*>(wagon);
            const SecondClassWagon* scw = dynamic_cast<const SecondClassWagon*>(wagon);
            const SleepingWagon* slw = dynamic_cast<const SleepingWagon*>(wagon);

            if (fcw)
            {
                file << "WAGON_TYPE:FIRST" << std::endl;
                file << "WAGON_ID:" << fcw->getID().c_str() << std::endl;
                file << "SEATS:" << fcw->getSeatCount() << std::endl;
                file << "BASE_PRICE:" << fcw->getBasePrice() << std::endl;
                file << "COMFORT:" << fcw->getComfortFactor() << std::endl;
                file << "FOOD:" << (fcw->isFoodIncluded() ? "1" : "0") << std::endl;
            }
            else if (scw)
            {
                file << "WAGON_TYPE:SECOND" << std::endl;
                file << "WAGON_ID:" << scw->getID().c_str() << std::endl;
                file << "SEATS:" << scw->getSeatCount() << std::endl;
                file << "BASE_PRICE:" << scw->getBasePrice() << std::endl;
                file << "BAGGAGE_PRICE:" << scw->getBaggagePricePerKg() << std::endl;
            }
            else if (slw)
            {
                file << "WAGON_TYPE:SLEEPING" << std::endl;
                file << "WAGON_ID:" << slw->getID().c_str() << std::endl;
                file << "SEATS:" << slw->getSeatCount() << std::endl;
                file << "BASE_PRICE:" << slw->getBasePrice() << std::endl;
                file << "PRICE_PER_100KM:" << slw->getPricePer100km() << std::endl;
            }
        }

        file << "---" << std::endl;
    }

    file.close();
    return true;
}

bool FileManager::loadTrains(Vector<Train*>& trains)
{
    if (!fileExists(TRAINS_FILE))
        return false;

    std::ifstream file(TRAINS_FILE.c_str());
    if (!file.is_open())
        return false;

    std::string line;
    Train* currentTrain = nullptr;

    while (std::getline(file, line))
    {
        String strLine(line.c_str());

        if (strLine.size() >= 6 && std::strncmp(strLine.c_str(), "TRAIN:", 6) == 0)
        {
            String trainId(strLine.c_str() + 6);
            String start, dest, depTime, arrTime;
            double distance = 0, speed = 0;
            int platform = 1;

            std::getline(file, line); // START
            start = String(line.c_str() + 6);

            std::getline(file, line); //DEST
            dest = String(line.c_str() + 5);

            std::getline(file, line); //DEP_TIME
            depTime = String(line.c_str() + 9);

            std::getline(file, line); //ARR_TIME
            arrTime = String(line.c_str() + 9);

            std::getline(file, line); //DISTANCE
            distance = std::atof(line.c_str() + 9);

            std::getline(file, line); //SPEED
            speed = std::atof(line.c_str() + 6);

            std::getline(file, line); //PLATFORM
            platform = std::atoi(line.c_str() + 9);

            currentTrain = new Train(trainId, start, dest, depTime, arrTime, distance, speed, platform);
            trains.push_back(currentTrain);

            std::getline(file, line);
            int wagonCount = std::atoi(line.c_str() + 7);

            for (int i = 0; i < wagonCount; ++i)
            {
                std::getline(file, line); //WAGON_TYPE
                String wagonType(line.c_str() + 12);

                std::getline(file, line); //WAGON_ID
                String wagonId(line.c_str() + 9);

                std::getline(file, line); //SEATS
                int seats = std::atoi(line.c_str() + 6);

                std::getline(file, line); //BASE_PRICE
                double basePrice = std::atof(line.c_str() + 11);

                if (wagonType == String("FIRST"))
                {
                    std::getline(file, line); //COMFORT
                    double comfort = std::atof(line.c_str() + 8);

                    std::getline(file, line); //FOOD
                    bool food = (line.c_str()[5] == '1');

                    FirstClassWagon* wagon = new FirstClassWagon(wagonId, seats, basePrice, comfort, food);
                    currentTrain->addWagon(wagon);
                }
                else if (wagonType == String("SECOND"))
                {
                    std::getline(file, line); //BAGGAGE_PRICE
                    double baggagePrice = std::atof(line.c_str() + 14);

                    SecondClassWagon* wagon = new SecondClassWagon(wagonId, seats, basePrice, baggagePrice);
                    currentTrain->addWagon(wagon);
                }
                else if (wagonType == String("SLEEPING"))
                {
                    std::getline(file, line); //PRICE_PER_100KM
                    double pricePer100km = std::atof(line.c_str() + 15);

                    SleepingWagon* wagon = new SleepingWagon(wagonId, seats, basePrice, pricePer100km);
                    currentTrain->addWagon(wagon);
                }
            }
        }
    }

    file.close();
    return true;
}

bool FileManager::saveDiscountCards(const Vector<DiscountCard*>& cards)
{
    createDirectoryIfNotExists("data");

    std::ofstream file(CARDS_FILE.c_str());
    if (!file.is_open())
        return false;

    for (size_t i = 0; i < cards.size(); ++i)
    {
        const DiscountCard* card = cards[i];
        file << "CARD:" << card->getCardId() << std::endl;
        file << "TYPE:" << card->getType().c_str() << std::endl;
        file << "HOLDER:" << card->getHolderName().c_str() << std::endl;
        file << "DISCOUNT:" << card->getDiscountPercent() << std::endl;
        file << "---" << std::endl;
    }

    file.close();
    return true;
}

bool FileManager::loadDiscountCards(Vector<DiscountCard*>& cards)
{
    if (!fileExists(CARDS_FILE))
        return false;

    std::ifstream file(CARDS_FILE.c_str());
    if (!file.is_open())
        return false;

    std::string line;

    while (std::getline(file, line))
    {
        if (std::strncmp(line.c_str(), "CARD:", 5) == 0)
        {
            int cardId = std::atoi(line.c_str() + 5);

            std::getline(file, line); //TYPE
            String type(line.c_str() + 5);

            std::getline(file, line); //HOLDER
            String holder(line.c_str() + 7);

            std::getline(file, line); //DISCOUNT
            double discount = std::atof(line.c_str() + 9);

            DiscountCard* card = new DiscountCard(type, holder, cardId, discount);
            cards.push_back(card);
        }
    }

    file.close();
    return true;
}

bool FileManager::saveTicket(const Ticket& ticket, const String& filename)
{
    createDirectoryIfNotExists("data");
    createDirectoryIfNotExists("data/tickets");

    String fullPath = TICKETS_FILE + filename;
    std::ofstream file(fullPath.c_str());
    if (!file.is_open())
        return false;

    file << "===============Train Ticket===============" << std::endl;
    file << "Ticket: " << ticket.getTrainID().c_str() << std::endl;
    file << "Train ID: " << ticket.getTrainID().c_str() << std::endl;
    file << "Wagon ID: " << ticket.getWagonID().c_str() << std::endl;
    file << "Seat ID: " << ticket.getSeatID() << std::endl;
    file << "Price: " << ticket.getPrice() << " lv." << std::endl;
    file << "=========================================" << std::endl;

    file.close();
    return true;
}

bool FileManager::loadTicket(Ticket& ticket, const String& filename)
{
    String fullPath = TICKETS_FILE + filename;
    if (!fileExists(fullPath))
        return false;

    std::ifstream file(fullPath.c_str());
    if (!file.is_open())
        return false;


    file.close();
    return true;
}

bool FileManager::saveAdminCredentials(const String& username, const String& password)
{
    createDirectoryIfNotExists("data");

    std::ofstream file(ADMIN_FILE.c_str());
    if (!file.is_open())
        return false;

    file << username.c_str() << std::endl;
    file << password.c_str() << std::endl;

    file.close();
    return true;
}

bool FileManager::loadAdminCredentials(String& username, String& password)
{
    if (!fileExists(ADMIN_FILE))
        return false;

    std::ifstream file(ADMIN_FILE.c_str());
    if (!file.is_open())
        return false;

    std::string line;
    if (std::getline(file, line))
        username = String(line.c_str());

    if (std::getline(file, line))
        password = String(line.c_str());

    file.close();
    return true;
}

// Utility methods
String FileManager::getCurrentDateTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    String dateTime(dt);
    return dateTime;
}

String FileManager::generateUniqueID(const String& prefix)
{
    static int counter = 1000;
    char buffer[50];
    sprintf(buffer, "%s%d", prefix.c_str(), counter++);
    return String(buffer);
}

bool FileManager::writeStringToFile(const String& filename, const String& content)
{
    std::ofstream file(filename.c_str());
    if (!file.is_open())
        return false;

    file << content.c_str();
    file.close();
    return true;
}

bool FileManager::readStringFromFile(const String& filename, String& content)
{
    if (!fileExists(filename))
        return false;

    std::ifstream file(filename.c_str());
    if (!file.is_open())
        return false;

    std::string line, allContent;
    while (std::getline(file, line))
    {
        allContent += line + "\n";
    }

    content = String(allContent.c_str());
    file.close();
    return true;
}

bool FileManager::clearAllData()
{
    std::remove(STATIONS_FILE.c_str());
    std::remove(TRAINS_FILE.c_str());
    std::remove(USERS_FILE.c_str());
    std::remove(CARDS_FILE.c_str());
    std::remove(ADMIN_FILE.c_str());

    return true;
}

bool FileManager::initializeDefaultData()
{
    saveAdminCredentials(String("admin"), String("admin"));

    Vector<Station*> defaultStations;
    defaultStations.push_back(new Station(String("Sofia")));
    defaultStations.push_back(new Station(String("Varna")));
    defaultStations.push_back(new Station(String("Burgas")));
    defaultStations.push_back(new Station(String("Silistra")));
    defaultStations.push_back(new Station(String("Blagoevgrad")));

    bool result = saveStations(defaultStations);

    for (size_t i = 0; i < defaultStations.size(); ++i)
    {
        delete defaultStations[i];
    }

    return result;
}

bool FileManager::validateDataIntegrity()
{
    Vector<Station*> stations;
    Vector<Train*> trains;
    Vector<DiscountCard*> cards;

    bool stationsOk = loadStations(stations);
    bool trainsOk = loadTrains(trains);
    bool cardsOk = loadDiscountCards(cards);

    for (size_t i = 0; i < stations.size(); ++i) delete stations[i];
    for (size_t i = 0; i < trains.size(); ++i) delete trains[i];
    for (size_t i = 0; i < cards.size(); ++i) delete cards[i];

    return stationsOk || trainsOk || cardsOk; 
}

bool FileManager::createBackup(const String& backupName)
{
    createDirectoryIfNotExists("backups");
    String backupDir = String("backups/") + backupName;
    createDirectoryIfNotExists(backupDir);

    return true;
}

bool FileManager::restoreBackup(const String& backupName)
{
    String backupDir = String("backups/") + backupName;

    return fileExists(backupDir);
}