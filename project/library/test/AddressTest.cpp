//
// Created by student on 12.06.2022.
//
#include <boost/test/unit_test.hpp>
#include "model/Address.h"

BOOST_AUTO_TEST_SUITE(TestSuiteAddress)

    BOOST_AUTO_TEST_CASE(ConstructorTest){
        Address adres("Polska", "Warszawa", "Papierowa", "13B");
        BOOST_TEST(adres.getCountry()=="Polska");
        BOOST_TEST(adres.getCity()=="Warszawa");
        BOOST_TEST(adres.getStreet()=="Papierowa");
        BOOST_TEST(adres.getNumber()=="13B");
    }

    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_THROW(Address adres("", "Warszawa", "Papierowa", "13B"), std::logic_error);
        BOOST_REQUIRE_THROW(Address adres("Polska", "", "Papierowa", "13B"), std::logic_error);
        BOOST_REQUIRE_THROW(Address adres("Polska", "Warszawa", "", "13B"), std::logic_error);
        BOOST_REQUIRE_THROW(Address adres("Polska", "Warszawa", "Papierowa", ""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetterTest){
        Address adres("Polska", "Warszawa", "Papierowa", "13B");
        adres.setCountry("Unitet Kingdom");
        BOOST_TEST(adres.getCountry() == "Unitet Kingdom");
        adres.setCountry("");
        BOOST_TEST(adres.getCountry() == "Unitet Kingdom");

        adres.setCity("Gdansk");
        BOOST_TEST(adres.getCity() == "Gdansk");
        adres.setCity("");
        BOOST_TEST(adres.getCity() == "Gdansk");

        adres.setStreet("Kraszlak");
        BOOST_TEST(adres.getStreet() == "Kraszlak");
        adres.setStreet("");
        BOOST_TEST(adres.getStreet() == "Kraszlak");

        adres.setNumber("11");
        BOOST_TEST(adres.getNumber() == "11");
        adres.setNumber("");
        BOOST_TEST(adres.getNumber() == "11");
    }

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        Address adres("Polska", "Warszawa", "Papierowa", "13B");
        BOOST_TEST(adres.getInfo() == "Country: Polska, city: Warszawa, street: Papierowa, number: 13B");
    }
BOOST_AUTO_TEST_SUITE_END()
