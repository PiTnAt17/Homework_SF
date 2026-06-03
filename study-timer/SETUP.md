# 🔧 Инструкция по установке и сборке Study Timer

## Системные требования

- **Windows 10+** / Linux / macOS
- **C++17 компилятор**
- **CMake 3.10+** (альтернативно: Make или ручная компиляция)

## Windows

### Вариант 1: Используя MSVC (Visual Studio)

```bash
# В папке study-timer
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
.\Release\study-timer.exe
```

### Вариант 2: Используя MinGW (g++)

1. Установите MinGW с поддержкой C++17
2. Используйте `build.bat`:
```bash
cd study-timer
build.bat
.\build\study-timer.exe
```

### Вариант 3: Используя CMake и Ninja

```bash
cd study-timer
mkdir build
cd build
cmake .. -G Ninja
ninja
.\study-timer.exe
```

## Linux / macOS

### Используя Make

```bash
cd study-timer
make
./study-timer
```

### Используя CMake

```bash
cd study-timer
mkdir build
cd build
cmake ..
make
./study-timer
```

## Компиляция вручную

### Windows (cmd)
```batch
cd study-timer
g++ -std=c++17 -Wall src/main.cpp src/timer.cpp src/storage.cpp src/ui.cpp -o study-timer.exe -I./include -lws2_32
```

### Linux/macOS (bash)
```bash
cd study-timer
g++ -std=c++17 -Wall src/main.cpp src/timer.cpp src/storage.cpp src/ui.cpp -o study-timer -I./include
```

## Проверка установки

После компиляции, запустите приложение:

```bash
./study-timer    # Linux/macOS
study-timer.exe  # Windows
```

Должно появиться красивое меню с опциями.

## Решение проблем

### "command not found: cmake"
→ Установите CMake с [cmake.org](https://cmake.org/download/)

### "command not found: g++"
→ Установите MinGW для Windows или gcc для Linux/Mac

### Ошибки компиляции
→ Убедитесь, что используется C++17 (`-std=c++17` флаг)

### "ENABLE_VIRTUAL_TERMINAL_PROCESSING not found"
→ Это нормально на старых Windows; приложение все равно будет работать
