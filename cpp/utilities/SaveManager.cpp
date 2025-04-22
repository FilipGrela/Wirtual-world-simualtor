//
// Created by Filip on 22/04/2025.
//

#include "SaveManager.h"
#include "../nlohmann/json.hpp"
#include "../organism/OrganismIncludes.h"
#include "../world/World.h"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

void SaveManager::saveWorldToFile(const World &world, const std::string &filename) {
    json j;

    // Zapisz wymiary świata
    j["width"] = world.getWidth();
    j["height"] = world.getHeight();
    j["turnCounter"] = world.getTurnCounter();

    // Zapisz organizmy
    for (const auto &organism : world.getOrganisms()) {
        json organismJson;
        organismJson["symbol"] = organism->getSymbol();
        organismJson["x"] = organism->getPosition().x;
        organismJson["y"] = organism->getPosition().y;
        organismJson["strength"] = organism->getStrength();
        organismJson["initiative"] = organism->getInitiative();
        organismJson["age"] = organism->getAge();
        j["organisms"].push_back(organismJson);
    }

    // Zapisz do pliku
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku do zapisu.");
    }
    file << j.dump(4); // Formatowanie JSON z wcięciami
    file.close();
}

void SaveManager::loadWorldFromFile(World &world, const std::string &filename) {
    json j = readJsonFromFile(filename);
    initializeWorld(world, j);
    loadOrganisms(world, j["organisms"]);
}

json SaveManager::readJsonFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku do odczytu.");
    }

    json j;
    file >> j;
    file.close();
    return j;
}

void SaveManager::initializeWorld(World &world, const json &j) {
    world = World(j["width"], j["height"]);
}

void SaveManager::loadOrganisms(World &world, const json &organismsJson) {
    for (const auto &organismJson : organismsJson) {
        Organism *organism = createOrganismFromJson(organismJson, world);
        if (organism) {
            organism->setStrength(organismJson["strength"]);
            organism->setInitiative(organismJson["initiative"]);
            organism->setAge(organismJson["age"]);
            world.addOrganism(organism);
        }
    }
}

Organism* SaveManager::createOrganismFromJson(const json &organismJson, World &world) {
    Point position(organismJson["x"], organismJson["y"]);
    std::string symbol = organismJson["symbol"];

    if (symbol == Constants::Animal::Human::Symbol) {
        return new Human(position, world);
    } else if (symbol == Constants::Animal::Wolf::Symbol) {
        return new Wolf(position, world);
    } else if (symbol == Constants::Animal::Fox::Symbol) {
        return new Fox(position, world);
    } else if (symbol == Constants::Animal::Sheep::Symbol) {
        return new Sheep(position, world);
    } else if (symbol == Constants::Animal::Turtle::Symbol) {
        return new Turtle(position, world);
    } else if (symbol == Constants::Plant::Grass::Symbol) {
        return new Grass(position, world);
    } else if (symbol == Constants::Plant::Dandelion::Symbol) {
        return new Dandelion(position, world);
    } else if (symbol == Constants::Plant::Belladonna::Symbol) {
        return new Belladonna(position, world);
    } else if (symbol == Constants::Plant::Guarana::Symbol) {
        return new Guarana(position, world);
    } else if (symbol == Constants::Plant::SosnowskyHogweed::Symbol) {
        return new SosnowskyHogweed(position, world);
    }

    return nullptr;
}