#include <windows.h>
#include <iostream>
#include "organism/animal/species/Wolf.h"
#include "world/World.h"

using namespace std;

auto colored(const string& text, int color) {
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

    World world(10, 10);

    // Dodaj wilka do świata
world.addOrganism(new Wolf(Point(0, 0), world));


    // Pętla symulacji
    world.draw();
    while (true) {
        system("pause");
        world.executeTurn();
        system("cls");
        world.draw();
    }

    return 0;
}