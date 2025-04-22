//
// Created by Filip on 14/04/2025.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>

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
