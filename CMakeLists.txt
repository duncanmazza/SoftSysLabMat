cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_NAME LabMat)
set(PROJECT_NAME SoftSys${EXECUTABLE_NAME})
set(LIB_NAME lib${EXECUTABLE_NAME})
set(LIB_SRC_DIR_NAME src)
project(SoftSys${PROJECT_NAME} C)

add_subdirectory(tests)
include_directories(.)
include_directories(include)

add_library(
        ${LIB_NAME}
        ${LIB_SRC_DIR_NAME}/cl_input.c
        ${LIB_SRC_DIR_NAME}/dll.c
        ${LIB_SRC_DIR_NAME}/sll.c
)

add_executable(
        ${EXECUTABLE_NAME}
        src/main.c
)

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE m ${LIB_NAME})  # Link math library
