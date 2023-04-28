//
// Created by student on 13.06.2022.
//

#ifndef PENSJONAT_ROOMMANAGER_H
#define PENSJONAT_ROOMMANAGER_H


#include "model/typedefs.h"

#include "managers/RoomManager.h"
#include "model/Repository.h"
#include "model/Room.h"
#include "exceptions/ParameterException.h"
class RoomManager {
private:
    RoomRepositoryPtr roomRepository;
public:

    RoomManager(const RoomRepositoryPtr &roomRepository);

    virtual ~RoomManager();

    const RoomPtr addRoom(int basePrice, int roomNumber, int maxPeopleInRoom); //ustawiamy na false, bo zajety
    void removeRoom(const RoomPtr room);//ustawiamy na true bo wolny

    const RoomPtr getRoom(int roomNumber) const;

    // zwraca pierwszy dopasoany do parametrów wskaźnik na objekt pokoju
    const RoomPtr getRoom(int price, int MaxPeopleInRoom) const;


    std::string getRoomsInfo() const;
    /*
     * RoomMenager(in roomRepository: Repository)
+~RoomManager()
+addRoom(in basePrice: integer, in roomNumber:integer, in roomMaxPeopleInRoom: integer): Room
+removeRoom(in room: Room)
+getRoom(in riimNumber: integer, in MaxPeopleinRoom: integer, in price: integer)
+getRoomsInfo(): strin
     */
};


#endif //PENSJONAT_ROOMMANAGER_H
