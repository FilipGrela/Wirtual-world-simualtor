//
// Created by Filip on 14/04/2025.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>

class EventLogger {
public:
    EventLogger() = default;

    void logEvent(const std::string &event);
    void displayAndClear();
    void displayAndClear(int numberOfEvents);

private:
        std::vector<std::string> events;
        std::string popEvent();
        void clearEvents();
};


