#pragma once
#include <string>
#include <ctime>

struct StudySession {
    std::string date;
    int seconds;
    std::string subject;
};

class Timer {
private:
    bool isRunning;
    time_t startTime;
    int elapsedSeconds;
    std::string currentSubject;

public:
    Timer();
    void start(const std::string& subject);
    void stop();
    void pause();
    void resume();
    int getElapsedSeconds() const;
    bool getIsRunning() const;
    std::string getCurrentSubject() const;
    std::string getFormattedTime() const;
    void reset();
};
