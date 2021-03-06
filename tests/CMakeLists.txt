# cmakefile for check testing
# followed from http://isti.bitbucket.org/2012/06/01/cmake-check.html
#               http://johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html

enable_testing()
find_package(Check REQUIRED)

if (NOT CHECK_FOUND)
    message(STATUS "Skipping unit tests, Check library not found!")
else (NOT CHECK_FOUND)
    set(LIBS ${LIBS} ${CHECK_LIBRARIES} libh3)

    include_directories(. ${CHECK_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

    add_executable(bench_h3 bench_h3.c bench/bench.c)
    target_link_libraries(bench_h3 ${LIBS})

    # include_directories("${PROJECT_SOURCE_DIR}/include/r2")
    add_executable(test_h3 check_parser.c)
    target_link_libraries(test_h3 ${LIBS})

    add_test(test_h3 ${CMAKE_CURRENT_BINARY_DIR}/test_h3)

    add_custom_command(
        TARGET test_h3 POST_BUILD
        COMMENT "Running unit tests"
        COMMAND test_h3
    )
endif (NOT CHECK_FOUND)
