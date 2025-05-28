#include "catch.hpp"
#include "GoL_Rules/RuleOfExistence.h"
#include "GoL_Rules/RuleOfExistence_Erik.h"

SCENARIO("Using a RuleOfExistence_Erik object to test it") {
    GIVEN("A RuleOfExistence_Erik object with empty cells") {
        WHEN("The cell is not declared") {
            // Empty cells
            map<Point, Cell> cells;

            // main object declared with empty cells
            RuleOfExistence_Erik ruleOfExistenceErik(cells);

            THEN("The name of the rule name should be 'erik'") {
                REQUIRE(ruleOfExistenceErik.getRuleName() == "erik");
            }

            THEN("There should always be 0 neighbours alive no matter "
                 "which cell we are controlling") {
                const int MAX_SIZE = 6; // The cells are built 6X6
                for (int x = 0; x < MAX_SIZE; x++) {
                    for (int y = 0; y < MAX_SIZE; y++) {
                        REQUIRE(ruleOfExistenceErik
                                        .testCountAliveNeighbours(Point{x, y}) == 0); // Testing every point
                    }
                }
            }

            THEN("The population limits should match the ones give by the"
                 "RuleOfExistenceErik constructor") {
                REQUIRE(ruleOfExistenceErik.testGetPopulationLimits().UNDERPOPULATION == 2);
                REQUIRE(ruleOfExistenceErik.testGetPopulationLimits().OVERPOPULATION == 3);
                REQUIRE(ruleOfExistenceErik.testGetPopulationLimits().RESURRECTION == 3);
            }

            THEN("Testing the executerule should not result in any types of errors"
                 "since the cells are empty") {
                REQUIRE_NOTHROW(ruleOfExistenceErik.executeRule());
            }

            THEN("The directions, all horizontal and vertical, "
                 "should have the same size as the ALL_DIRECTIONS object") {
                REQUIRE(ruleOfExistenceErik.testGetDirections().size() == ALL_DIRECTIONS.size());
            }

        }
    }

    GIVEN("A RuleOfExistence_Erik object with declared cells") {
        WHEN("A RuleOfExistence_Erik object is created with declared cells") {
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

            // Object
            RuleOfExistence_Erik ruleOfExistenceErik(cells);

            // Execute Erik's rules
            THEN("The execution of Erik's rules should not throw errors and "
                 "it should ignore rim cells") {
                REQUIRE_NOTHROW(ruleOfExistenceErik.executeRule());
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
                        REQUIRE(ruleOfExistenceErik
                                        .testGetAction(ruleOfExistenceErik
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
                        REQUIRE(ruleOfExistenceErik.testCountAliveNeighbours(Point{x, y})
                                == neighboursAlive[i]);
                    }
                    i++;
                }
            }

            // Test old, elder and prime elder values, they should return the expected values
            THEN("None of the cells should be old "
                 "since no one is older than 5 generations") {
                for(auto &e : cells) {
                    // Using Erik function which differs from the Conway rules
                    ruleOfExistenceErik.testErikfyCell(e.second, e.second.getNextGenerationAction());
                    e.second.updateState();

                    // The state of the cell should be correct
                    AND_THEN("The state of the cells should not be old, elder or prime") {
                        // Checking old
                        REQUIRE(e.second.getColor() != STATE_COLORS.OLD);

                        // Checking elder
                        REQUIRE(e.second.getCellValue() != 'E');

                        /* From what I understand the Color Elder is
                        *meant to represent elder and not prime elder
                        */
                        // Checking prime elder
                        REQUIRE(e.second.getColor() != STATE_COLORS.ELDER);
                    }
                }
            }

            // Test old, after setting their age value to 6
            THEN("The age of the cells is now 6, older than 5, meaning they should be considered"
                 "old by now. The state color should be OLD") {
                for(auto &e : cells) {
                    // Set the age of the cell to 6
                    for(int i = 0; i < 6; i++) {
                        e.second.testIncrementAge();
                    }

                    // Using Erik function which differs from the Conway rules
                    ruleOfExistenceErik.testErikfyCell(e.second, e.second.getNextGenerationAction());
                    e.second.updateState();

                    AND_THEN("The COLOR value should be OLD"
                             "and it should not have the cell value E") {
                        REQUIRE(e.second.getColor() == STATE_COLORS.OLD);
                        REQUIRE(e.second.getCellValue() != 'E');
                    }
                }
            }

            // Test elder/prime, after setting their age value to 15. Only 1 may be a prime elder
            THEN("The age of the cells will now be 15, which is over 10, "
                 "meaning they should be either elder or prime elder") {
                for(auto &e : cells) {
                    // Set the age of the cell to 15
                    for (int i = 0; i < 15; i++) {
                        e.second.testIncrementAge();
                    }

                    // Using Erik function which differs from the Conway rules
                    ruleOfExistenceErik.testErikfyCell(e.second, e.second.getNextGenerationAction());
                    e.second.updateState();

                    /*
                     * An elder will have the values of COLOR = OLD and value E
                     *
                     * While a prime elder will have the values of
                     * COLOR = ELDER and value E
                     */
                    AND_THEN("The cell should be an elder or prime elder") {
                        if(e.second.getColor() == STATE_COLORS.OLD ||
                        e.second.getColor() == STATE_COLORS.ELDER) {
                            REQUIRE(e.second.getCellValue() == 'E');
                        }
                    }
                }
            }
        }
    }
}

