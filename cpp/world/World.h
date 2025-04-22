//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../organism/Organism.h"
#include "../utilities/Point.h"
#include "../utilities/eventLogger/EventLogger.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <random>

class Organism;// Deklaracja wstępna

class World {
public:
    std::unordered_map<Constants::Direction, Point> directionToPoint = {
            {Constants::Direction::UP, Point(0, -1)},
            {Constants::Direction::DOWN, Point(0, 1)},
            {Constants::Direction::LEFT, Point(-1, 0)},
            {Constants::Direction::RIGHT, Point(1, 0)},
            {Constants::Direction::NONE, Point(0, 0)}};

    World(int width, int height);
    void draw();

    bool isOccupied(Point position) const;
    bool isInBounds(Point position) const;

    void executeTurn();

    void addOrganism(Organism *organism);
    void removeOrganism(Organism *organism);
    const std::vector<std::unique_ptr<Organism>> &getOrganisms() const;
    std::vector<Organism *> getOrganismsAt(Point position);
    const std::vector<std::unique_ptr<Organism>> &getOrganismsToAdd() const;

    Point getFreeSpace(Point &newPosition);
    EventLogger &getLogger();

    void queueOrganismAddition(Organism *organism);
    bool isStrongerOrganismAt(Point position, int strength) const;

    int incrementTurnCounter();
    int getTurnCounter() const;

    void setHumanDirection(enum Constants::Direction);
    enum Constants::Direction getHumanDirection() const;

    int getWidth() const;
    int getHeight() const;
    bool isHumanAlive() const;
    void setHumanAlive(bool alive);
    void activateHumanAbility();
    void killPlantsOnPosition(Point position);

    std::vector<Point> getNeighboringPositions(Point position);

    World &operator=(const World &other);
    bool containsOrganism(const Organism *organism) const;
    std::mt19937 &getRandomEngine();
private:
    const int width, height;
    int turnCounter = 0;// Licznik tur
    enum Constants::Direction humanDirection = Constants::Direction::NONE;
    bool humanAlive;
    bool humanAbilityActive = false;
    std::mt19937 randomEngine;

    EventLogger eventLogger;// Logger do rejestrowania zdarzeń

    std::vector<std::unique_ptr<Organism>>
            organisms, organismsToAdd;// vector to represent the organisms in the world, vector to represent the organisms to add to the world
};
