cmake_minimum_required(VERSION 3.2)

project(otus_cpp)

add_subdirectory(hw1)
add_subdirectory(hw2)
add_subdirectory(gtest)

# Инструкция enable_testing неявно объявляет опцию BUILD_TESTING,
#  по умолчанию BUILD_TESTING=ON.
# Вызывайте `cmake -DBUILD_TESTING=OFF projectdir` из командной строки,
#  если не хотите собирать тесты.
enable_testing()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

