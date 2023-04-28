//
// Created by student on 11.06.2022.
//
#include <boost/test/unit_test.hpp>
#include "model/Repository.h"
#include "model/typedefs.h"
#include "model/Client.h"
#include "model/Address.h"

struct TestSuiteRepositoryFixture {
    const std::string testName = "Adam";
    const std::string testSurname = "Mickiewicz";
    const std::string testPersonalId = "0123456789";
    AddressPtr testAddress;

    TestSuiteRepositoryFixture() {
        testAddress = std::make_shared<Address>("Polska", "Warszawa", "Papierowa", "13B");
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepository, TestSuiteRepositoryFixture)

    BOOST_AUTO_TEST_CASE(GetTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        ClientPtr clients[size];

        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            clients[i] = std::make_shared<Client>(testName, testSurname, sout.str(), testAddress);
            cRepo.add(clients[i]);
        }

        for (int i = 0; i < size; i++) {
            BOOST_TEST(cRepo.get(i) == clients[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(GetTestException) {
        Repository<ClientPtr> cRepo;
        BOOST_REQUIRE_THROW(cRepo.get(1), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(AddTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        ClientPtr clients[size];

        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testName, testSurname, sout.str(), testAddress));
        }

        BOOST_TEST(cRepo.size() == size);
    }

    BOOST_AUTO_TEST_CASE(AddTestException) {
        Repository<ClientPtr> cRepo;
        BOOST_REQUIRE_THROW(cRepo.add(nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(FindTest) {
        Repository<ClientPtr> cRepo;
        std::string findPersonalId = "looking_id";
        ClientPtr findClient = std::make_shared<Client>(testName, testSurname, findPersonalId, testAddress);
        cRepo.add(findClient);

        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testName, testSurname, sout.str(), testAddress));
        }

        ClientPredicate predicate = [findPersonalId](const ClientPtr &ptr) {
            return ptr->getPersonalId() == findPersonalId;
        };

        BOOST_TEST(cRepo.find(predicate) == findClient);
    }

    BOOST_AUTO_TEST_CASE(FindAllTest) {
        Repository<ClientPtr> cRepo;
        int MickiewiczSize = 3;
        int RaszynSize = 2;
        std::string findSurname = "Raszyn";
        BOOST_TEST_REQUIRE(testName != findSurname);
        for (int i = 0; i < MickiewiczSize; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testName, findSurname, sout.str(), testAddress));
        }
        for (int i = 0; i < RaszynSize; i++) {
            std::ostringstream sout;
            sout << "012345678" << i + MickiewiczSize;
            cRepo.add(std::make_shared<Client>(testName, testSurname, sout.str(), testAddress));
        }

        ClientPredicate predicate = [findSurname](const ClientPtr &ptr) {
            return ptr->getSurname() == findSurname;
        };

        BOOST_TEST(cRepo.findAll(predicate).size() == MickiewiczSize);
    }

    BOOST_AUTO_TEST_CASE(SizeTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testName, testSurname, sout.str(), testAddress));
        }

        BOOST_TEST(cRepo.size() == size);
    }

    BOOST_AUTO_TEST_CASE(RemoveTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        ClientPtr clients[size];
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            clients[i] = std::make_shared<Client>(testName, testSurname, sout.str(), testAddress);
            cRepo.add(clients[i]);
        }

        cRepo.remove(clients[2]);
        cRepo.remove(clients[3]);

        BOOST_TEST(cRepo.size() == size - 2);
    }


BOOST_AUTO_TEST_SUITE_END()