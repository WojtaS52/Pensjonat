//
// Created by student on 11.06.2022.
//

#include "model/Address.h"
#include "exceptions/ParameterException.h"

Address::Address(const std::string &country, const std::string &city, const std::string &street,
                 const std::string &number) : country(country), city(city), street(street), number(number) {
    if (country.empty()) { throw ParameterException("Blad! Pole kraj puste..."); }
    if (city.empty()) { throw ParameterException("Blad! Pole miasto puste..."); }
    if (street.empty()) { throw ParameterException("Blad! Pole ulica puste..."); }
    if (number.empty()) { throw ParameterException("Blad! Pole numer domu puste..."); }

}

Address::~Address() {

}


const std::string &Address::getCountry() const {
    return country;
}

const std::string &Address::getCity() const {
    return city;
}

const std::string &Address::getStreet() const {
    return street;
}

const std::string &Address::getNumber() const {
    return number;
}


void Address::setCountry(const std::string &nCountry) {

    if(!nCountry.empty()){
        Address::country = nCountry;
    }
}

void Address::setCity(const std::string &nCity) {
    if(!nCity.empty()){
        Address::city = nCity;
    }

}

void Address::setStreet(const std::string &nStreet) {
    if(!nStreet.empty()){
        Address::street = nStreet;
    }

}

void Address::setNumber(const std::string &nNumber) {
    if(!nNumber.empty()){
        Address::number = nNumber;
    }

}


std::string Address::getInfo() const {
    return "Country: " + getCountry() + ", city: " + getCity() + ", street: " + getStreet() + ", number: " + getNumber();
}
