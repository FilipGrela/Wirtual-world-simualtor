#include "organism/organismIncludes.h"
#include "utilities/SaveManager.h"
#include "world/World.h"
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

auto colored(const string &text, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Ustaw kolor tekstu
    SetConsoleTextAttribute(hConsole, color);
    cout << text;

    // Przywróć domyślne ustawienia konsoli
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);

    return "";
}

void initializeConsole() {
    // Ustawienia konsoli
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    SetConsoleTextAttribute(hConsole, csbi.wAttributes | FOREGROUND_INTENSITY);

    // Ustaw kodowanie UTF-8
    SetConsoleOutputCP(CP_UTF8);
}

void endGame(World &world) {
    system("cls");
    cout << "==============================" << endl;
    cout << "       KONIEC GRY!           " << endl;
    cout << "==============================" << endl;
    cout << "Liczba tur: " << world.getTurnCounter() << endl;
    cout << "Liczba organizmów: " << world.getOrganisms().size() << endl;
    cout << "Dziękujemy za grę!" << endl;
    cout << "==============================" << endl;
    system("pause");
}

void displayWelcomeScreen() {
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

void displayHelpScreen() {
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
    std::cout << "  - Spacja: Aktywacja specjalnej umiejetnosci czlowieka\n";
    std::cout << "=========================================\n";
    std::cout << "Nacisnij dowolny klawisz, aby wrocic do gry...\n";
    _getch();
}

void handleSpecialKeys(char key, bool &running, World &world) {
    switch (key) {
        case 'q':// Wyjscie
            running = false;
            break;
        case 's':// Zapis
            SaveManager::saveWorldToFile(world, "save.json");
            system("cls");
            std::cout << "Stan gry zapisany!\n";
            system("pause");
            break;
        case 'l':// Wczytanie
            SaveManager::loadWorldFromFile(world, "save.json");
            system("cls");
            std::cout << "Stan gry wczytany!\n";
            system("pause");
            break;
        case 'h':// Pomoc
            displayHelpScreen();
            break;
        case ' ':// Specjalna umiejętność człowieka
            world.activateHumanAbility();
            break;
        default:
            break;
    }
}

int main() {
    initializeConsole();
    displayWelcomeScreen();

    World world(41, 41);
    world.addOrganism(new Human(Point(world.getWidth() / 2, world.getHeight() / 2), world));

    // Dodaj inne organizmy...
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

    bool running = true;
    while (world.isHumanAlive()) {
        world.setHumanDirection(Constants::Direction::NONE);

        if (_kbhit()) {
            char key = _getch();
            if (key == 'q' || key == 's' || key == 'l' || key == 'h' || key == ' ') {
                handleSpecialKeys(key, running, world);
                continue;// Nie licz jako tura
            }
            // Obsługa strzałek
            if (key == -32){
                key = _getch();
            }
            switch (key) {
                case 72:// Strzałka w górę
                    world.setHumanDirection(Constants::Direction::UP);
                    break;
                case 80:// Strzałka w dół
                    world.setHumanDirection(Constants::Direction::DOWN);
                    break;
                case 75:// Strzałka w lewo
                    world.setHumanDirection(Constants::Direction::LEFT);
                    break;
                case 77:// Strzałka w prawo
                    world.setHumanDirection(Constants::Direction::RIGHT);
                    break;
            }
            world.executeTurn();
            system("cls");
            cout << "Autor: Filip Grela, 203850\n" << "Turn counter: " << world.getTurnCounter() << "\n";
            world.draw();
            world.getLogger().displayAndClear(5);
        }
    }

    endGame(world);
}