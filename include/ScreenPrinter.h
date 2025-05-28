/*
 * Filename    ScreenPrinter.h
 * Author      Erik Ström
 * Date        July 2019
 * Version     0.2
*/



#ifndef screenPrinterH
#define screenPrinterH


#include "../terminal/terminal.h"
#include "Cell_Culture/Population.h"

// Responsible for visually representing the simulation world on screen.
class ScreenPrinter {

private:
    Terminal terminal;

    ScreenPrinter() = default;

public:
    static ScreenPrinter& getInstance() {
        static ScreenPrinter instance;
        return instance;
    }


    void printBoard(Population& population);

    void printHelpScreen();

    void printMessage(const string& message);

    void clearScreen();
};

#endif
