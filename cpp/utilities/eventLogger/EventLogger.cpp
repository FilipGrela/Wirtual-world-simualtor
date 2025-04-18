//
// Created by Filip on 14/04/2025.
//

#include "EventLogger.h"
#include <chrono>

void EventLogger::logEvent(const std::string &event) {
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);
  auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

  std::ostringstream timestamp_stream;
  timestamp_stream << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S")
                   << "." << std::setfill('0') << std::setw(5) << now_ms.count();

  std::string timestamp = timestamp_stream.str();
  std::string log = "[" + timestamp + "] " + event;
  events.push_back(log);
}
void EventLogger::displayAndClear() {
    bool alternateColor = false;
    for (const auto &event : events) {
        if (alternateColor) {
            std::cout << "\033[1;31m" << event << "\033[0m" << std::endl; // Czerwony kolor
        } else {
            std::cout << event << std::endl; // Domyślny kolor
        }
        alternateColor = !alternateColor;
    }
    events.clear();
}