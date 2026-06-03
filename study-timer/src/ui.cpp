#include "ui.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#endif

UI::UI() {
    enableANSISupport();
}

void UI::enableANSISupport() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void UI::clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UI::setCursorPosition(int x, int y) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hOut, pos);
#endif
}

void UI::printColored(const std::string& text, int colorCode) {
    std::cout << "\033[" << colorCode << "m" << text << "\033[0m";
}

void UI::printHeader() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════╗\n";
    printColored("║  ", 36);
    printColored("📚 STUDY TIMER - Подсчет учебного времени", 96);
    printColored("  ║\n", 36);
    std::cout << "╚═══════════════════════════════════════════╝\n\n";
}

void UI::printMenu() {
    std::cout << "┌─────────────────────────────────────────┐\n";
    std::cout << "│          " << "\033[92m" << "ГЛАВНОЕ МЕНЮ" << "\033[0m" << "            │\n";
    std::cout << "├─────────────────────────────────────────┤\n";
    std::cout << "│ " << "\033[92m" << "1" << "\033[0m" << " - Запустить таймер                    │\n";
    std::cout << "│ " << "\033[93m" << "2" << "\033[0m" << " - Остановить / Пауза                 │\n";
    std::cout << "│ " << "\033[94m" << "3" << "\033[0m" << " - Статистика за сегодня             │\n";
    std::cout << "│ " << "\033[94m" << "4" << "\033[0m" << " - Статистика за неделю              │\n";
    std::cout << "│ " << "\033[94m" << "5" << "\033[0m" << " - Статистика по предметам           │\n";
    std::cout << "│ " << "\033[91m" << "0" << "\033[0m" << " - Выход                              │\n";
    std::cout << "└─────────────────────────────────────────┘\n";
    std::cout << "\nВыберите пункт: ";
}

void UI::printTimer(const Timer& timer) {
    clear();
    printHeader();

    std::cout << "\n┌─────────────────────────────────────────┐\n";
    if (timer.getIsRunning()) {
        printColored("│  ", 92);
        printColored("▶ ТАЙМЕР РАБОТАЕТ", 92);
        printColored("  │\n", 92);
    } else {
        printColored("│  ", 91);
        printColored("⏸ ТАЙМЕР ОСТАНОВЛЕН", 91);
        printColored("  │\n", 91);
    }
    std::cout << "├─────────────────────────────────────────┤\n";
    std::cout << "│ Предмет: " << std::setw(32) << std::left << timer.getCurrentSubject() << " │\n";
    std::cout << "│ Время:   ";
    printColored(timer.getFormattedTime(), 96);
    std::cout << std::setw(24) << " " << "│\n";
    std::cout << "└─────────────────────────────────────────┘\n";

    if (timer.getIsRunning()) {
        std::cout << "\nНажмите Enter для паузы или введите 'q' для выхода: ";
    } else {
        std::cout << "\nНажмите Enter для возобновления: ";
    }
}

void UI::printBox(const std::string& title, const std::vector<std::string>& content) {
    int width = 45;
    std::cout << "┌" << std::string(width - 2, '─') << "┐\n";
    std::cout << "│ " << std::setw(width - 4) << std::left << title << " │\n";
    std::cout << "├" << std::string(width - 2, '─') << "┤\n";

    for (const auto& line : content) {
        std::cout << "│ " << std::setw(width - 4) << std::left << line << " │\n";
    }

    std::cout << "└" << std::string(width - 2, '─') << "┘\n";
}

void UI::printStatsToday(Storage& storage) {
    clear();
    printHeader();

    auto stats = storage.getStatsByDate(
        std::to_string(2024) + "-" +
        std::to_string(6) + "-" +
        std::to_string(3)
    );

    std::vector<std::string> content;
    if (stats.empty()) {
        content.push_back("Нет данных за сегодня");
    } else {
        int total = 0;
        for (const auto& pair : stats) {
            int hours = pair.second / 3600;
            int minutes = (pair.second % 3600) / 60;
            std::ostringstream oss;
            oss << pair.first << ": " << hours << "ч " << minutes << "м";
            content.push_back(oss.str());
            total += pair.second;
        }
        int hours = total / 3600;
        int minutes = (total % 3600) / 60;
        std::ostringstream oss;
        oss << "\033[92mИтого: " << hours << "ч " << minutes << "м\033[0m";
        content.push_back(oss.str());
    }

    printBox("СТАТИСТИКА НА СЕГОДНЯ", content);
    std::cout << "\nНажмите Enter для возврата в меню...";
    std::cin.ignore();
}

void UI::printSubjectStats(Storage& storage) {
    clear();
    printHeader();

    auto stats = storage.getStatsBySubject();

    std::vector<std::string> content;
    if (stats.empty()) {
        content.push_back("Нет данных");
    } else {
        for (const auto& pair : stats) {
            int hours = pair.second / 3600;
            int minutes = (pair.second % 3600) / 60;
            std::ostringstream oss;
            oss << pair.first << ": " << hours << "ч " << minutes << "м";
            content.push_back(oss.str());
        }
    }

    printBox("СТАТИСТИКА ПО ПРЕДМЕТАМ", content);
    std::cout << "\nНажмите Enter для возврата в меню...";
    std::cin.ignore();
}

void UI::printWeekStats(Storage& storage) {
    clear();
    printHeader();

    auto stats = storage.getStatsLastWeek();

    std::vector<std::string> content;
    if (stats.empty()) {
        content.push_back("Нет данных за неделю");
    } else {
        int total = 0;
        for (const auto& pair : stats) {
            int hours = pair.second / 3600;
            int minutes = (pair.second % 3600) / 60;
            std::ostringstream oss;
            oss << pair.first << ": " << hours << "ч " << minutes << "м";
            content.push_back(oss.str());
            total += pair.second;
        }
        int hours = total / 3600;
        int minutes = (total % 3600) / 60;
        std::ostringstream oss;
        oss << "\033[92mИтого за неделю: " << hours << "ч " << minutes << "м\033[0m";
        content.push_back(oss.str());
    }

    printBox("СТАТИСТИКА ЗА НЕДЕЛЮ", content);
    std::cout << "\nНажмите Enter для возврата в меню...";
    std::cin.ignore();
}
