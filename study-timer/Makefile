CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS =
SOURCES = src/main.cpp src/timer.cpp src/storage.cpp src/ui.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = study-timer

ifeq ($(OS),Windows_NT)
	TARGET = study-timer.exe
	LDFLAGS += -lws2_32
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -Iinclude

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Iinclude

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
