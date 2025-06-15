#pragma once
#include "User.h"
#include "DiscountCard.h"
#include <fstream>
#include <iostream>

class FileManager
{
private:
    static const String STATIONS_FILE;
    static const String TRAINS_FILE;
    static const String USERS_FILE;
    static const String CARDS_FILE;
    static const String TICKETS_FILE;
    static const String ADMIN_FILE;

    static Vector<String> splitString(const String& str, char delimiter);
    static String trim(const String& str);
    static bool fileExists(const String& filename);
    static void createDirectoryIfNotExists(const String& path);

public:
    static bool saveStations(const Vector<Station*>& stations);
    static bool loadStations(Vector<Station*>& stations);

    static bool saveTrains(const Vector<Train*>& trains);
    static bool loadTrains(Vector<Train*>& trains);

    static bool saveUsers(const Vector<User*>& users);
    static bool loadUsers(Vector<User*>& users);

    static bool saveDiscountCards(const Vector<DiscountCard*>& cards);
    static bool loadDiscountCards(Vector<DiscountCard*>& cards);

    static bool saveTicket(const Ticket& ticket, const String& filename);
    static bool loadTicket(Ticket& ticket, const String& filename);

    static bool saveAdminCredentials(const String& username, const String& password);
    static bool loadAdminCredentials(String& username, String& password);

    static bool createBackup(const String& backupName);
    static bool restoreBackup(const String& backupName);

    static bool validateDataIntegrity();

    static String getCurrentDateTime();
    static String generateUniqueID(const String& prefix);
    static bool writeStringToFile(const String& filename, const String& content);
    static bool readStringFromFile(const String& filename, String& content);

    static bool clearAllData();

    static bool initializeDefaultData();
};