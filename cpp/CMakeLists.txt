cmake_minimum_required(VERSION 3.30)
project(Projekt_1_programowanie_obiektowe)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projekt_1_programowanie_obiektowe main.cpp
        organism/Organism.cpp
        organism/Organism.h
        utilities/Point.cpp
        utilities/Point.h
        world/World.cpp
        world/World.h
        organism/animal/Animal.cpp
        organism/animal/Animal.h
        organism/animal/species/Human.cpp
        organism/animal/species/Human.h
        organism/animal/species/Wolf.cpp
        organism/animal/species/Wolf.h
        Constants.h
        utilities/eventLogger/EventLogger.cpp
        utilities/eventLogger/EventLogger.h
        organism/animal/species/Sheep.cpp
        organism/animal/species/Sheep.h
        organism/animal/species/Fox.cpp
        organism/animal/species/Fox.h
        #        organism/animal/species/Antelope.cpp
#        organism/animal/species/Antelope.h
#        organism/plant/Plant.cpp
#        organism/plant/Plant.h
#        organism/plant/species/Grass.cpp
#        organism/plant/species/Grass.h
#        organism/plant/species/Guarana.cpp
#        organism/plant/species/Guarana.h
#        organism/plant/species/NightshadeBerries.cpp
#        organism/plant/species/NightshadeBerries.h
#        organism/plant/species/HogweedOfPine.cpp
#        organism/plant/species/HogweedOfPine.h

)
