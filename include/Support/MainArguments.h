/*
 * Filename    MainArguments.h
 * Author      Erik Ström
 * Date        July 2019
 * Version     0.2
*/

#ifndef GAMEOFLIFE_MAINARGUMENTS_H
#define GAMEOFLIFE_MAINARGUMENTS_H

#include "Globals.h"
#include "ScreenPrinter.h"
#include <sstream>
#include <string>
#include <utility>

using namespace std;

struct ApplicationValues {
    bool runSimulation = true;
    string evenRuleName, oddRuleName;
    int maxGenerations = 100;

};

class BaseArgument {
protected:
    const string argValue;

    // inform the user that no value was provided for the argument
    void printNoValue();

public:
    explicit BaseArgument(string argValue) : argValue(std::move(argValue)) {}
    virtual ~BaseArgument() = default;
    virtual void execute(ApplicationValues& appValues, char* value = nullptr) = 0;

    const string& getValue() { return argValue; }
};

// Help screen
class HelpArgument : public BaseArgument {
public:
    HelpArgument() : BaseArgument("-h") {}
    ~HelpArgument() override = default;

    void execute(ApplicationValues& appValues, char* value) override;
};

// Amount of generations to simulate
class GenerationsArgument : public BaseArgument {
public:
    GenerationsArgument() : BaseArgument("-g") {}
    ~GenerationsArgument() override = default;

    void execute(ApplicationValues& appValues, char* generations) override;
};

// Custom population size
class WorldsizeArgument : public BaseArgument {
public:
    WorldsizeArgument() : BaseArgument("-s") {}
    ~WorldsizeArgument() override = default;

    void execute(ApplicationValues& appValues, char* dimensions) override;
};

// Initiate population from file
class FileArgument : public BaseArgument {
public:
    FileArgument() : BaseArgument("-f") {}
    ~FileArgument() override = default;

    void execute(ApplicationValues& appValues, char* fileNameArg) override;
};

// Rule used for even generations
class EvenRuleArgument : public BaseArgument {
public:
    EvenRuleArgument() : BaseArgument("-er") {}
    ~EvenRuleArgument() override = default;

    void execute(ApplicationValues& appValues, char* evenRule) override;
};

// Rule used for odd generations
class OddRuleArgument : public BaseArgument {
public:
    OddRuleArgument() : BaseArgument("-or") {}
    ~OddRuleArgument() override = default;

    void execute(ApplicationValues& appValues, char* oddRule) override;
};

#endif //GAMEOFLIFE_MAINARGUMENTS_H
