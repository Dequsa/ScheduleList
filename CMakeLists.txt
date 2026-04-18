cmake_minimum_required(VERSION 4.0)
project(ListScheduling)

set(CMAKE_CXX_STANDARD 20)

add_executable(ListScheduling main.cpp
        Task.cpp
        Task.h
        TaskArray.cpp
        TaskArray.h
        TaskScheduler.cpp
        TaskScheduler.h
        utility.cpp
        Cpu.cpp
        Cpu.h)
