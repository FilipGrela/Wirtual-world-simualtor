#include <windows.h>
#include <iostream>

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

    cout << colored("Hello, World!", 0x0A) << endl; // Zielony tekst


    system("pause");
    return 0;
}