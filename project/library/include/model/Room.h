//
// Created by student on 11.06.2022.
//

#ifndef PENSJONAT_ROOM_H
#define PENSJONAT_ROOM_H


#include <string>

class Room {

private:
    int baseprice;
    int roomNumber;
    int MaxPeopleInRoom;
    bool isArchive;

public:
    Room(int baseprice, int roomNumber, int MaxPeopleInRoom);
    virtual ~Room();

    //gettery
    int getBaseprice() const;
    int getRoomNumber() const;
    int getMaxPeopleInRoom() const;
    bool getIsArchive() const;


    void setBasePrice(int baseprice);

    void setArchiveStatus(bool status);


    // string get info
    std::string getInfo() const;


};



#endif //PENSJONAT_ROOM_H
