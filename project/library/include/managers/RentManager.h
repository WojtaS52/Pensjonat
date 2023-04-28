//
// Created by student on 13.06.2022.
//

#ifndef PENSJONAT_RENTMANAGER_H
#define PENSJONAT_RENTMANAGER_H

#include "model/typedefs.h"
#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>


class RentManager {
private:
    RentRepositoryPtr presentRent;
    RentRepositoryPtr archiveRent;

    void changeClientType(const ClientPtr &client) const;

public:
    RentManager(const RentRepositoryPtr &presentRent, const RentRepositoryPtr &archiveRent);

    virtual ~RentManager();

    RentPtr rentRoom(const ClientPtr &client, const RoomPtr &room,
                     const boost::posix_time::ptime &startRentTime = boost::posix_time::second_clock::local_time());

    void returnRoom(const RoomPtr &room) const;

    RentPtr getRent(const RoomPtr &room) const;

    std::string getPresentRentsReport() const;

    std::string getArchiveRentsReport() const;
};


#endif //PENSJONAT_RENTMANAGER_H
