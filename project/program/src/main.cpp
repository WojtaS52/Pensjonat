#include <iostream>
#include "interface/InterfaceTerminal.h"
#include "managers/ClientManager.h"
#include "managers/RentManager.h"
#include "managers/RoomManager.h"
#include "model/Repository.h"

using namespace std;

int main(){

    ClientRepositoryPtr clientRepo = std::make_shared<Repository<ClientPtr>>();
    ClientManagerPtr clientManager = std::make_shared<ClientManager>(clientRepo);

    RoomRepositoryPtr roomRepo = std::make_shared<Repository<RoomPtr>>();
    RoomManagerPtr roomManager = std::make_shared<RoomManager>(roomRepo);

    RentRepositoryPtr currentRents = std::make_shared<Repository<RentPtr>>();
    RentRepositoryPtr archiveRents = std::make_shared<Repository<RentPtr>>();
    RentManagerPtr rentManager = std::make_shared<RentManager>(currentRents, archiveRents);

    InterfaceTerminal terminal (clientManager, roomManager, rentManager);

    terminal.begin();



    return 0;
}