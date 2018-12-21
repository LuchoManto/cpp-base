cmake_minimum_required(VERSION 3.13.2)
project(cpp-base)
 
# Use c++11
set (CMAKE_CXX_STANDARD 11)

#source and include files
file(GLOB SOURCES "src/*.cpp")
include_directories(include) 

#Main executable
add_executable(hellosum ${SOURCES})


#--- TESTING

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR test/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable
file(GLOB TEST_SOURCES test/*.cpp)
add_executable(runtest ${TEST_SOURCES})
target_link_libraries(runtest Catch)

#to execute tests when targeting test
add_custom_target(test
COMMAND ./runtest
DEPENDS runtest
WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
 