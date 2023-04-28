//
// Created by student on 13.06.2022.
//

#ifndef PENSJONAT_CLIENTMANAGER_H
#define PENSJONAT_CLIENTMANAGER_H

#include "model/typedefs.h"
#include <string>

class ClientManager {
private:
    ClientRepositoryPtr clientRepository;

public:
    ClientManager(const ClientRepositoryPtr &clientRepository);

    virtual ~ClientManager();


    ClientPtr addClient(const std::string &firstName, const std::string &surname,
                             const std::string &personalID, const AddressPtr &address);

    void unregisterClient(const ClientPtr &client);

    const ClientPtr getClient(const std::string &personalID) const;

    std::string getClientInfo() const;

};


#endif //PENSJONAT_CLIENTMANAGER_H
