//
// Created by student on 12.06.2022.
//

#ifndef PENSJONAT_LOGICEXCEPTION_H
#define PENSJONAT_LOGICEXCEPTION_H

#include <vector>
#include <string>
#include <stdexcept>

class LogicException:public std::logic_error{
private:
   //puste miejsce
public:
    explicit LogicException(const std::string& what_arg): std::logic_error(what_arg){}
};


#endif //PENSJONAT_LOGICEXCEPTION_H
