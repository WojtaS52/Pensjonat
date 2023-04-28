//
// Created by student on 12.06.2022.
//
#include <boost/test/unit_test.hpp>

#include "managers/ClientManager.h"
#include "model/Repository.h"
#include "model/Client.h"
#include "model/Address.h"

struct TestSuiteClientManagerFixture {
    const std::string testName = "Adam";
    const std::string testSurname = "Mickiewicz";
    const std::string testPersonalID = "9876543210";
    AddressPtr testAddress;
    ClientRepositoryPtr testClientRepository;

    TestSuiteClientManagerFixture() {
        testAddress = std::make_shared<Address>("Polska", "Warszawa", "Papierowa", "13B");
        testClientRepository = std::make_shared<Repository<ClientPtr>>();
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteClientManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new ClientManager(nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(RegisterClientTest) {
        ClientManager cManager(testClientRepository);

        ClientPtr testClient = cManager.addClient(testName, testSurname, testPersonalID, testAddress);

        BOOST_TEST(testClient == cManager.getClient(testPersonalID));
    }
    BOOST_AUTO_TEST_CASE(RegisterClientTestTheSameID) {
        ClientManager cManager(testClientRepository);

        ClientPtr testClient1 = cManager.addClient("Piotr", "Raszyn", testPersonalID, testAddress);
        ClientPtr testClient2 = cManager.addClient("Gotai", "Kojin", testPersonalID, testAddress);

        BOOST_TEST_REQUIRE(testClient1 == testClient2);
        BOOST_TEST(testClient1->getFirstName() == "Gotai");
        BOOST_TEST(testClient1->getSurname() == "Kojin");
        BOOST_TEST(testClient1->getPersonalId() == testPersonalID);
        BOOST_TEST(testClient1->getAddress() == testAddress);
        BOOST_TEST(testClient1->getArchive());
    }

    BOOST_AUTO_TEST_CASE(GetClientTest) {
        ClientManager cManager(testClientRepository);

        ClientPtr testClient = cManager.addClient(testName, testSurname, testPersonalID, testAddress);
        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678 " << (i);
            cManager.addClient("Janusz", "Kowalski", sout.str(), testAddress);
        }

        BOOST_TEST(cManager.getClient(testPersonalID) == testClient);
    }

    BOOST_AUTO_TEST_CASE(GetClientTestNullPtr) {
        ClientManager cManager(testClientRepository);

        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678 " << (i);
            cManager.addClient("Janusz", "Kowalski", sout.str(), testAddress);
        }

        BOOST_TEST(cManager.getClient(testPersonalID) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(UnregisterClientTest) {
        ClientManager cManager(testClientRepository);

        ClientPtr client = cManager.addClient(testName, testSurname, testPersonalID, testAddress);
        cManager.unregisterClient(client);

        BOOST_TEST(cManager.getClient(testPersonalID)->getArchive());
    }

BOOST_AUTO_TEST_SUITE_END()