# Projektets namn
project(GameOfLife)

# Minsta tillåtna cmake version
cmake_minimum_required(VERSION 3.2)

# Kompilera med c++ 11 stöd
set(CMAKE_CXX_STANDARD 11)

# Lägg till katalogen med våra bibliotek till INCLUDE path
# (i dessa kataloger kommer kompilatorn att leta efter de
# header filer som inkluderas i koden)
include_directories($ENV{TOOLS_INCLUDE} ${CMAKE_SOURCE_DIR}/include)

# Add terminal sub directory
add_subdirectory(terminal)

# Om Debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Debug mode
    message("Debug mode")
    add_definitions(-DDEBUG)
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Release mode.
    message("Release mode")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

set(SRC_LIST
        src/main.cpp
        include/Cell_Culture/Cell.h include/Support/FileLoader.h include/GameOfLife.h
        include/Support/Globals.h include/Support/MainArgumentsParser.h
        include/Cell_Culture/Population.h include/GoL_Rules/RuleFactory.h
        include/GoL_Rules/RuleOfExistence.h
        include/ScreenPrinter.h src/Cell_Culture/Cell.cpp
        src/Support/FileLoader.cpp src/GameOfLife.cpp
        src/Support/Globals.cpp src/Cell_Culture/Population.cpp
        src/GoL_Rules/RuleFactory.cpp src/GoL_Rules/RuleOfExistence.cpp
        src/ScreenPrinter.cpp include/GoL_Rules/RuleOfExistence_Conway.h
        src/GoL_Rules/RuleOfExistence_Conway.cpp include/GoL_Rules/RuleOfExistence_VonNeumann.h
        src/GoL_Rules/RulesOfExistence_VonNeumann.cpp include/GoL_Rules/RuleOfExistence_Erik.h
        src/GoL_Rules/RuleOfExistence_Erik.cpp include/Support/SupportStructures.h
        src/Support/MainArgumentsParser.cpp include/Support/MainArguments.h src/Support/MainArguments.cpp)

set(TEST_SRC_LIST
        test/test-main.cpp
        test/test-population.cpp
        test/test-cell.cpp
        test-GoL_Rules/test-main.cpp
        test-GoL_Rules/test-RuleFactory.cpp
        test-GoL_Rules/test-RuleOfExistence_VonNeumann.cpp
        test-GoL_Rules/test-RuleOfExistence_Erik.cpp
        test-GoL_Rules/test-RuleOfExistence_Conway.cpp
        include/Cell_Culture/Cell.h include/Support/FileLoader.h
        include/GameOfLife.h include/Support/Globals.h
        include/Support/MainArgumentsParser.h
        include/Cell_Culture/Population.h include/GoL_Rules/RuleFactory.h
        include/GoL_Rules/RuleOfExistence.h include/ScreenPrinter.h src/Cell_Culture/Cell.cpp
        src/Support/FileLoader.cpp src/GameOfLife.cpp src/Support/Globals.cpp src/Cell_Culture/Population.cpp
        src/GoL_Rules/RuleFactory.cpp src/GoL_Rules/RuleOfExistence.cpp src/ScreenPrinter.cpp
        include/GoL_Rules/RuleOfExistence_Conway.h src/GoL_Rules/RuleOfExistence_Conway.cpp
        include/GoL_Rules/RuleOfExistence_VonNeumann.h src/GoL_Rules/RulesOfExistence_VonNeumann.cpp
        include/GoL_Rules/RuleOfExistence_Erik.h src/GoL_Rules/RuleOfExistence_Erik.cpp
        include/Support/SupportStructures.h src/Support/MainArgumentsParser.cpp
        include/Support/MainArguments.h src/Support/MainArguments.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(Test-${PROJECT_NAME} ${TEST_SRC_LIST})

target_link_libraries(${PROJECT_NAME} Terminal)
target_link_libraries(Test-${PROJECT_NAME} Terminal)