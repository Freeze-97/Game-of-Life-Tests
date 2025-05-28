/*
 * Filename    RuleOfExistence_VonNeumann.h
 * Author      Erik Ström
 * Date        July 2019
 * Version     0.2
*/

#ifndef GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
#define GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H

#include "RuleOfExistence.h"
/*
Von Neumann's RuleOfExistence, differs from Conway in that only 4 neighbours are accounted for.

Concrete Rule of existence, implementing Von Neumann's rule.
Only difference from Conway is that neighbours are determined using only cardinal directions (N, E, S, W).
*/
class RuleOfExistence_VonNeumann : public RuleOfExistence
{
private:

public:
    explicit RuleOfExistence_VonNeumann(map<Point, Cell>& cells)
            : RuleOfExistence({ 2,3,3 }, cells, CARDINAL, "von_neumann") {}
    ~RuleOfExistence_VonNeumann() override = default;

    void executeRule() override;
};

#endif //GAMEOFLIFE_RULEOFEXISTENCE_VONNEUMANN_H
