#include <ctime>
#include <memory>
#include <random>
#include "Cell_Culture/Population.h"
#include "catch.hpp"


SCENARIO(
        "getInstance() will return the one and only instance of the object RuleFactory") {
    GIVEN("RuleFactory object") {
        WHEN("getInstance() for RuleFactory is being called") {
            THEN("The RuleFactory object should always be the one and only one, "
                 "in other words, the same one by using std::addressof") {
                CHECK(std::addressof(RuleFactory::getInstance()) ==
                      std::addressof(RuleFactory::getInstance()));
            }
        }
    }
}

