//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../Constants.h"
#include "../utilities/Point.h"
#include "../world/World.h"
#include <vector>

class World; // Forward declaration

class Organism {
public:
  virtual ~Organism();

  // Metody abstrakcyjne`
  virtual void action();

/**
   * Handles the collision between this organism and another organism.
   *
   * @param other A reference to the other organism involved in the collision.
   * @return true if no organism is deleted as a result of the collision.
   */
  virtual bool collision(Organism &other) = 0;

  virtual Point getPosition();
  virtual Point setPosition(Point newPosition);
  virtual std::string getSymbol() const;
  virtual int getAge();
  virtual int setAge(int newAge);
  virtual int increaseAge();
  virtual void reproduce() = 0;
  virtual bool isHuman() const { return false; }
  virtual bool isSosnowskyHogweed() const { return false; }
  void move(Point newPosition);

  virtual void die();
  int getStrength() const;
  void setStrength(int strength);
  int getInitiative() const;
  Point getPreviousPosition() const;

  void changeSymbol(const std::string &newSymbol);

  virtual bool isPlant() const { return false; }

protected:
  Organism(Point point, std::string symbol, int strength, int initiative,
           World &world);
  virtual Point getNewPosition();

  Point position;
  Point previousPosition;

  std::string symbol;
  int strength;
  const int initiative;
  int age;

  World &world; // Referencja do świata, w którym znajduje się organizm
};
