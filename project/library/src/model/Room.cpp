//
// Created by student on 11.06.2022.
//

#include "model/Room.h"
#include "exceptions/ParameterException.h"
Room::Room(int baseprice, int roomNumber, int MaxPeopleInRoom) : baseprice(baseprice),
                                                                                     roomNumber(roomNumber),
                                                                                     MaxPeopleInRoom(
                                                                                             MaxPeopleInRoom){

    isArchive = false;

    if (baseprice <= 0) {
        throw ParameterException("Nieprawidlowa cena");
    }
    if (roomNumber <= 0) {
        throw ParameterException("Nieprawidlowy numer pokoju!");
    }
    if (MaxPeopleInRoom<= 0) {
        throw ParameterException("Nieprawidlowa ilosc osob!");
    }




}

Room::~Room() {

}

int Room::getBaseprice() const {
    return baseprice;
}

int Room::getRoomNumber() const {
    return roomNumber;
}

int Room::getMaxPeopleInRoom() const {
    return MaxPeopleInRoom;
}

bool Room::getIsArchive()const {
    return isArchive;
}

void Room::setBasePrice(int newBaseprice) {
    if(newBaseprice >= 0) {
        Room::baseprice = newBaseprice;
    }
}

void Room::setArchiveStatus(bool status) {
    Room::isArchive= true;
}

std::string Room::getInfo() const {
    return "Room's base price: " + std::to_string(getBaseprice()) + ", room number: " +
           std::to_string(getRoomNumber()) + ", number of people: " + std::to_string(getMaxPeopleInRoom()) + ", archived: " + (getIsArchive()? "true":"false");
}


