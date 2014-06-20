enable_testing()
find_package(Check REQUIRED)

if (NOT CHECK_FOUND)
    message(STATUS "Skipping unit tests, Check library not found!")
else (NOT CHECK_FOUND)
    set(TEST_LIBS ${LIBS} ${CHECK_LIBRARIES} libh3)

    include_directories(${CHECK_INCLUDE_DIRS})
    # include_directories("${PROJECT_SOURCE_DIR}/include/r2")
    add_executable(test_h3 check_parser.c)
    target_link_libraries(test_h3 ${TEST_LIBS})

    add_custom_command(
        TARGET test_h3 POST_BUILD
        COMMENT "Running unit tests"
        COMMAND test_h3
    )
endif (NOT CHECK_FOUND)
