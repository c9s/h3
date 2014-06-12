cmake_minimum_required(VERSION 2.8)

PROJECT( h3 )

if(CMAKE_COMPILER_IS_GNUCC)
  SET(TARGET_COMPILE_FLAGS "-std=gnu++11") # Add C++11 support for GCC
endif()

set(TARGET_COMPILE_DEFS "_CRT_SECURE_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS;_BIND_TO_CURRENT_CRT_VERSION")

##########################################
# ------ Target: h3 ------------
set(h3ProjDir ${CMAKE_CURRENT_SOURCE_DIR})

set(h3_Header_Files 
        ${h3ProjDir}/include/h3.h
        ${h3ProjDir}/src/hash.h
        ${h3ProjDir}/src/mempool.h
        ${h3ProjDir}/src/scanner.h)

set(h3_Source_Files 
        ${h3ProjDir}/src/hash.c
        ${h3ProjDir}/src/header_field.c
        ${h3ProjDir}/src/header_field_list.c
        ${h3ProjDir}/src/mempool.c
        ${h3ProjDir}/src/request_header.c
        ${h3ProjDir}/src/scanner.c)

set(h3_Data_Files
        ${h3ProjDir}/t/data/01-chrome-github.txt
        ${h3ProjDir}/t/data/02-chrome-github.txt
        ${h3ProjDir}/t/data/03-firefox.txt)

set_source_files_properties(${h3ProjDir}/src/scanner.c PROPERTIES LANGUAGE CXX)

set(h3_Compile_Flags ${TARGET_COMPILE_FLAGS})
set(h3_Compile_Defs  ${TARGET_COMPILE_DEFS})
set(h3_Include_Dirs  ${h3ProjDir}/include ${h3ProjDir}/src)

set(h3_Dependencies )

add_library(h3 
	${h3_Source_Files}
	${h3_Header_Files}
    ${h3_Data_Files})
set_target_properties(h3 PROPERTIES 
    COMPILE_DEFINITIONS "${h3_Compile_Defs}" 
    COMPILE_FLAGS       "${h3_Compile_Flags}"
    INCLUDE_DIRECTORIES "${h3_Include_Dirs}"
    LINKER_LANGUAGE     CXX)
target_link_libraries(h3 ${h3_Dependencies})

###########################################
#  ------ Target: h3-test ----------

set(h3_test_Source_Files 
        ${h3ProjDir}/parser.c)
set(h3_test_Header_Files )
set(h3_test_Data_Files )

set(h3_test_Compile_Flags ${TARGET_COMPILE_FLAGS})
set(h3_test_Compile_Defs  ${TARGET_COMPILE_DEFS})
set(h3_test_Include_Dirs  ${h3_Include_Dirs})

set(h3_test_Dependencies h3)

add_executable(h3-test 
    ${h3_test_Source_Files}
    ${h3_test_Header_Files}
    ${h3_test_Data_Files})
set_target_properties(h3-test PROPERTIES 
    COMPILE_DEFINITIONS "${h3_test_Compile_Defs}" 
    COMPILE_FLAGS       "${h3_test_Compile_Flags}"
    INCLUDE_DIRECTORIES "${h3_test_Include_Dirs}")
target_link_libraries(h3-test ${h3_test_Dependencies})
