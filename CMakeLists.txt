cmake_minimum_required(VERSION 2.8)
project(MAIN)

if (EXISTS "${CMAKE_SOURCE_DIR}")
	#add_subdirectory(minisat)
else()
	message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
endif()

## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall --static ${CMAKE_CXX_FLAGS}")

set(MAIN Main_teste.cpp SatInstance.cpp)
add_executable(MAIN Main_teste.cpp SatInstance.cpp)

# create the main executable
# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)
## add additional .cpp files if needed
#add_executable(MAIN main.cpp)
# link minisat library with the main executable
target_link_libraries(MAIN libminisat.so)
