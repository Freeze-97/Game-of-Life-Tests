# Terminal Cpp
Mikael Nilsson 2016

Terminal är ett plattforms oberoende bibliotek som kan användas för att rita ut grundläggande färger samt manipulera markören i terminal fönsteret. 

## Färger 
För att byta färger på tecken kan tre medlemsfunktioner användas.
### 1. pushColor, popColor
De här medlemsfunktionerna lämpa sig bäst då man har längre utskrifter som ska skrivas ut i samma färg.

```c++
Terminal terminal;
terminal.clear();
terminal.pushColor(TerminalColor(COLOR::BLUE, COLOR::WHITE));
cout << "This text has a blue font and a white background color!" << endl;
terminal.popColor();
// Now the color is the same as before.
cout << "This text has the previous (default color)" << endl;
``` 

### 2. strColor
Den här funktionen lämpa sig bäst då man vill skriva ut enstaka ord i specifika färger. Den fungerar så att man får ett funktions objekt som ritar den angivna färg och det ända man behöver göra är att fylla i texten. 

```c++
auto cyan = terminal.strColor(TerminalColor(COLOR::CYAN, COLOR::BLACK));
cout << "This text has a " << cyan("word") << " with cyan color!" << endl;
``` 

### 3. color
Den här funktionen lämpar sig bäst då man vill skriva ut lite länge avsnitt i samma färg. Den fungerar så att man får ett funktions objekt som lägger till den angivna färgen.

```c++
auto green = terminal.color(TerminalColor(COLOR::GREEN, COLOR::BLACK));
auto red = terminal.color(TerminalColor(COLOR::RED));
cout << "This text has a " << green << "sentence in green color!" << red <<
    " and this one is in red. (this is similar to pushColor but it can be done inside cout)" << endl;
terminal.popColor();
cout << "Use popColor to remove a color from the stack or";
terminal.clearColors();
cout << " clearColors to remove all colors!";
``` 

## Ändra markörens position
För att ända markörens position finns två medlemsfunktioner
### 1. position
Används för att få ut ett positions objekt som kan användas inuti cout för att flytta markören.

```c++
auto pos = terminal.position();
cout << "AAA Hopp" << pos(1,1) << "Hej" << endl;
``` 

### 2. setCursor
Används för att flytta markören.

```c++
terminal.setCursor(1,1);
cout << "Set the cursor to the upper left corner, this is equal to calling .resetCursor()" << endl;
``` 
## Övriga medlemsfunktioner
### clearColors
Används för att rensa alla färger som används. 

```c++
terminal.clearColors();
```

### clear
Används för att tömma terminalfönstret, färgerna på stacken samt flytta markören till position 1,1.

```c++
terminal.clear();
``` 

### resetCursor
Används för att sätta markören till position 1,1.

```c++
terminal.resetCursor();
``` 

### showCursor
Används för att gömma respektive visa markören.

```c++
// Göm markören
terminal.showCursor(false);
// Visa markören
terminal.showCursor(false);
```