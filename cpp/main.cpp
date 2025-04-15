#include "organism/animal/species/Fox.h"
#include "organism/animal/species/Sheep.h"
#include "organism/animal/species/Turtle.h"
#include "organism/animal/species/Wolf.h"
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

int main() {
  initializeConsole();

  World world(9, 9);

  world.addOrganism(new Sheep(Point(7, 5), world));
  world.addOrganism(new Sheep(Point(6, 5), world));

  world.addOrganism(new Turtle(Point(6, 1), world));
  world.addOrganism(new Turtle(Point(6, 1), world));

  world.draw();
  bool running = true;
  while (running) {

    switch (_getch()) {
    case 'q': // q
    case 27:  // ESC
      running = false;
      break;
    case 0: // Klawisze specjalne (np. strzałki)
    case 224: {
      switch (_getch()) {
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
      break;
    }
    default:
      break;
    }

    world.executeTurn();
    system("cls");
    world.draw();
    cout << "Długość getOrganisms " << world.getOrganisms().size() << endl;

    world.getLogger().displayAndClear();
  }

  return 0;
}