cmake_minimum_required(VERSION 3.10)
project(ThreadPoolProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

add_executable(ThreadPoolProject 
    src/ThreadPool.cpp 
    src/main.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(ThreadPoolProject PRIVATE Threads::Threads)
