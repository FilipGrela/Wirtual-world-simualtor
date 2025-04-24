//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_HUMAN_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_HUMAN_H

#include "../Animal.h"

class Human : public Animal {
public:
    Human(Point point, World &world);
    void reproduce() override;
    Point getNewPosition() override;
    bool isHuman() const override;
    void action() override;
    Organism *clone() const override;

    void die() override;

    void activateAbility();
    void setAbilityCooldown(int cooldown);
    int getAbilityyCooldown() const;
    void setAbilityDuration(int duration);
    int getAbilityDuration() const;
    void setAbilityActive(bool active);
    int getAbilityCooldown() const;
    bool isAbilityActive() const;

private:
    bool abilityActive = false;
    int abilityCooldown = 0;
    int abilityDuration = 0;

    void escapeToRandomPosition();
};

#endif// PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_HUMAN_H
