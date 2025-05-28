#include "catch.hpp"
#include "GoL_Rules/RuleOfExistence.h"
#include "GoL_Rules/RuleOfExistence_Conway.h"


SCENARIO("Using a RuleOfExistence_Conway object") {
    GIVEN("A RulesOfExistence_Conway object with undeclared parameter, empty cells ") {
        // Variable for the RuleOfExistence_Conway object
        map<Point, Cell> cells;

        // Object
        RuleOfExistence_Conway ruleOfExistenceConway(cells);

        THEN("The name of the rule name should be 'conway'") {
            REQUIRE(ruleOfExistenceConway.getRuleName() == "conway");
        }

        THEN("There should always be 0 neighbours alive no matter "
             "which cell we are controlling") {
            const int MAX_SIZE = 6; // The cells are built 6X6
            for (int x = 0; x < MAX_SIZE; x++) {
                for (int y = 0; y < MAX_SIZE; y++) {
                    REQUIRE(ruleOfExistenceConway
                                    .testCountAliveNeighbours(Point{x, y}) == 0); // Testing every point
                }
            }
        }

        // Check population limits
        THEN("The populations limits should return the ones "
             "conway uses, 2, 3 and 3") {
            REQUIRE(ruleOfExistenceConway.testGetPopulationLimits().UNDERPOPULATION == 2);
            REQUIRE(ruleOfExistenceConway.testGetPopulationLimits().OVERPOPULATION == 3);
            REQUIRE(ruleOfExistenceConway.testGetPopulationLimits().RESURRECTION == 3);
        }

        // Check directions
        THEN("The directions, all horizontal and vertical, "
             "should have the same size as the ALL_DIRECTIONS object") {
            REQUIRE(ruleOfExistenceConway.testGetDirections().size() == ALL_DIRECTIONS.size());
        }
    }

    // RuleOfExistence object with cells
    GIVEN("A RuleOfExistence_Conway object with all cells declared ") {
        // Cells with given conditions by me
        map<Point, Cell> cells{
                {Point{0, 0}, Cell(true, DO_NOTHING)},
                {Point{0, 1}, Cell(true, DO_NOTHING)},
                {Point{0, 2}, Cell(false, DO_NOTHING)},
                {Point{0, 3}, Cell(false, DO_NOTHING)},
                {Point{0, 4}, Cell(true, DO_NOTHING)},
                {Point{0, 5}, Cell(true, DO_NOTHING)},

                {Point{1, 0}, Cell(true, DO_NOTHING)},
                {Point{1, 1}, Cell(false, DO_NOTHING)},
                {Point{1, 2}, Cell(false, GIVE_CELL_LIFE)},
                {Point{1, 3}, Cell(true, DO_NOTHING)},
                {Point{1, 4}, Cell(false, DO_NOTHING)},
                {Point{1, 5}, Cell(true, DO_NOTHING)},


                {Point{2, 0}, Cell(false, DO_NOTHING)},
                {Point{2, 1}, Cell(false, DO_NOTHING)},
                {Point{2, 2}, Cell(true, DO_NOTHING)},
                {Point{2, 3}, Cell(true, DO_NOTHING)},
                {Point{2, 4}, Cell(false, DO_NOTHING)},
                {Point{2, 5}, Cell(false, DO_NOTHING)},


                {Point{3, 0}, Cell(true, DO_NOTHING)},
                {Point{3, 1}, Cell(true, DO_NOTHING)},
                {Point{3, 2}, Cell(false, GIVE_CELL_LIFE)},
                {Point{3, 3}, Cell(true, DO_NOTHING)},
                {Point{3, 4}, Cell(false, DO_NOTHING)},
                {Point{3, 5}, Cell(false, GIVE_CELL_LIFE)},


                {Point{4, 0}, Cell(false, DO_NOTHING)},
                {Point{4, 1}, Cell(false, DO_NOTHING)},
                {Point{4, 2}, Cell(false, GIVE_CELL_LIFE)},
                {Point{4, 3}, Cell(false, GIVE_CELL_LIFE)},
                {Point{4, 4}, Cell(false, DO_NOTHING)},
                {Point{4, 5}, Cell(true, DO_NOTHING)},


                {Point{5, 0}, Cell(true, DO_NOTHING)},
                {Point{5, 1}, Cell(false, DO_NOTHING)},
                {Point{5, 2}, Cell(false, DO_NOTHING)},
                {Point{5, 3}, Cell(false, DO_NOTHING)},
                {Point{5, 4}, Cell(true, DO_NOTHING)},
                {Point{5, 5}, Cell(true, DO_NOTHING)},
        };

        WHEN("A RuleOfExistence_Conway object is created with declared cells") {
            // Add cells to the object
            RuleOfExistence_Conway ruleOfExistenceConway(cells);

            THEN("The execute method should run without any types of errors") {
                REQUIRE_NOTHROW(ruleOfExistenceConway.executeRule());
            }

            // Control the actions
            THEN("The actions should match the ones given in the cells variable") {
                // Variable with expected actions for every cell, represented by 6x6
                ACTION getAction[36] = {
                        DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING,
                        DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING,
                        DO_NOTHING, KILL_CELL, DO_NOTHING, IGNORE_CELL, IGNORE_CELL, DO_NOTHING,
                        DO_NOTHING, DO_NOTHING, DO_NOTHING, GIVE_CELL_LIFE, IGNORE_CELL, DO_NOTHING,
                        DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING, DO_NOTHING,
                        DO_NOTHING, DO_NOTHING, DO_NOTHING, KILL_CELL, DO_NOTHING, DO_NOTHING
              };

                // Check all points
                int i;
                const int MAX_SIZE = 6; // The cells are built 6X6
                for (int x = 0; x < MAX_SIZE; x++) {
                    for (int y = 0; y < MAX_SIZE; y++) {
                        REQUIRE(ruleOfExistenceConway
                        .testGetAction(ruleOfExistenceConway
                        .testCountAliveNeighbours(Point{x, y}),
                                       cells.at(Point{x, y}).isAlive()) ==
                                       getAction[i]);
                    }
                    i++;
                }
            }

            AND_THEN("The test function of countAliveNeighbours should equal the "
             "expected neighboursAlive variable which represents the 6X6 cell system") {
                // This int will stores expected amount of neighbours to be alive
                int const FIELD_SIZE = 36;
                int neighboursAlive[FIELD_SIZE] = {
                        0, 0, 0, 0, 0, 0,
                        1, 1, 2, 2, 2, 1,
                        1, 1, 2, 2, 2, 2,
                        1, 1, 2, 3, 2, 2,
                        0, 0, 1, 2, 2, 1,
                        0, 0, 1, 0, 1, 0
                };

                // Check all points
                int i;
                const int MAX_SIZE = 6; // The cells are built 6X6
                for (int x = 0; x < MAX_SIZE; x++) {
                    for (int y = 0; y < MAX_SIZE; y++) {
                        REQUIRE(ruleOfExistenceConway.testCountAliveNeighbours(Point{x, y})
                        == neighboursAlive[i]);
                    }
                    i++;
                }
            }
        }
    }
}

