//
// Created by student on 12.06.2022.
//

#ifndef PENSJONAT_CLIENTTYPE_H
#define PENSJONAT_CLIENTTYPE_H


#include <string>

class ClientType {
public:
    virtual float applyCost(float price) const = 0;
    virtual std::string getInfo() const = 0;
};

class Default : public ClientType {
public:
    float applyCost(float price) const override;
    std::string getInfo() const override;
};

class Premium : public ClientType {
public:
    float applyCost(float price) const override;
    std::string getInfo() const override;
};


#endif //PENSJONAT_CLIENTTYPE_H
