/*
 * Autor       : Mikael Nilsson
 * Filename    : main.cpp
 * Description : Exemple program using Terminal lib.
 *
*/

#include "terminal.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "This text has the default color" << endl;

    Terminal terminal;
    //terminal.clear();
    //terminal.resetCursor();

    // Using colors!
    // Using push and pop color.
    terminal.pushColor(TerminalColor(COLOR::BLUE, COLOR::WHITE));
    cout << "This text has a blue font and a white background color!" << endl;
    terminal.popColor();
    // Now the color is the same as before.
    cout << "This text has the previous (default color)" << endl;

    // Using strColor
    auto cyan = terminal.strColor(TerminalColor(COLOR::CYAN, COLOR::BLACK));
    cout << "This text has a " << cyan("word") << " with cyan color!" << endl;

    // Using color
    auto green = terminal.color(TerminalColor(COLOR::GREEN, COLOR::BLACK));
    auto red = terminal.color(TerminalColor(COLOR::RED));
    cout << "This text has a " << green << "sentence in green color!" << red <<
            " and this one is in red. (this is similar to pushColor but it can be done inside cout)" << endl;
    terminal.popColor();
    cout << "Use popColor to remove a color from the stack or";
    terminal.clearColors();
    cout << " clearColors to remove all colors!";

    // Using cursor
    cout << "Press enter to continue" << endl;
    cin.get();
    terminal.clear();

    terminal.setCursor(1,1);
    cout << "Set the cursor to the upper left corner, this is equal to calling .resetCursor()" << endl;
    terminal.showCursor(false);
    cout << "Now the terminal cursor is invisible!" << endl;

    cout << "Press enter to continue" << endl;
    cin.get();
    terminal.clear();

    auto pos = terminal.position();
    cout << "AAA Hopp" << pos(1,1) << "Hej" << endl;
    return 0;
}
