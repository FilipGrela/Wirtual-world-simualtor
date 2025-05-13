//
// Created by Filip on 23/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_UTILITIES_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_UTILITIES_H

#include <string>
#include <windows.h>
#include "../world/World.h"
#include "../utilities/SaveManager.h"

class Utilities {
    SaveManager saveManager;
public:
    void initializeConsole();
    void displayWelcomeScreen();
    void displayHelpScreen();
    void handleSpecialKeys(char key, bool &running, World &world);
    void addDefoultOrganisms(World &world);
    void endGame(World &world);
    std::string colored(const std::string &text, int color);
};

#endif // PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_UTILITIES_H
