cmake_minimum_required(VERSION 3.10)
project(StudyTimer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(study-timer
    src/main.cpp
    src/timer.cpp
    src/storage.cpp
    src/ui.cpp
)

target_include_directories(study-timer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
    target_link_libraries(study-timer PRIVATE ws2_32)
endif()
