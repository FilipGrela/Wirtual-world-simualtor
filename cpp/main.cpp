#include "organism/animal/species/Antelope.h"
#include "organism/animal/species/Fox.h"
#include "organism/animal/species/Human.h"
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

int main() {
  initializeConsole();

  World world(9, 9);

  world.addOrganism(
      new Human(Point(world.getWidth() / 2, world.getHeight() / 2), world));

  world.addOrganism(new Antelope(Point(7, 5), world));
  world.addOrganism(new Antelope(Point(6, 5), world));

  world.addOrganism(new Wolf(Point(6, 1), world));
  world.addOrganism(new Wolf(Point(6, 1), world));
  world.addOrganism(new Wolf(Point(6, 1), world));
  world.addOrganism(new Wolf(Point(6, 1), world));
  world.addOrganism(new Wolf(Point(6, 1), world));
  world.addOrganism(new Turtle(Point(6, 1), world));

  world.draw();
  bool running = true;
  while (running) {
    world.setHumanDirection(Constants::Direction::NONE);
    if (!world.getHumanAlive()) {
      running = false;
      endGame(world);
    }
    switch (_getch()) {
    case 'q': // q
    case 27:  // ESC
      running = false;
      break;
    case 0: // Klawisze specjalne (np. strzałki)
    case 224: {
      switch (_getch()) {
      case 72: // Strzałka w górę
        world.setHumanDirection(Constants::Direction::UP);
        break;
      case 80: // Strzałka w dół
        world.setHumanDirection(Constants::Direction::DOWN);
        break;
      case 75: // Strzałka w lewo
        world.setHumanDirection(Constants::Direction::LEFT);
        break;
      case 77: // Strzałka w prawo
        world.setHumanDirection(Constants::Direction::RIGHT);
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