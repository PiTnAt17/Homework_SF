#include "storage.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <iostream>

Storage::Storage(const std::string& filePath) : dataFile(filePath) {}

std::string getDateString() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    std::ostringstream oss;
    oss << (timeinfo->tm_year + 1900) << "-"
        << (timeinfo->tm_mon + 1) << "-"
        << timeinfo->tm_mday;
    return oss.str();
}

void Storage::saveSession(const StudySession& session) {
    std::vector<StudySession> sessions = loadSessions();
    sessions.push_back(session);

    std::ofstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << dataFile << std::endl;
        return;
    }

    file << "[\n";
    for (size_t i = 0; i < sessions.size(); ++i) {
        file << "  {\n";
        file << "    \"date\": \"" << sessions[i].date << "\",\n";
        file << "    \"seconds\": " << sessions[i].seconds << ",\n";
        file << "    \"subject\": \"" << sessions[i].subject << "\"\n";
        file << "  }";
        if (i < sessions.size() - 1) file << ",";
        file << "\n";
    }
    file << "]\n";
    file.close();
}

std::vector<StudySession> Storage::loadSessions() {
    std::vector<StudySession> sessions;
    std::ifstream file(dataFile);

    if (!file.is_open()) {
        return sessions;
    }

    std::string line;
    StudySession current;
    bool inObject = false;

    while (std::getline(file, line)) {
        if (line.find("\"date\"") != std::string::npos) {
            size_t start = line.find("\"") + 1;
            size_t end = line.rfind("\"");
            current.date = line.substr(start, end - start);
        }
        if (line.find("\"seconds\"") != std::string::npos) {
            size_t start = line.find(":") + 1;
            current.seconds = std::stoi(line.substr(start));
        }
        if (line.find("\"subject\"") != std::string::npos) {
            size_t start = line.find("\"", line.find(":")) + 1;
            size_t end = line.rfind("\"");
            current.subject = line.substr(start, end - start);
            sessions.push_back(current);
        }
    }

    file.close();
    return sessions;
}

std::map<std::string, int> Storage::getStatsByDate(const std::string& date) {
    std::map<std::string, int> stats;
    std::vector<StudySession> sessions = loadSessions();

    for (const auto& session : sessions) {
        if (session.date == date) {
            stats[session.subject] += session.seconds;
        }
    }

    return stats;
}

std::map<std::string, int> Storage::getStatsLastWeek() {
    std::map<std::string, int> stats;
    std::vector<StudySession> sessions = loadSessions();

    time_t now = time(nullptr);
    for (int i = 0; i < 7; ++i) {
        time_t dayTime = now - (i * 86400);
        struct tm* timeinfo = localtime(&dayTime);
        std::ostringstream oss;
        oss << (timeinfo->tm_year + 1900) << "-"
            << (timeinfo->tm_mon + 1) << "-"
            << timeinfo->tm_mday;
        std::string date = oss.str();

        for (const auto& session : sessions) {
            if (session.date == date) {
                stats[date] += session.seconds;
            }
        }
    }

    return stats;
}

std::map<std::string, int> Storage::getStatsBySubject() {
    std::map<std::string, int> stats;
    std::vector<StudySession> sessions = loadSessions();

    for (const auto& session : sessions) {
        stats[session.subject] += session.seconds;
    }

    return stats;
}

int Storage::getTotalTimeToday() {
    std::string today = getDateString();
    auto stats = getStatsByDate(today);
    int total = 0;
    for (const auto& pair : stats) {
        total += pair.second;
    }
    return total;
}
