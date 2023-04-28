//
// Created by student on 12.06.2022.
//
#include <boost/test/unit_test.hpp>

#include "model/ClientType.h"
#include "model/typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteClientType)

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        ClientTypePtr clientType = std::make_shared<Default>();
        BOOST_TEST(clientType->getInfo() == "default");

        clientType = std::make_shared<Premium>();
        BOOST_TEST(clientType->getInfo() == "premium");
    }

    BOOST_AUTO_TEST_CASE(ApplyDiscountTest) {

        ClientTypePtr clientType = std::make_shared<Premium>();
        BOOST_TEST(clientType->applyCost(1000) == 900);

        clientType = std::make_shared<Default>();
        BOOST_TEST(clientType->applyCost(1000) == 1000);
    }
BOOST_AUTO_TEST_SUITE_END()