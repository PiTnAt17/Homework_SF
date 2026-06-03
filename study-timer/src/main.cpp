#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "timer.h"
#include "storage.h"
#include "ui.h"

int main() {
    setlocale(LC_ALL, "");

    UI ui;
    Storage storage("study_stats.json");
    Timer timer;

    bool running = true;

    while (running) {
        ui.clear();
        ui.printHeader();
        ui.printMenu();

        char choice;
        std::cin >> choice;

        switch (choice) {
            case '1': {
                ui.clear();
                ui.printHeader();

                std::string subject;
                std::cout << "Введите название предмета: ";
                std::cin.ignore();
                std::getline(std::cin, subject);

                timer.start(subject);

                bool timerRunning = true;
                while (timerRunning) {
                    ui.printTimer(timer);

                    char input;
                    std::cin >> input;

                    if (input == 'q' || input == 'Q') {
                        time_t now = time(nullptr);
                        struct tm* timeinfo = localtime(&now);
                        std::ostringstream oss;
                        oss << (timeinfo->tm_year + 1900) << "-"
                            << (timeinfo->tm_mon + 1) << "-"
                            << timeinfo->tm_mday;

                        StudySession session;
                        session.date = oss.str();
                        session.seconds = timer.getElapsedSeconds();
                        session.subject = subject;

                        timer.stop();
                        storage.saveSession(session);
                        timerRunning = false;

                        std::cout << "\n✓ Сессия сохранена!\n";
                        std::cout << "Нажмите Enter для возврата в меню...";
                        std::cin.ignore();
                    } else if (timer.getIsRunning()) {
                        timer.pause();
                    } else {
                        timer.resume();
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                break;
            }

            case '2': {
                if (timer.getIsRunning()) {
                    timer.stop();
                    std::cout << "\n⏸ Таймер остановлен\n";
                } else {
                    std::cout << "\n⚠ Таймер не запущен\n";
                }
                std::cout << "Нажмите Enter...";
                std::cin.ignore();
                std::cin.ignore();
                break;
            }

            case '3': {
                ui.printStatsToday(storage);
                break;
            }

            case '4': {
                ui.printWeekStats(storage);
                break;
            }

            case '5': {
                ui.printSubjectStats(storage);
                break;
            }

            case '0': {
                if (timer.getIsRunning()) {
                    timer.stop();
                }
                std::cout << "\n\nСпасибо за использование Study Timer!\n";
                running = false;
                break;
            }

            default: {
                std::cout << "\n❌ Неверный выбор. Попробуйте снова.\n";
                std::cout << "Нажмите Enter...";
                std::cin.ignore();
                std::cin.ignore();
            }
        }
    }

    return 0;
}
