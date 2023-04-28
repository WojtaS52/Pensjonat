//
// Created by student on 11.06.2022.
//

#ifndef PENSJONAT_RENT_H
#define PENSJONAT_RENT_H
#include <boost/uuid/uuid.hpp>
#include <boost/date_time.hpp>
#include "model/typedefs.h"

class Rent {
private:
    const boost::uuids::uuid id;
    const ClientPtr client;
    const RoomPtr room;

    boost::posix_time::ptime startRentTime;

    boost::posix_time::ptime endRentTime;

    float finalRentCost;

public:
    Rent(const boost::uuids::uuid &id, const ClientPtr &client, const RoomPtr &room,
         const boost::posix_time::ptime &startRentTime=boost::posix_time::not_a_date_time);

    virtual ~Rent();

    const ClientPtr &getClient() const;

    const RoomPtr &getRoom() const;

    const boost::uuids::uuid &getId() const;

    const boost::posix_time::ptime &getStartRentTime() const;

    const boost::posix_time::ptime &getEndRentTime() const;

    float getFinalRentCost() const;


    std::string getInfo() const;

    void endRent(const boost::posix_time::ptime &arg_endRentTime);

    int getRentDays() const;

    float calculateFinalRentCost() const;
};


#endif //PENSJONAT_RENT_H
