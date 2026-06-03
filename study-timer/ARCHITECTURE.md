# 🏗️ Архитектура Study Timer

## Обзор компонентов

```
┌─────────────────────────────────────────┐
│           main.cpp (точка входа)       │
├─────────────────────────────────────────┤
│   ┌──────────────────────────────────┐  │
│   │  UI (интерфейс и отображение)   │  │
│   ├──────────────────────────────────┤  │
│   │  Timer (логика таймера)          │  │
│   ├──────────────────────────────────┤  │
│   │  Storage (сохранение данных)    │  │
│   └──────────────────────────────────┘  │
└─────────────────────────────────────────┘
```

## Описание классов

### Timer (timer.h/cpp)
**Ответственность:** Управление временем отслеживания

```cpp
class Timer {
    - isRunning: bool          // Работает ли таймер
    - startTime: time_t        // Когда начался отсчет
    - elapsedSeconds: int      // Всего накоплено секунд
    - currentSubject: string   // Текущий предмет
    
    + start(subject)           // Запустить таймер
    + stop()                   // Остановить и сохранить время
    + pause()                  // Пауза
    + resume()                 // Возобновить
    + getElapsedSeconds()      // Получить прошедшее время
    + getFormattedTime()       // Время в формате HH:MM:SS
}
```

### Storage (storage.h/cpp)
**Ответственность:** Сохранение и загрузка статистики

```cpp
class Storage {
    - dataFile: string         // Путь к JSON файлу
    
    + saveSession(session)     // Сохранить сессию
    + loadSessions()           // Загрузить все сессии
    + getStatsByDate(date)     // Статистика по дате
    + getStatsLastWeek()       // Статистика за неделю
    + getStatsBySubject()      // Статистика по предметам
    + getTotalTimeToday()      // Время за сегодня
}
```

### UI (ui.h/cpp)
**Ответственность:** Визуализация и взаимодействие с пользователем

```cpp
class UI {
    + printHeader()            // Вывести заголовок
    + printMenu()              // Вывести меню
    + printTimer(timer)        // Показать таймер в работе
    + printStats()             // Показать статистику
    + printColored(text, code) // Цветной вывод
    + printBox(title, content) // Бокс с содержимым
    + enableANSISupport()      // Включить цвета (Windows)
}
```

## Поток данных

```
1. Пользователь запускает программу (main)
   ↓
2. UI показывает меню
   ↓
3. Пользователь выбирает действие
   ↓
4. Если "Запустить":
   - Timer.start(subject)
   - Отсчитываем время
   - При выходе: Timer.stop()
   - Storage.saveSession(session)
   ↓
5. Если "Статистика":
   - Storage.loadSessions()
   - Storage.getStats*()
   - UI.printStats()
   ↓
6. Повторить меню
```

## Формат JSON

```json
[
  {
    "date": "YYYY-MM-DD",
    "seconds": 3600,
    "subject": "Название предмета"
  }
]
```

Каждая строка = одна учебная сессия с датой, временем и предметом.

## Расширения

### Добавить экспорт в CSV
```cpp
// В storage.cpp
void Storage::exportToCSV(const std::string& filename) {
    // Реализация
}
```

### Добавить уведомления
```cpp
// Новый файл: notifier.h/cpp
class Notifier {
    + sendNotification(message)
    + scheduleReminder(time)
}
```

### Добавить синхронизацию облака
```cpp
// Новый файл: cloud_sync.h/cpp
class CloudSync {
    + uploadStats()
    + downloadStats()
}
```

## Сборка проекта

**Зависимости:**
- Windows API (ws2_32) для консольных функций
- стандартная библиотека C++17

**Компиляция:** (см. SETUP.md)

## Инструменты разработки

- **Компилятор:** g++, MSVC, Clang (C++17+)
- **Отладка:** gdb, Visual Studio Debugger
- **Версионирование:** Git

## Изменение логики

### Чтобы добавить новый тип статистики:

1. Добавить метод в `Storage`:
```cpp
std::map<std::string, int> getStatsMonthly() {
    // Логика
}
```

2. Добавить метод в `UI`:
```cpp
void UI::printMonthlyStats(Storage& storage) {
    // Отображение
}
```

3. Обновить меню в `main.cpp`:
```cpp
case '6': {
    ui.printMonthlyStats(storage);
    break;
}
```
