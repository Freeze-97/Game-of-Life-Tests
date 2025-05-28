/*
 * Filename    RuleOfExistence_Erik.h
 * Author      Erik Ström
 * Date        July 2019
 * Version     0.2
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
#define GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H

#include "RuleOfExistence.h"

/*
Erik's RuleOfExistence, based on Conway's rule while also differentiate the appearance of cells based on their age.

Concrete Rule of existence, implementing Erik's rule.
Sentient lifeforms is rarely created, but once in a while a cell has lived enough generations to become as wise as Erik.

- Once a cell has survived a minimum amount of generations it will recieve a color to distinguish itself from younger ones.
- If such a cell would then survive another set amount of generations, it will be marked with a value of **E**.
- In the extreme case, where the cell has achieved above requirements and is determined to be the oldest living cell, it will
become a **prime elder**, and have its color changed once again. A generation may only have one such elder.
*/
class RuleOfExistence_Erik : public RuleOfExistence
{
private:
    char usedCellValue;	// char value to differentiate very old cells.
    Cell* primeElder;

    void erikfyCell(Cell& cell, ACTION action);
    void setPrimeElder(Cell* newElder);

public:
    explicit RuleOfExistence_Erik(map<Point, Cell>& cells)
            : RuleOfExistence({2,3,3},
                              cells, ALL_DIRECTIONS, "erik"), usedCellValue('E') {
        primeElder = nullptr;
    }
    ~RuleOfExistence_Erik() override = default;

    void executeRule() override;

    /**
     * @test This function will check if cells should be declared old, elder or prime elder
     * @param cell - The cell we are controlling
     * @param action - What action has been taken,
     * if it's kill then ignore the rest of the function
     */
    void testErikfyCell(Cell& cell, ACTION action) {
        erikfyCell(cell, action);
    }
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_ERIK_H
