//
// Created by student on 13.06.2022.
//

#include "managers/ClientManager.h"
#include "model/Repository.h"
#include "model/Client.h"
#include "exceptions/ParameterException.h"


ClientManager::ClientManager(const ClientRepositoryPtr &clientRepository) : clientRepository(clientRepository) {
    if(clientRepository == nullptr){
        throw ParameterException("Error: Trying to create ClientManager but there is no repository!");
    }
}

ClientManager::~ClientManager() {}

ClientPtr ClientManager::addClient(const std::string &firstName, const std::string &surname, const std::string &personalID,
                         const AddressPtr &address) {
    ClientPtr clientExam = getClient(personalID);
    if(clientExam == nullptr){
        ClientPtr newClient = std::make_shared<Client>(firstName, surname, personalID, address);
        clientRepository->add(newClient);
        return newClient;
    }
    else{
        clientExam->setArchiveStatus(false);
        clientExam->setFirstName(firstName);
        clientExam->setSurname(surname);
        clientExam->setAddress(address);
        return clientExam;
    }


}

void ClientManager::unregisterClient(const ClientPtr &client) {
    if(client == nullptr){
        throw ParameterException("Non correct ClientPtr");
    }
    client->setArchiveStatus(true);
}

const ClientPtr ClientManager::getClient(const std::string &personalID) const {
    ClientPredicate predicate = [personalID](const ClientPtr ptr){
        return ptr->getPersonalId() == personalID;
    };
    return clientRepository->find(predicate);
}

std::string ClientManager::getClientInfo() const {
    return clientRepository->report();
}






