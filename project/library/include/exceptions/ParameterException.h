//
// Created by student on 13.06.2022.
//

#ifndef PENSJONAT_PARAMETEREXCEPTION_H
#define PENSJONAT_PARAMETEREXCEPTION_H

#include <string>
#include <stdexcept>

class ParameterException:public std::logic_error {
private:

public:
    explicit ParameterException(const std::string& what_arg):std::logic_error(what_arg){}
};


#endif //PENSJONAT_PARAMETEREXCEPTION_H
