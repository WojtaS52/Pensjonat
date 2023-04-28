//
// Created by student on 11.06.2022.
//

#include "model/Rent.h"
#include "model/Client.h"
#include "model/Room.h"
#include <cmath>
#include <boost/uuid/uuid_io.hpp>

#include "exceptions/LogicException.h"
#include "exceptions/ParameterException.h"

Rent::Rent(const boost::uuids::uuid &id, const ClientPtr &client, const RoomPtr &room,
           const boost::posix_time::ptime &startRentTime) : id(id), client(client), room(room),
                                                            startRentTime(startRentTime) {
    if(startRentTime == boost::posix_time::not_a_date_time){
        Rent::startRentTime = boost::posix_time::second_clock::local_time();
    }
    endRentTime = boost::posix_time::not_a_date_time;
    finalRentCost = 0.0;

    if(room == nullptr){
        throw ParameterException("Error! Can create Rent without room!");
    }
    if(client == nullptr){
        throw ParameterException("Error! Can create Rent without client!");
    }
}
Rent::~Rent() {}


const boost::uuids::uuid &Rent::getId() const {
    return id;
}

const ClientPtr &Rent::getClient() const {
    return client;
}

const RoomPtr &Rent::getRoom() const {
    return room;
}
const boost::posix_time::ptime &Rent::getStartRentTime() const {
    return startRentTime;
}

const boost::posix_time::ptime &Rent::getEndRentTime() const {
    return endRentTime;
}

float Rent::getFinalRentCost() const {
    return finalRentCost;
}

std::string Rent::getInfo() const {
    std::ostringstream info;
    info << "Rent: rent id: " << id << " " << getClient()->getInfo()<<" "<<getRoom()->getInfo()
    << ", start rent time: " << startRentTime << ", end rent time: " << endRentTime << ", final cost: " << finalRentCost;
    return info.str();
}

void Rent::endRent(const boost::posix_time::ptime &endRent_time) {
    if(endRentTime == boost::posix_time::not_a_date_time){
        if(endRent_time == boost::posix_time::not_a_date_time){
            endRentTime = boost::posix_time::second_clock::local_time();
        }
        else if(endRent_time > startRentTime) {
            endRentTime = endRent_time;
        }
        else
            endRentTime = startRentTime;
        finalRentCost = calculateFinalRentCost();
    }
}

int Rent::getRentDays() const {
    unsigned int days;
    boost::posix_time::time_period timePeriod = boost::posix_time::time_period(startRentTime, endRentTime);
    days = timePeriod.length().hours()/24;
    if(timePeriod.length().hours()%24 >=1)
        days++;
    return days;
}

float Rent::calculateFinalRentCost() const {
    float costs;
    costs = getClient()->calculateClientCosts(getRentDays() * getRoom()->getBaseprice());

    if(costs < 0){
        throw LogicException("Error! Wrong final rent costs!");
    }
    return costs;
}





