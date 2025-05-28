#include "catch.hpp"
#include "Cell_Culture/Cell.h"

SCENARIO("Using a default (nonparameterized) cell object", "[Cell]") {
    GIVEN("A default (nonparameterized) cell object") {
        Cell cell;

        THEN("The age of the cell should be 0") {
            REQUIRE(cell.getAge() == 0);
        }

        THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
            REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
        }

        THEN("The cell value should match the default value '#'") {
            REQUIRE(cell.getCellValue() == '#');
        }

        THEN("The cell should not be a rim cell") {
            REQUIRE(!cell.isRimCell());
        }

        THEN("The cell should not be alive") {
            REQUIRE(!cell.isAlive());
        }

        THEN("The action for the next generation should be DO_NOTHING") {
            REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
        }

        THEN("The value for willBeAlive in the next generation should be false") {
            REQUIRE(!cell.isAliveNext());
        }

        COLOR newColor = STATE_COLORS.LIVING;
        WHEN("Setting the color for the next generation to STATE_COLORS.LIVING (white == 7)") {
            cell.setNextColor(newColor);

            AND_THEN("Updating the cell state") {
                cell.updateState();

                THEN("That color should match the color STATE_COLORS.LIVING (white == 7)") {
                    REQUIRE(cell.getColor() == STATE_COLORS.LIVING);
                }
            }
        }

        char newValue = 'E';
        WHEN("Setting a new value '"  + newValue + "' for the next generation") {
            cell.setNextCellValue(newValue);

            AND_THEN("Updating the cell state") {
                cell.updateState();

                THEN("That value should match the value '"  + newValue + "', that was passed") {
                    REQUIRE(cell.getCellValue() == newValue);
                }
            }
        }

        WHEN("Setting 'isAlive' for next generation to true") {
            cell.setIsAliveNext(true);

            AND_THEN("Getting the value for 'isAlive' for next generation") {
                bool isAliveNext = cell.isAliveNext();

                THEN("That value should be true") {
                    REQUIRE(isAliveNext);
                }
            }
        }

        WHEN("Setting 'nextGenerationAction' for next generation to KILL_CELL") {
            cell.setNextGenerationAction(KILL_CELL);

            AND_THEN("Getting the value of 'nextGenerationAction'") {
                ACTION nextAction = cell.getNextGenerationAction();

                THEN("That value should match what was passed") {
                    REQUIRE(nextAction == KILL_CELL);
                }
            }
        }

        WHEN("Setting the action for the next generation to GIVE_CELL_LIFE") {
            cell.setNextGenerationAction(GIVE_CELL_LIFE);

            AND_THEN("Updating the cell state") {
                cell.updateState();

                THEN("The cell should be alive") {
                    REQUIRE(cell.isAlive() == true);
                }

                THEN("The age should be 1") {
                    REQUIRE(cell.getAge() == 1);
                }

                WHEN("Setting the action for the next generation to IGNORE") {
                    cell.setNextGenerationAction(IGNORE_CELL);

                    AND_THEN("Updating the cell state") {
                        cell.updateState();

                        THEN("The the age should be 2") {
                            REQUIRE(cell.getAge() == 2);
                        }

                        WHEN("Setting the action for the next generation to KILL_CELL") {
                            cell.setNextGenerationAction(KILL_CELL);

                            AND_THEN("Updating the cell state") {
                                cell.updateState();

                                THEN("The cell should no longer be alive") {
                                    REQUIRE(cell.isAlive() == false);
                                }

                                THEN("The the age should be 0") {
                                    REQUIRE(cell.getAge() == 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("Using a singly parameterized cell object - Cell(isRimCell)", "[Cell], [isRimCell]") {
    GIVEN("A singly parameterized cell object - Cell(isRimCell)") {

        WHEN("isRimCell is initialized to true") {
            Cell cell(true);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should be a rim cell") {
                REQUIRE(cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("isRimCell is initialized to false") {
            Cell cell(false);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should not be a rim cell") {
                REQUIRE(!cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }
    }
}

SCENARIO("Using a doubly parameterized cell object - Cell(isRimCell, action)", "[Cell], [Action]") {
    GIVEN("A doubly parameterized cell object - Cell(isRimCell, action)") {

        WHEN("IsRimCell is initialized to false and Action is initialized to KILL_CELL") {
            Cell cell(false,KILL_CELL);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should not be a rim cell") {
                REQUIRE(!cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to true and Action is initialized to KILL_CELL") {
            Cell cell(true,KILL_CELL);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should be a rim cell") {
                REQUIRE(cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to false and Action is initialized to IGNORE_CELL") {
            Cell cell(false, IGNORE_CELL);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should not be a rim cell") {
                REQUIRE(!cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to true and Action is initialized to IGNORE_CELL") {
            Cell cell(true, IGNORE_CELL);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should be a rim cell") {
                REQUIRE(cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to false and Action is initialized to GIVE_CELL_LIFE") {
            Cell cell(false, GIVE_CELL_LIFE);

            THEN("The age of the cell should be 1") {
                REQUIRE(cell.getAge() == 1);
            }

            THEN("The color of the cell should match the color of a living cell (STATE_COLORS.LIVING == WHITE)") {
                REQUIRE(cell.getColor() == STATE_COLORS.LIVING);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should not be a rim cell") {
                REQUIRE(!cell.isRimCell());
            }

            THEN("The cell should be alive") {
                REQUIRE(cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to true and Action is initialized to GIVE_CELL_LIFE") {
            Cell cell(true, GIVE_CELL_LIFE);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should be a rim cell") {
                REQUIRE(cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to false and Action is initialized to DO_NOTHING") {
            Cell cell(false, DO_NOTHING);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should not be a rim cell") {
                REQUIRE(!cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }

        WHEN("IsRimCell is initialized to true and Action is initialized to DO_NOTHING") {
            Cell cell(true, DO_NOTHING);

            THEN("The age of the cell should be 0") {
                REQUIRE(cell.getAge() == 0);
            }

            THEN("The color of the cell should match the color of a dead cell (STATE_COLORS.DEAD == BLACK)") {
                REQUIRE(cell.getColor() == STATE_COLORS.DEAD);
            }

            THEN("The cell value should match the default value '#'") {
                REQUIRE(cell.getCellValue() == '#');
            }

            THEN("The cell should be a rim cell") {
                REQUIRE(cell.isRimCell());
            }

            THEN("The cell should not be alive") {
                REQUIRE(!cell.isAlive());
            }

            THEN("The action for the next generation should be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }

            THEN("The value for willBeAlive in the next generation should be false") {
                REQUIRE(!cell.isAliveNext());
            }
        }
    }
}

SCENARIO("Testing Cell::setNextGenerationAction(action)", "[Cell]") {

    GIVEN("A cell object initialized as a rim cell") {
        Cell cell(true);

        WHEN("Attempting to set the next generation action to GIVE_CELL_LIFE") {
            cell.setNextGenerationAction(GIVE_CELL_LIFE);

            THEN("The next generation action should still be DO_NOTHING") {
                REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
            }
        }
    }

    GIVEN("A cell object initialized as a living cell") {
        Cell cell(false, GIVE_CELL_LIFE);

        THEN("The cell should be alive") {
            REQUIRE(cell.isAlive());

            WHEN("Attempting to set the next generation action to GIVE_CELL_LIFE") {
                cell.setNextGenerationAction(GIVE_CELL_LIFE);

                THEN("The next generation action should still be DO_NOTHING") {
                    REQUIRE(cell.getNextGenerationAction() == DO_NOTHING);
                }
            }
        }
    }
}