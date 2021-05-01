project(Google_tests)

add_subdirectory(./googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../include)
include_directories(.)

add_executable(Google_Tests_run
        test_all.cpp
        test_DLL.cpp
        test_SLL.cpp
        test_matrix.cpp
#        test_ht.cpp
)

set_property(TARGET Google_Tests_run PROPERTY CXX_STANDARD 20)

target_link_libraries(Google_Tests_run PRIVATE gtest gtest_main ${LIB_NAME})
