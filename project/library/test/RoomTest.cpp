//
// Created by student on 12.06.2022.
//

#include <boost/test/unit_test.hpp>
#include "model/Room.h"

BOOST_AUTO_TEST_SUITE(TestSuiteRoom)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        Room room(100, 11, 2);

        BOOST_TEST(room.getBaseprice() == 100);
        BOOST_TEST(room.getRoomNumber() == 11);
        BOOST_TEST(room.getMaxPeopleInRoom() == 2);
        BOOST_TEST(!room.getIsArchive());
    }

    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_THROW(Room room(-100, 11, 2), std::logic_error);
        BOOST_REQUIRE_THROW(Room room(100, -11, 2), std::logic_error);
        BOOST_REQUIRE_THROW(Room room(100, 11, -2), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SettersTest) {
        Room room(100, 11, 2);

        room.setBasePrice(123);

        BOOST_TEST(room.getBaseprice() == 123);
    }

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        Room room(100, 11, 2);

        BOOST_TEST(room.getInfo() == "Room's base price: 100, room number: 11, number of people: 2, archived: false");
    }

    BOOST_AUTO_TEST_CASE(ArchiveTest) {
        Room room(100, 11, 2);

        room.setArchiveStatus(false);

        BOOST_TEST(room.getIsArchive());
    }

BOOST_AUTO_TEST_SUITE_END()