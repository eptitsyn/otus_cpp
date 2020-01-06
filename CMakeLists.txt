cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(opengl-samples)

# Лайфхак: объявленные в старшем CMakeLists функции
#  будут видны в подпроектах, включённых через add_subdirectory
#include(scripts/functions.cmake)

add_subdirectory(hw1)

# Инструкция enable_testing неявно объявляет опцию BUILD_TESTING,
#  по умолчанию BUILD_TESTING=ON.
# Вызывайте `cmake -DBUILD_TESTING=OFF projectdir` из командной строки,
#  если не хотите собирать тесты.
enable_testing()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
