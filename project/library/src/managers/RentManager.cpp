//
// Created by student on 13.06.2022.
//

#include "exceptions/ParameterException.h"
#include "managers/RentManager.h"
#include "model/Rent.h"
#include "model/Repository.h"
#include "model/Client.h"
#include <boost/uuid/uuid_generators.hpp>
#include <vector>


RentManager::RentManager(const RentRepositoryPtr &presentRent, const RentRepositoryPtr &archiveRent) : presentRent(
        presentRent), archiveRent(archiveRent) {

    if(presentRent == nullptr){
        throw ParameterException("Blad! Nie utworzymy rentManagera bez repository!");
    }
    if(archiveRent == nullptr){
        throw ParameterException("Blad! Nie utworzymy rentManagera bez repository!");
    }
}

RentManager::~RentManager() {

}

void RentManager::changeClientType(const ClientPtr &client) const {
    float moneySpent;
    RentPredicate predicate = [client](const RentPtr &ptr) {
        return ptr->getClient() == client;
    };
    std::vector<RentPtr> clientAvailableRents = archiveRent->findAll(predicate);
    int i = 0;
    while (i < clientAvailableRents.size()) {
        moneySpent += clientAvailableRents[i]->getFinalRentCost();
        i++;
    }
    if (moneySpent < 1000) {
    }
    else {
        client->setClientType(std::make_shared<Premium>());
    }
}

RentPtr RentManager::rentRoom(const ClientPtr &client, const RoomPtr &room,
                              const boost::posix_time::ptime &startRentTime) {
    if(getRent(room) == nullptr){
        boost::uuids::random_generator rg;
        RentPtr newRent = std::make_shared<Rent>(rg(), client, room, startRentTime);
        presentRent->add(newRent);
        return newRent;
    }
    else{
        return nullptr;
    }
}

void RentManager::returnRoom(const RoomPtr &room) const {
    RentPtr rent = getRent(room);
    if(rent != nullptr){
        rent->endRent(boost::posix_time::second_clock::local_time());
        archiveRent->add(rent);
        presentRent->remove(rent);
        changeClientType(rent->getClient());
    }
}

RentPtr RentManager::getRent(const RoomPtr &room) const {
    RentPredicate predicate = [room](const RentPtr &ptr){
        return ptr->getRoom() == room;
    };
    return presentRent->find(predicate);
}

std::string RentManager::getPresentRentsReport() const {
    return presentRent->report();
}

std::string RentManager::getArchiveRentsReport() const {
    return archiveRent->report();
}




