//
// Created by Filip on 22/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_SAVEMANAGER_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_SAVEMANAGER_H

#include "../nlohmann/json.hpp"
#include "../world/World.h"
#include <string>

class SaveManager {
public:
    static void saveWorldToFile(const World &world, const std::string &filename);
    static void loadWorldFromFile(World &world, const std::string &filename);

private:
    static nlohmann::json readJsonFromFile(const std::string &filename);
    static void initializeWorld(World &world, const nlohmann::json &j);
    static void loadOrganisms(World &world, const nlohmann::json &organismsJson);
    static Organism *createOrganismFromJson(const nlohmann::json &organismJson, World &world);
};

#endif// PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_SAVEMANAGER_H