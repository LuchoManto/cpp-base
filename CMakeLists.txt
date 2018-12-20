cmake_minimum_required(VERSION 3.13.2)
project(cpp-base)
 
# Use c++11
set (CMAKE_CXX_STANDARD 11)

#Bring the headers, such as Student.h into the project
include_directories(include)
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/main.cpp src/sum.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(hellosum ${SOURCES})



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
 