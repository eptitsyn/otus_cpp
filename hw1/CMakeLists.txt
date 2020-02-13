cmake_minimum_required(VERSION 3.2)

if ($ENV{TRAVIS_BUILD_NUMBER})
    project(hw1 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hw1 VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(lib/version.h.in lib/version.h)

add_executable(helloworld_cli src/hw1.cpp)
add_library(helloworld_lib lib/lib.cpp)
add_executable(test_version tests/test_version.cpp)

include_directories(${PROJECT_SOURCE_DIR}/lib)

set_target_properties(helloworld_cli helloworld_lib test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"

)

target_include_directories(helloworld_cli
    PRIVATE "${PROJECT_SOURCE_DIR}/lib"
)

target_include_directories(test_version
    PRIVATE "${PROJECT_SOURCE_DIR}/lib"
    ${Boost_INCLUDE_DIR}
)

target_include_directories(helloworld_lib
    PRIVATE "${PROJECT_SOURCE_DIR}/lib"
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(helloworld_cli PUBLIC
    helloworld_lib
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    helloworld_lib
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld_lib PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

#add_test(test_version bin/test_version)

add_executable(gtest_version tests/gtest_version.cpp)
#add_library(gtest_version tests/gtest_version.cpp)
target_link_libraries(gtest_version gtest_main helloworld_lib)
set_property(TARGET gtest_version PROPERTY CXX_STANDARD 17)
add_test(gtest_version gtest_version)



