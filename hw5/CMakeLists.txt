cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(hw5 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hw5 VERSION 0.0.1)
endif()

add_subdirectory(docs)

add_executable(editor src/main.cpp)

target_include_directories(editor PRIVATE ${PROJECT_SOURCE_DIR}/src)

set_target_properties(editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

if (MSVC)
    target_compile_options(editor PRIVATE
        /W4
    )
else ()
    target_compile_options(editor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

#add_executable(gtest_hw4 tests/gtest_unittest.cpp)
#target_link_libraries(gtest_hw4 gtest_main)
#target_include_directories(gtest_hw4 PRIVATE ${PROJECT_SOURCE_DIR}/src)
#set_property(TARGET gtest_hw4 PROPERTY CXX_STANDARD 17)

