cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(hw10 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hw10 VERSION 0.0.1)
endif()

#install Intel TBB
include(${PROJECT_SOURCE_DIR}/../oneTBB/cmake/TBBGet.cmake)
tbb_get(TBB_ROOT tbb_root CONFIG_DIR TBB_DIR)
find_package(TBB REQUIRED tbb)

#add_subdirectory(docs)

add_executable(bulkmt src/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/../../oneTBB/include/)
target_include_directories(bulkmt PRIVATE ${PROJECT_SOURCE_DIR}/src )
target_include_directories(bulkmt PUBLIC ${PROJECT_SOURCE_DIR}/../../oneTBB/include/)
target_link_libraries(bulkmt ${TBB_IMPORTED_TARGETS})

set_target_properties(bulkmt PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

if (MSVC)
    target_compile_options(bulkmt PRIVATE
        /W4
    )
else ()
    target_compile_options(bulkmt PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

#add_executable(gtest_hw7 tests/gtest_unittest.cpp)
#target_link_libraries(gtest_hw7 gtest_main)
#target_include_directories(gtest_hw7 PRIVATE ${PROJECT_SOURCE_DIR}/src)
#set_property(TARGET gtest_hw7 PROPERTY CXX_STANDARD 17)
#add_test(gtest_hw7 gtest_hw7)
