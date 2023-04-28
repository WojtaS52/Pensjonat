//
// Created by student on 12.06.2022.
//

#include "model/ClientType.h"


float Default::applyCost(float price) const {
    return price;
}

std::string Default::getInfo() const {
    return "default";
}

float Premium::applyCost(float price) const {
    return (float)(0.9 * price);
}

std::string Premium::getInfo() const {
    return "premium";
}
