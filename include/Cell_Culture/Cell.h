/**
 * @file    Cell.h
 * @author  Erik Ström
 * @date    July 2019
 * @version 0.2
*/

#ifndef cellH
#define cellH

#include "../../terminal/terminal.h"

/**
 * @brief Data structure holding colors to visualize the state of cells.
*/
struct StateColors {
    /// Representing living cell
    COLOR LIVING,
    /// Representing dead cell
    DEAD,
    /// Representing old cell
    OLD,
    /// Representing very old cell
    ELDER;
}	/* Initiate default values. */
const STATE_COLORS = { COLOR::WHITE, COLOR::BLACK, COLOR::CYAN, COLOR::MAGENTA };

/**
 * @brief Cell action. Determined by rule, and sent to cell for future change.
*/
enum ACTION { KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING };


/**
 * @brief Cells represents a certain combination of row and column of the simulated world.
 *
 * @details Cells may be of two types; rim cells, those representing the outer limits of the world,
 * or non-rim cells. The first cell type are immutable, exempt from the game's rules, and
 * thus their values may not be changed. The latter type, however, may be changed and edited
 * in ways specified by the rules.
*/
class Cell {
private:
    /**
     * Encapsulate cell details
     */
    struct CellDetails {
        int age;
        COLOR color;
        bool rimCell;
        char value;
    } details;

    /**
     * Encapsulate changes to next state
     */
    struct NextUpdate {
        ACTION nextGenerationAction;
        COLOR nextColor;
        char nextValue;
        bool willBeAlive;	// some rules may need to know beforehand whether the cell will be alive
    } nextUpdate;


    /**
     * @brief Function for increasing the age of the cell by 1.
     */
    void incrementAge() { details.age++; }

    /**
     * @brief Function for resetting the age of a cell, effectively killing it.
     */
    void killCell() { details.age = 0; }

    /**
     * @brief Sets the character value of the cell, which will be printed to screen.
     * @param value the new cell character
     */
    void setCellValue(char value) { details.value = value; }

    /**
     * @brief Function for setting the color of a cell.
     * @param color the new cell color
     */
    void setColor(COLOR color) { this->details.color = color; }

public:

    /**
     * @brief Cell constructor for creating new cell objects.
     *
     * @param isRimCell decides whether its a rim cell or not
     * @param action the action to be performed on the cell
     *
     * @test Test if data members are initialized to the expected values
     * using Constructor with default parameters
     * @test Test if data members are initialized to the expected values
     * using Constructor with single parameter Cell(isRimeCell)
     * @test Test if data members are initialized to the expected values
     * using Constructor with double parameters Cell(isRimCell, Action)
     *
     * @bug The value for nextUpdate.willBeAlive is never initialized or updated,
     * hence it is undefined and the value can be either true or false.
     *
     * @todo The combination of a cell being a rim cell and also giving it life seems somewhat contradictory, resulting in a rim cell having the color of a living cell.
     *
     */
    explicit Cell(bool isRimCell = false, ACTION action = DO_NOTHING);


    /**
     * @brief Function for testing if the cell is alive.
     *
     * @return true if the cell is alive, otherwise dead
     *
     * @test Test if the expected value for living and dead cells are returned
     * for cells constructed with different combinations of parameters
     *
     * @test Test if the expected value for living and dead cells are returned
     * after updating a cell with different actions (KILL_CELL, IGNORE_CELL, GIVE_CELL_LIFE, DO_NOTHING)
     */
    bool isAlive();

    /**
     * @brief Function for setting the action to be executed on the cell
     * in the next generation.
     *
     * @param action action for the next generation
     *
     * @test Test if nextGenerationAction is properly set, by first
     * setting the next action and then getting the next action
     * to see if they match
     *
     * @test Test if nextGenerationAction is properly set
     * by setting the next action, updating the cell state,
     * then checking if the cell state was changed according
     * to the passed action.
     */
    void setNextGenerationAction(ACTION action);

    /**
     * @brief Function used to update the state of a cell.
     *
     * @details A cells state is updated each new generation, using
     * the data members set in the NextUpdate structure
     *
     * @test Test if cells details are properly updated by comparing
     * the updated cell details with those specified in NextUpdate
     *
     */
    void updateState();

    /**
     * @brief Function for getting the current age of the cell.
     *
     * @return the age of the cell
     *
     * @test Test if the expected age is returned when constructing new cells (age == 0)
     *
     * @test Test if the expected age is returned for a living cell that has
     * lived through at least one generation (age > 0)
     */
    int getAge() { return details.age; }

    /**
     * @brief Function for getting the color of the cell.
     *
     * @return the color of the cell
     *
     * @test Test if the expected color is returned
     * for cells constructed with different combinations of parameters
     *
     */
    COLOR getColor() { return details.color; }

    /**
     * @brief Determines whether the cell is a rim cell, and thus should be immutable.
     *
     * @return true if the cell is a rim cell
     *
     * @test Test if the expected status for isRimCell is returned
     * for cells constructed with different combinations of parameters
     */
    bool isRimCell() { return details.rimCell; }

    /**
     * @brief Sets the color the cell will have after its next update.
     *
     * @param nextColor cell color after the next update
     *
     * @test Test if color for the next update is set properly by
     * first setting the next color, updating the cell and then getting
     * the new color to compare with the passed value.
     */
    void setNextColor(COLOR nextColor) { this->nextUpdate.nextColor = nextColor; }

    /**
     * @brief Function for getting the current cell value.
     *
     * @return the cell value
     *
     * @test Test if the default cell value '#' is returned
     * for cells constructed with different combinations of parameters
     *
     * @test Test if the expected cell value is returned by first setting the cell value,
     * updating the cell and then getting the new cell value to compare with the passed value.
     *
     */
    char getCellValue() { return details.value; }

    /**
     * @brief Sets the next character value of the cell, which will be printed to screen.
     *
     * @param value the new cell value
     *
     * @test Test if the cell value for the next generation is set properly by
     * first setting next cell value, updating the cell and then getting
     * the new cell value to compare with the passed value.
     */
    void setNextCellValue(char value) { nextUpdate.nextValue = value; }

    /**
     * @brief Sets whether the cell is alive/dead next generation.
     *
     * @param isAliveNext true if alive, false if dead
     *
     * @test Test if the value for willBeAlive is properly set by
     * first setting willBeAlive for the next generation,
     * updating the cell and then getting
     * the new value to compare with the passed value.
     */
    void setIsAliveNext(bool isAliveNext) { nextUpdate.willBeAlive = isAliveNext; }

    /**
     * @brief Will the cell be alive next generation?
     *
     * @return true if the cell will be alive
     *
     * @test Test if the expected value for willBeAlive is returned
     * for cells constructed with different combinations of parameters
     *
     */
    bool isAliveNext() { return nextUpdate.willBeAlive; }

    /**
     * @brief Gets the cells next action.
     *
     * @return the cells action for next generation
     *
     * @test Test if the expected value (DO_NOTHING) is returned
     * for cells constructed with different combinations of parameters
     */
    ACTION& getNextGenerationAction() { return nextUpdate.nextGenerationAction; }
};

#endif
