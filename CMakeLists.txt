cmake_minimum_required(VERSION 3.16)
project(LabMat C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(
        LabMat
        src/main.c)
