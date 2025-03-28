cmake_minimum_required(VERSION 3.10)

# Set the project name
project(TaskTracker)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(TaskTracker src/main.cpp)