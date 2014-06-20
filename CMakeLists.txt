cmake_minimum_required(VERSION 2.8)
PROJECT( h3 )
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules ${PROJECT_SOURCE_DIR}/cmake)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

if(CMAKE_COMPILER_IS_GNUCC)
  SET(TARGET_COMPILE_FLAGS "-std=gnu++11") # Add C++11 support for GCC
endif()

include_directories(. ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/3rdparty /opt/local/include)
link_directories(${LINK_DIRECTORIES} . ${PROJECT_SOURCE_DIR}/src /opt/local/lib)
# include_directories(. ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/3rdparty ${PROJECT_SOURCE_DIR})
enable_testing()
# add_subdirectory(src)
add_subdirectory(tests)
