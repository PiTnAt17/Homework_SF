#pragma once
#include <string>
#include <vector>
#include "timer.h"
#include "storage.h"

class UI {
public:
    UI();
    void enableANSISupport();
    void clear();
    void printHeader();
    void printMenu();
    void printTimer(const Timer& timer);
    void printStats(Storage& storage);
    void printStatsToday(Storage& storage);
    void printSubjectStats(Storage& storage);
    void printWeekStats(Storage& storage);
    void setCursorPosition(int x, int y);
    void printColored(const std::string& text, int colorCode);
    void printBox(const std::string& title, const std::vector<std::string>& content);
};
