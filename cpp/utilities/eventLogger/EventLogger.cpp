//
// Created by Filip on 14/04/2025.
//

#include "EventLogger.h"
#include <chrono>

void EventLogger::logEvent(const std::string &event) {
  auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::string timestamp = ctime(&now);
  timestamp.pop_back(); // Usunięcie znaku nowej linii z końca
  events.push_back("[" + timestamp + "] " + event);
}

void EventLogger::displayAndClear() {
    for (const auto &event : events) {
        std::cout << event << std::endl;
    }
    events.clear();
}