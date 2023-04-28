//
// Created by student on 11.06.2022.
//

#include <fstream>
#include "model/Client.h"

#include "model/Address.h"
#include "exceptions/ParameterException.h"

Client::Client(const std::string &firstName, const std::string &surname, const std::string &personalId,
               const AddressPtr &address) : firstName(firstName), surname(surname), personalId(personalId),
                                            address(address) {

    isArchive = false;

    clientType = std::make_shared<Default>();

    if(firstName.empty()){
       throw ParameterException("Imie nie może byc puste!\n");
    }

    if(surname.empty()){

        throw ParameterException("Nazwisko nie moze pozostac puste!\n");
    }

    if(personalId.empty()){

        throw ParameterException("Pole personalID nie moze pozostac puste!\n");
    }

    if(address == nullptr){

        throw ParameterException("Pole address nie moze pozostac puste!\n");

    }

}

Client::~Client() {

}

const std::string &Client::getFirstName() const {
    return firstName;
}

const std::string &Client::getSurname() const {
    return surname;
}

const std::string &Client::getPersonalId() const {
    return personalId;
}

const AddressPtr &Client::getAddress() const {
    return address;
}



void Client::setFirstName(const std::string &nFirstName) {
    if(!nFirstName.empty()){
        firstName = nFirstName;
    }

}

void Client::setSurname(const std::string &nSurname) {
    if(!nSurname.empty()){
        surname = nSurname;
    }

}



void Client::setAddress(const AddressPtr &nAddress) {
    if(nAddress!= nullptr){
        address = nAddress;
    }

}


const ClientTypePtr &Client::getClientType() const {
    return clientType;
}

void Client::setClientType(const ClientTypePtr &newClientType) {
    if (newClientType == nullptr) {
        return;
    }
    clientType = newClientType;
}


bool Client::getArchive() const {
    return isArchive;
}

void Client::setArchiveStatus(bool status) {
    isArchive= true; //domyślnie ustawiamy true, bo jak se no to true
}

float Client::calculateClientCosts(float price) const {

    return clientType->applyCost(price);


}



std::string Client::getInfo() const {

    std::ofstream file("klienci.txt");



    file<<getFirstName()<<" "<<getSurname()<<" "<<getPersonalId()<<" "<<getArchive()<<" "<<address->getInfo();


    file.close();

    return "(Client) first name: " + getFirstName() + ", last name: " + getSurname() + ", personal id: " +
           getPersonalId() + " " + ", is archived: " +
           (getArchive() ? "true" : "false") + " " + address->getInfo();
}