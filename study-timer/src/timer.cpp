#include "timer.h"
#include <cmath>
#include <iomanip>
#include <sstream>

Timer::Timer() : isRunning(false), startTime(0), elapsedSeconds(0), currentSubject("") {}

void Timer::start(const std::string& subject) {
    if (!isRunning) {
        isRunning = true;
        startTime = time(nullptr);
        currentSubject = subject;
    }
}

void Timer::stop() {
    if (isRunning) {
        time_t endTime = time(nullptr);
        elapsedSeconds += static_cast<int>(difftime(endTime, startTime));
        isRunning = false;
        startTime = 0;
    }
}

void Timer::pause() {
    stop();
}

void Timer::resume() {
    if (!isRunning && currentSubject != "") {
        start(currentSubject);
    }
}

int Timer::getElapsedSeconds() const {
    int total = elapsedSeconds;
    if (isRunning) {
        time_t now = time(nullptr);
        total += static_cast<int>(difftime(now, startTime));
    }
    return total;
}

bool Timer::getIsRunning() const {
    return isRunning;
}

std::string Timer::getCurrentSubject() const {
    return currentSubject;
}

std::string Timer::getFormattedTime() const {
    int seconds = getElapsedSeconds();
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << secs;
    return oss.str();
}

void Timer::reset() {
    isRunning = false;
    startTime = 0;
    elapsedSeconds = 0;
    currentSubject = "";
}
