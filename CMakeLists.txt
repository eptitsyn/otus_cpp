cmake_minimum_required(VERSION 3.2)

project(otus_cpp)

#add_subdirectory(hw1)
#add_subdirectory(hw2)
#add_subdirectory(hw3)
#add_subdirectory(hw4)
#add_subdirectory(hw5)
#add_subdirectory(hw6)
add_subdirectory(hw7)
add_subdirectory(gtest)

enable_testing()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
