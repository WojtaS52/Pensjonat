//
// Created by student on 11.06.2022.
//
#include <boost/test/unit_test.hpp>
#include "managers/RentManager.h"
#include "model/Repository.h"
#include "model/Rent.h"
#include "model/Client.h"
#include "model/ClientType.h"
#include "model/Room.h"
#include "model/Address.h"
#include <boost/uuid/uuid_generators.hpp>

struct TestSuiteRentManagerFixture {

    const std::string testFirstName = "Mateusz";
    const std::string testSurname = "Zmigrocki";
    const std::string testPersonalID = "692137420";
    const unsigned int testBasePrice = 200;
    const unsigned int testRoomNumber = 8;
    const unsigned int testRoomCapacity = 2;
    RentRepositoryPtr testCurrentRents;
    RentRepositoryPtr testArchiveRents;
    ClientPtr testClient;
    AddressPtr testAddress;
    RoomPtr testRoom;
    RoomPtr testRoom2;
    boost::posix_time::ptime testTime;

    TestSuiteRentManagerFixture() {
        testCurrentRents = std::make_shared<Repository<RentPtr>>();
        testArchiveRents = std::make_shared<Repository<RentPtr>>();
        testAddress = std::make_shared<Address>("Poland","Sandomierz", "Piaskowa", "42");
        testClient = std::make_shared<Client>(testFirstName, testSurname, testPersonalID, testAddress);
        testRoom = std::make_shared<Room>(testBasePrice, testRoomNumber, testRoomCapacity);
        testRoom2 = std::make_shared<Room>(testBasePrice, testRoomNumber, testRoomCapacity);
        testTime = boost::posix_time::second_clock::local_time();
    }

};
BOOST_FIXTURE_TEST_SUITE(TestSuiteRenttManager, TestSuiteRentManagerFixture)
    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new RentManager(nullptr, nullptr), std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(RentRoomTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent = rManager.rentRoom(testClient, testRoom, testTime);

        BOOST_TEST(rManager.getRent(testRoom) == testRent);
    }
    BOOST_AUTO_TEST_CASE(RentRoomTestWhenAlreadyRented) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent1 = rManager.rentRoom(testClient, testRoom, testTime);
        RentPtr testRent2 = rManager.rentRoom(testClient, testRoom, testTime);

        BOOST_TEST(testRent2 == nullptr);
    }
    BOOST_AUTO_TEST_CASE(ReturnRoomTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent = rManager.rentRoom(testClient, testRoom, testTime);
        rManager.returnRoom(testRoom);

        BOOST_TEST(rManager.getRent(testRoom) == nullptr);
    }
    BOOST_AUTO_TEST_CASE(findRoomRentTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent1 = rManager.rentRoom(testClient, testRoom, testTime);
        RentPtr testRent2 = rManager.rentRoom(testClient, testRoom2, testTime);

        BOOST_TEST(rManager.getRent(testRoom) == testRent1);
    }

    BOOST_AUTO_TEST_CASE(findRoomRentTestNullPtr) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        rManager.rentRoom(testClient, testRoom, testTime);

        BOOST_TEST(rManager.getRent(testRoom2) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(ChangeClientTypeTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        BOOST_TEST(testClient->getClientType()->getInfo() == "default");//domyslnego uzytkownik

        RoomPtr expensiveRoom = std::make_shared<Room>(2000, testRoomNumber, testRoomCapacity);

        rManager.rentRoom(testClient, expensiveRoom, testTime - boost::posix_time::hours(24));

        rManager.returnRoom(expensiveRoom);

        BOOST_TEST(testClient->getClientType()->getInfo() == "premium");//testujemy dla premium
    }


BOOST_AUTO_TEST_SUITE_END()