cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(hw9 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hw9 VERSION 0.0.1)
endif()

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(docs)

add_executable(bayan src/main.cpp src/hash.cpp src/file.cpp src/bayan.cpp)

TARGET_LINK_LIBRARIES(bayan LINK_PUBLIC ${Boost_LIBRARIES} )

target_include_directories(bayan PRIVATE ${PROJECT_SOURCE_DIR}/src)

set_target_properties(bayan PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

if (MSVC)
    target_compile_options(bayan PRIVATE
        /W4
    )
else ()
    target_compile_options(bayan PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_executable(gtest_hw9 tests/gtest_unittest.cpp)
target_link_libraries(gtest_hw9 gtest_main)
target_include_directories(gtest_hw9 PRIVATE ${PROJECT_SOURCE_DIR}/src)
set_property(TARGET gtest_hw9 PROPERTY CXX_STANDARD 17)
add_test(gtest_hw9 gtest_hw9)
