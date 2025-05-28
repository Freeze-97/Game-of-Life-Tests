/*
 * Filename    RuleFactory.h
 * Author      Erik Ström
 * Date        July 2019
 * Version     0.2
*/

#ifndef RULEFACTORY_H
#define RULEFACTORY_H

#include "GoL_Rules/RuleOfExistence.h"

// Singleton class to handle creation of RulesOfExistence objects.
class RuleFactory
{
private:
    RuleFactory() = default;

public:
    static RuleFactory& getInstance();
    RuleOfExistence* createAndReturnRule(map<Point, Cell>& cells, const string& ruleName = "conway");
};

#endif