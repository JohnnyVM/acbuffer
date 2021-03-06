if(DEFINED ENV{CPPUTEST_HOME})
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

add_executable(tests
	src/main.cpp)

target_link_libraries(tests
	PRIVATE orm ${CPPUTEST_LDFLAGS})
target_include_directories(tests PRIVATE ${CPPUTEST_INCLUDE_DIRS})
target_link_directories(tests PRIVATE ${CPPUTEST_LIBRARIES})

if(RUN_TESTS)
add_custom_command(TARGET tests COMMAND ./tests POST_BUILD)
endif()
