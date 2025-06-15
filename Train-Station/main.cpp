/*
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