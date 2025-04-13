#include <windows.h>
#include <iostream>
#include <conio.h>
#include "organism/animal/species/Wolf.h"
#include "world/World.h"

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

int main() {
    initializeConsole();

    World world(9, 9);

    // Dodaj wilka do świata
    world.addOrganism(new Wolf(Point(4, 4), world));


    world.draw();
    bool running = true;
    while (running) {

        switch (_getch()) {
            case 'q' or 27: // q lub ESC
                running = false;
                break;
            case 72: // Strzałka w górę
                break;
            case 80: // Strzałka w dół
                break;
            case 75: // Strzałka w lewo
                break;
            case 77: // Strzałka w prawo
                break;
            default:
                break;
        }

        world.executeTurn();
        system("cls");
        world.draw();
    }

    return 0;
}