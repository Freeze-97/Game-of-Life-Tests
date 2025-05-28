#include "catch.hpp"
#include "Cell_Culture/Population.h"

#include <string>
#include <random>

SCENARIO("Using a default (uninitiated) population object") {
    GIVEN("A default (uninitiated) population object") {
        Population population;
        std::default_random_engine generator(static_cast<unsigned int>(time(0))); // Ser till att raden av slumptal inte upprepas.
        std::uniform_int_distribution<int> randomHeight(0, WORLD_DIMENSIONS.HEIGHT);
        std::uniform_int_distribution<int> randomWidth(0, WORLD_DIMENSIONS.WIDTH);

        THEN("The cell population should be 0") {
            REQUIRE(population.getTotalCellPopulation() == 0);
        }

        int col = randomWidth(generator);
        int row = randomHeight(generator);
        Point p{col, row};

        THEN("Getting a cell at a random position in the world [" + to_string(col) + ", " + to_string(row) +
             "] will throw exception [out_of_range]") {
            REQUIRE_THROWS_AS(population.getCellAtPosition(p), std::logic_error &le);
        }

        THEN("Calculating a new generation should do nothing") {
            REQUIRE_NOTHROW(population.calculateNewGeneration());
        }
    }
}

SCENARIO("Initiating a population", "[Population]") {
    Population population;
    std::vector<std::string> ruleNames {"Conway", "Erik", "VonNeuMann"};
    std::default_random_engine generator(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<int> randomHeight(0, WORLD_DIMENSIONS.HEIGHT);
    std::uniform_int_distribution<int> randomWidth(0, WORLD_DIMENSIONS.WIDTH);

    for (const auto& rule : ruleNames) {
        GIVEN("A rule: " + rule) {
            population.initiatePopulation(rule);

            THEN("The cell population should be greater than 0") {
                CHECK(population.getTotalCellPopulation() > 0);
            }

            int col = randomWidth(generator);
            int row = randomHeight(generator);
            Point p{col, row};

            THEN("Getting a cell at a random position in the world [" + to_string(col) + ", " + to_string(row)
                 + "] should return a reference to the element") {
                REQUIRE_NOTHROW(population.getCellAtPosition(p));
            }

            THEN("Calculating the new generation should return 1") {
                REQUIRE(population.calculateNewGeneration() == 1);
            }
        }
    }

    for (const auto& evenRule : ruleNames) {
        for (const auto& oddRule : ruleNames) {
            GIVEN("An even rule: " + evenRule + " and an odd rule: " + oddRule) {
                population.initiatePopulation(evenRule, oddRule);

                THEN("The cell population should be greater than 0") {
                    CHECK(population.getTotalCellPopulation() > 0);
                }

                int col = randomWidth(generator);
                int row = randomHeight(generator);
                Point p{col, row};

                THEN("Getting a cell at a random position in the world [" + to_string(col) + ", " + to_string(row) +
                     "] return a reference to the element") {
                    REQUIRE_NOTHROW(population.getCellAtPosition(p));
                }

                THEN("Calculating the new generation should return 1") {
                    REQUIRE(population.calculateNewGeneration() == 1);
                }
            }
        }
    }
}