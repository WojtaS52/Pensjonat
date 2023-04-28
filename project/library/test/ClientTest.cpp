//
// Created by student on 12.06.2022.
//
#include <boost/test/unit_test.hpp>

#include "model/Client.h"
#include "model/Address.h"
#include "model/typedefs.h"

struct TestSuiteClientFixture {
    const std::string testName = "Adam";
    const std::string testSurname = "Mickiewicz";
    const std::string testPersonalID = "9876543210";
    const std::string testFirstName2 = "Piotr";
    const std::string testSurname2 = "Raszyn";
    const std::string testPersonalID2 = "9876543211";
    const std::string testCountry = "Polska";
    const std::string testCity = "Warszawa";
    const std::string testStreet = "Papierowa";
    const std::string testNumber = "13B";
    AddressPtr testaddress;
    AddressPtr testaddress2;

    TestSuiteClientFixture() {
        testaddress = std::make_shared<Address>(testCountry, testCity, testStreet, testNumber);
        testaddress2 = std::make_shared<Address>("Unitet Kingdom", "Gdansk", "Kraszlak", "11");
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        Client client(testName, testSurname, testPersonalID, testaddress);

        BOOST_TEST(client.getFirstName() == testName);
        BOOST_TEST(client.getSurname() == testSurname);
        BOOST_TEST(client.getPersonalId() == testPersonalID);
        BOOST_TEST(client.getAddress() == testaddress);
        BOOST_TEST(!client.getArchive());
    }

    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_THROW(Client client("", testSurname, testPersonalID, testaddress), std::logic_error);
        BOOST_REQUIRE_THROW(Client client(testName, "", testPersonalID, testaddress), std::logic_error);
        BOOST_REQUIRE_THROW(Client client(testName, testSurname, "", testaddress), std::logic_error);
        BOOST_REQUIRE_THROW(Client client(testName, testSurname, testPersonalID, nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SettersTest) {
        Client client(testName, testSurname, testPersonalID, testaddress);

        client.setFirstName(testFirstName2);
        BOOST_TEST(client.getFirstName() == testFirstName2);
        client.setFirstName("");
        BOOST_TEST(client.getFirstName() == testFirstName2);

        client.setSurname(testSurname2);
        BOOST_TEST(client.getSurname() == testSurname2);
        client.setSurname("");
        BOOST_TEST(client.getSurname() == testSurname2);

        client.setAddress(testaddress2);
        BOOST_TEST(client.getAddress() == testaddress2);
        client.setAddress(nullptr);
        BOOST_TEST(client.getAddress() == testaddress2);
    }

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        Client client(testName, testSurname, testPersonalID, testaddress);
        BOOST_TEST(client.getInfo() ==
                           "(Client) first name: " + testName + ", last name: " + testSurname + ", personal id: " +
                                   testPersonalID + " " + ", is archived: " +
                           "false" + " " + testaddress->getInfo());
    }

    BOOST_AUTO_TEST_CASE(ArchiveTest) {
        Client client(testName, testSurname, testPersonalID, testaddress);

        client.setArchiveStatus(false);
        BOOST_TEST(client.getArchive());
    }

BOOST_AUTO_TEST_SUITE_END()