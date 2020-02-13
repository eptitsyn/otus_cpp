cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(hw3 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hw3 VERSION 0.0.1)
endif()

add_executable(allocator src/main.cpp)

target_include_directories(allocator PRIVATE ${PROJECT_SOURCE_DIR}/src)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)




install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

#enable_testing()


#add_executable(gtest_unittest tests/gtest_unittest.cpp)
#target_link_libraries(gtest_unittest gtest_main ip_filter_lib)
#set_property(TARGET gtest_unittest PROPERTY CXX_STANDARD 17)
#add_test(gtest_unittest gtest_unittest)

