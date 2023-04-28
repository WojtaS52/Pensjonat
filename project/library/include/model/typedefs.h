//
// Created by student on 13.06.2022.
//

#ifndef PENSJONAT_TYPEDEFS_H
#define PENSJONAT_TYPEDEFS_H

#include <memory>
#include <functional>

class Address;
class Client;
class ClientType;
class Rent;
class Room;
template<class T>
class Repository;

class ClientManager;
class RoomManager;
class RentManager;

class Default;
class Premium;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Room> RoomPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;
typedef std::shared_ptr<Address> AddressPtr;


typedef std::shared_ptr<Repository<RentPtr>> RentRepositoryPtr;
typedef std::shared_ptr<Repository<RoomPtr>> RoomRepositoryPtr;
typedef std::shared_ptr<Repository<ClientPtr>> ClientRepositoryPtr;

typedef std::shared_ptr<ClientManager> ClientManagerPtr;
typedef std::shared_ptr<RentManager> RentManagerPtr;
typedef std::shared_ptr<RoomManager> RoomManagerPtr;

typedef std::function<bool(RentPtr)> RentPredicate;
typedef std::function<bool(RoomPtr)> RoomPredicate;
typedef std::function<bool(ClientPtr)> ClientPredicate;

#endif //PENSJONAT_TYPEDEFS_H
