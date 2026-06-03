#pragma once
#include <vector>
#include <string>
#include <map>
#include "timer.h"

class Storage {
private:
    std::string dataFile;

public:
    Storage(const std::string& filePath = "study_stats.json");
    void saveSession(const StudySession& session);
    std::vector<StudySession> loadSessions();
    std::map<std::string, int> getStatsByDate(const std::string& date);
    std::map<std::string, int> getStatsLastWeek();
    std::map<std::string, int> getStatsBySubject();
    int getTotalTimeToday();
};
