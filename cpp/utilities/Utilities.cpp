//
// Created by Filip on 23/04/2025.
//

#include "Utilities.h"
#include <conio.h>
#include "../organism/OrganismIncludes.h"
#include <iostream>

void Utilities::initializeConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    SetConsoleTextAttribute(hConsole, csbi.wAttributes | FOREGROUND_INTENSITY);
    SetConsoleOutputCP(CP_UTF8);
}

void Utilities::displayWelcomeScreen() {
    system("cls");
    std::cout << "=========================================\n";
    std::cout << "         WIRTUALNY SWIAT - SYMULATOR     \n";
    std::cout << "=========================================\n";
    std::cout << "Zasady gry:\n";
    std::cout << "1. Symulator przedstawia wirtualny swiat z roslinami i zwierzetami.\n";
    std::cout << "2. Kazdy organizm ma swoje unikalne zachowanie.\n";
    std::cout << "3. Czlowiek jest sterowany za pomoca strzalek na klawiaturze.\n";
    std::cout << "4. Celem gry jest przetrwanie jak najdluzej.\n";
    std::cout << "\nSterowanie:\n";
    std::cout << "  - Strzalki: Poruszanie czlowiekiem\n";
    std::cout << "  - Spacja: Aktywacja specjalnej umiejetnosci czlowieka\n";
    std::cout << "  - S: Zapis stanu gry\n";
    std::cout << "  - L: Wczytanie stanu gry\n";
    std::cout << "  - H: Wyswietlenie pomocy\n";
    std::cout << "  - Q: Wyjscie z gry\n";
    std::cout << "=========================================\n";
    std::cout << "Nacisnij dowolny klawisz, aby rozpoczac gre...\n";
    _getch();
}

void Utilities::displayHelpScreen() {
    system("cls");
    std::cout << "=========================================\n";
    std::cout << "                 POMOC                   \n";
    std::cout << "=========================================\n";
    std::cout << "Sterowanie:\n";
    std::cout << "  - Strzalki: Poruszanie czlowiekiem\n";
    std::cout << "  - Spacja: Aktywacja specjalnej umiejetnosci czlowieka\n";
    std::cout << "  - S: Zapis stanu gry\n";
    std::cout << "  - L: Wczytanie stanu gry\n";
    std::cout << "  - Q: Wyjscie z gry\n";
    std::cout << "=========================================\n";
    std::cout << "Nacisnij dowolny klawisz, aby wrocic do gry...\n";
    _getch();
}

void Utilities::endGame(World &world) {
    system("cls");
    std::cout << "==============================" << std::endl;
    std::cout << "       KONIEC GRY!           " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Liczba tur: " << world.getTurnCounter() << std::endl;
    std::cout << "Liczba organizmów: " << world.getOrganisms().size() << std::endl;
    std::cout << "Dziękujemy za grę!" << std::endl;
    std::cout << "==============================" << std::endl;
    _getch();
}

std::string Utilities::colored(const std::string &text, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    SetConsoleTextAttribute(hConsole, color);
    std::cout << text;

    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
    return "";
}

void Utilities::handleSpecialKeys(char key, bool &running, World &world) {
    switch (key) {
        case 'q':
            running = false;
            break;
        case 's':
            saveManager.saveWorldToFile(world, "save.json");
            system("cls");
            std::cout << "Stan gry zapisany!\n";
            _getch();
            break;
        case 'l':
            saveManager.loadWorldFromFile(world, "save.json");
            system("cls");
            std::cout << "Stan gry wczytany!\n";
            _getch();
            break;
        case 'h':
            displayHelpScreen();
            break;
        case ' ':
            world.activateHumanAbility();
            break;
        default:
            break;
    }
}

void Utilities::addDefoultOrganisms(World &world) {
    for (int i = 0; i < 2; ++i) {
        world.addOrganism(new SosnowskyHogweed(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Fox(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Sheep(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Turtle(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Wolf(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Dandelion(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Grass(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
        world.addOrganism(new Guarana(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
       world.addOrganism(new Belladonna(Point::generateRandomPoint(world.getWidth(), world.getHeight(), world.getRandomEngine()), world));
    }
}
