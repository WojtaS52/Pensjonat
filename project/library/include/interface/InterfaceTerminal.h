//
// Created by student on 13.06.2022.
//

#ifndef PENSJONAT_INTERFACETERMINAL_H
#define PENSJONAT_INTERFACETERMINAL_H

#include "model/typedefs.h"



class InterfaceTerminal {
private:
    ClientManagerPtr clientManager;
    RoomManagerPtr roomManager;
    RentManagerPtr rentManager;

public:
    InterfaceTerminal(const ClientManagerPtr &clientManager, const RoomManagerPtr &roomManager,
                      const RentManagerPtr &rentManager);

    virtual ~InterfaceTerminal();

    //funkcje potrzeben do naszego interfejsu dla uzytkownika

    void begin();

    void client();

    void room();

    void rent();

};


#endif //PENSJONAT_INTERFACETERMINAL_H
