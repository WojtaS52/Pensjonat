#ifndef PENSJONAT_CLIENT_H
#define PENSJONAT_CLIENT_H


#include <string>
#include "model/ClientType.h"
#include "model/typedefs.h"

class Client {
private:
    std::string firstName;
    std::string surname;
    std::string personalId;
    AddressPtr  address;
    bool isArchive;
    ClientTypePtr clientType;


public:
    Client(const std::string &firstName, const std::string &surname, const std::string &personalId,
           const AddressPtr &address);
    virtual ~Client();

    //gettery
    const std::string &getFirstName() const;
    const std::string &getSurname() const;
    const std::string &getPersonalId() const;
    const AddressPtr &getAddress() const;
    bool getArchive() const;
    const ClientTypePtr &getClientType() const; //client type
    //setery
    void setFirstName(const std::string &firstName);
    void setSurname(const std::string &surname);
    void setAddress(const AddressPtr &address);
    void setArchiveStatus(bool status);

    void setClientType(const ClientTypePtr &newClientType); //client type
    //getinfo
    std::string getInfo() const;
    //inne funkcje
    float calculateClientCosts(float price) const;




};


#endif //PENSJONAT_CLIENT_H
