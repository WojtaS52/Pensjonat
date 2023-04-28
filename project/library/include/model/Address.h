#ifndef PENSJONAT_ADDRESS_H
#define PENSJONAT_ADDRESS_H
#include <string>

class Address {
private:
    std::string country;
    std::string city;
    std::string street;
    std::string number;

public:
    Address(const std::string &country, const std::string &city, const std::string &street, const std::string &number);

    virtual ~Address();


    const std::string &getCountry() const;

    const std::string &getCity() const;

    const std::string &getStreet() const;

    const std::string &getNumber() const;


    void setCountry(const std::string &country);

    void setCity(const std::string &city);

    void setStreet(const std::string &street);

    void setNumber(const std::string &number);

    std::string getInfo() const;
};


#endif //PENSJONAT_ADDRESS_H
