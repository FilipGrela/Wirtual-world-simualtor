#include "organism/organismIncludes.h"
#include "utilities/SaveManager.h"
#include "utilities/Utilities.h"
#include "world/World.h"
#include <conio.h>
#include <iostream>

using namespace std;


void addOrganisms(World &world) {
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

int main() {
    Utilities utilities;

    utilities.initializeConsole();
    utilities.displayWelcomeScreen();

    World world(41, 41);
    world.addOrganism(new Human(Point(world.getWidth() / 2, world.getHeight() / 2), world));

    addOrganisms(world);

    bool running = true;
    while (running) {
        world.setHumanDirection(Constants::Direction::NONE);

        if (_kbhit()) {
            char key = _getch();
            if (key == 'q' || key == 's' || key == 'l' || key == 'h' || key == ' ') {
                utilities.handleSpecialKeys(key, running, world);
                continue;
            }
            if (key == -32) {
                key = _getch();
            }
            switch (key) {
                case 72:
                    world.setHumanDirection(Constants::Direction::UP);
                    break;
                case 80:
                    world.setHumanDirection(Constants::Direction::DOWN);
                    break;
                case 75:
                    world.setHumanDirection(Constants::Direction::LEFT);
                    break;
                case 77:
                    world.setHumanDirection(Constants::Direction::RIGHT);
                    break;
            }
            world.executeTurn();
            system("cls");
            cout << "Autor: Filip Grela, 203850\n"
                 << "Turn number: " << world.getTurnCounter() << "\n";
            world.draw();
            world.getLogger().displayAndClear(5);
        }
    }
    utilities.endGame(world);
}