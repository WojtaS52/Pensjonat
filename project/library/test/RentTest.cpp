//
// Created by student on 12.06.2022.
//
#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Room.h"
#include "model/Rent.h"
#include "model/Address.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>

namespace pt = boost::posix_time;

struct TestSuiteRentFixture {
    const std::string testFirstName = "Jacob";
    const std::string testLastName = "Webstone";
    const std::string testPersonalID = "02250907670";
    const unsigned int testBasePrice = 150;
    const unsigned int testRoomNumber = 24;
    const unsigned int testRoomCapacity = 4;
    ClientPtr testClient;
    AddressPtr testaddress;
    RoomPtr testRoom;
    boost::uuids::uuid testId;
    pt::ptime testBeginTime;
    std::ostringstream testInfo;
    pt::ptime beginTime = pt::not_a_date_time;

    TestSuiteRentFixture() {
        testaddress = std::make_shared<Address>("United States of America","Warsaw", "KosciuszkoStreet", "34");
        testClient = std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress);
        testRoom = std::make_shared<Room>(testBasePrice, testRoomNumber, testRoomCapacity);
        boost::uuids::random_generator gen;
        testId = gen();
        testBeginTime = pt::second_clock::local_time();

        testInfo << "Rent: rent id: " << testId << " " << testClient->getInfo()<<" "<<testRoom->getInfo()
             << ", start rent time: " << testBeginTime << ", end rent time: " << beginTime << ", final cost: 0";
    }


};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)
    BOOST_AUTO_TEST_CASE(ConstructorTest) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    BOOST_TEST(testId == rent.getId());
    BOOST_TEST(testClient == rent.getClient());
    BOOST_TEST(testRoom == rent.getRoom());
    BOOST_TEST(testBeginTime == rent.getStartRentTime());
    BOOST_TEST(rent.getEndRentTime().is_not_a_date_time());
    BOOST_TEST(0 == rent.getFinalRentCost());
}

BOOST_AUTO_TEST_CASE(ConstructorTestExceptions) {
    BOOST_REQUIRE_THROW(Rent rent(testId, nullptr, testRoom, testBeginTime), std::logic_error);
    BOOST_REQUIRE_THROW(Rent rent(testId, testClient, nullptr, testBeginTime), std::logic_error);
}

BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    BOOST_TEST_REQUIRE(!rent.getStartRentTime().is_not_a_date_time());

    pt::ptime now = pt::second_clock::local_time();
    pt::time_period skew = pt::time_period(rent.getStartRentTime(), now);

    BOOST_TEST((skew.length().hours() == 0 && skew.length().minutes() == 0));
}

BOOST_AUTO_TEST_CASE(RentGetInfoTest) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    BOOST_TEST(testInfo.str() == rent.getInfo());
}

BOOST_AUTO_TEST_CASE(EndRentTestEndNow) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    rent.endRent(testBeginTime);

    pt::time_period skew = pt::time_period(rent.getEndRentTime(), testBeginTime);

    BOOST_TEST(rent.getEndRentTime() == testBeginTime);
}

BOOST_AUTO_TEST_CASE(EndRentTestEndInFuture) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    pt::ptime future = testBeginTime + pt::hours(1);

    rent.endRent(future);

    pt::time_period skew = pt::time_period(rent.getEndRentTime(), future);

    BOOST_TEST(rent.getEndRentTime() == future);
}

BOOST_AUTO_TEST_CASE(EndRentTestEndInPast) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    pt::ptime past = testBeginTime - pt::hours(1);

    rent.endRent(past);

    BOOST_TEST(rent.getEndRentTime() == rent.getStartRentTime());
}

BOOST_AUTO_TEST_CASE(EndRentTestEndRentAlreadyEnded) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    rent.endRent(testBeginTime);

    pt::ptime future = testBeginTime + pt::hours(1);

    rent.endRent(future);

    BOOST_TEST(rent.getEndRentTime()== testBeginTime);
}

BOOST_AUTO_TEST_CASE(GetDaysTestEndedAfter1h) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    pt::ptime future1h = testBeginTime + pt::hours(1);

    rent.endRent(future1h);

    BOOST_TEST(rent.getRentDays() == 1);
}

BOOST_AUTO_TEST_CASE(GetDaysTestEndedAfter59min) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    pt::ptime future59min = testBeginTime + pt::minutes(59);

    rent.endRent(future59min);

    BOOST_TEST(rent.getRentDays() == 0);
}

BOOST_AUTO_TEST_CASE(CalculateFinalRentCostTestDaysIs0) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    rent.endRent(testBeginTime);

    BOOST_TEST(rent.getFinalRentCost() == 0);
}

BOOST_AUTO_TEST_CASE(CalculateFinalRentCostTest) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    pt::ptime future2h = testBeginTime + pt::hours(2);

    rent.endRent(future2h);


   BOOST_TEST(rent.getFinalRentCost() == 150);
}

BOOST_AUTO_TEST_CASE(RentCostTestPernamentCost) {
    Rent rent(testId, testClient, testRoom, testBeginTime);

    pt::ptime future1h = testBeginTime + pt::hours(1);

    rent.endRent(future1h);

    float before = rent.getFinalRentCost();

    rent.getRoom()->setBasePrice(123);

    float after = rent.getFinalRentCost();

    BOOST_TEST(before == after);
}

BOOST_AUTO_TEST_SUITE_END()