cmake_minimum_required(VERSION 2.8.4)
project(bin_realGA)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake) # add custom package modules


find_package (Threads)

MESSAGE(STATUS "JSON Headers: ${JSON_INCLUDE_DIR}")

# Include generated headers.
include_directories(${CMAKE_CURRENT_BINARY_DIR})



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -g -Werror=return-type -fvisibility=hidden -ggdb3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror=return-type -fvisibility=hidden -ggdb3")




#source files
set(SOURCE_FILES
        Chromosome.cpp
        Chromosome.h
        GA.cpp
        GA.h
#        main.cpp
                        )

add_executable(bin_realGA ${SOURCE_FILES})

set(CURL_LIBRARY "-lcurl")

target_link_libraries(bin_realGA -pthread ${CMAKE_THREAD_LIBS_INIT} )