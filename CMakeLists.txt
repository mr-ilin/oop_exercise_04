cmake_minimum_required(VERSION 3.5)

project(oop_exercise_04)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(oop_exercise_04 main.cpp)
set_target_properties(oop_exercise_04 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
