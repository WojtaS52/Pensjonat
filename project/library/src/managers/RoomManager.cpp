//
// Created by student on 13.06.2022.
//

#include "managers/RoomManager.h"
#include "model/typedefs.h"


RoomManager::RoomManager(const RoomRepositoryPtr &roomRepository) : roomRepository(roomRepository) {

    if (roomRepository == nullptr)
    {
        throw ParameterException("Nie utowrzymy roomMangera bez repezytorium!!! \n");
    }


}

RoomManager::~RoomManager() {

}

const RoomPtr RoomManager::addRoom(int basePrice, int roomNumber, int maxPeopleInRoom) {

    RoomPtr roomStatus = getRoom(roomNumber);

    if (roomStatus == nullptr)
    {
        RoomPtr newRoom = std::make_shared<Room>(basePrice, roomNumber, maxPeopleInRoom);
        roomRepository->add(newRoom);
        return newRoom;
    }
    else
    {
        if (roomStatus->getIsArchive()) {
            roomStatus->setArchiveStatus(false);
        }
        return roomStatus;
    }


}

void RoomManager::removeRoom(const RoomPtr room) {

    if (room == nullptr) {
        throw ParameterException("Nieprawidłowy pokój - problem z usunieciem wynajecia\n");
    }

    room->setArchiveStatus(true);

}

const RoomPtr RoomManager::getRoom(int roomNumber) const {

    RoomPredicate predicate = [roomNumber](const RoomPtr ptr) {
        return ptr->getRoomNumber() == roomNumber;
    };
    return roomRepository->find(predicate);


}

const RoomPtr RoomManager::getRoom(int price, int roomCapacity) const {
    RoomPredicate predicate = [price, roomCapacity](const RoomPtr ptr) {
        return (ptr->getBaseprice() <= price && ptr->getMaxPeopleInRoom() == roomCapacity);
    };
    return roomRepository->find(predicate);
}


std::string RoomManager::getRoomsInfo() const  {
    return roomRepository->report();
}