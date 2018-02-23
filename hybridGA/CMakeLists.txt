cmake_minimum_required(VERSION 2.8.4)
project(hybridGA)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake) # add custom package modules


find_package (Threads)

# Include generated headers.
include_directories(${CMAKE_CURRENT_BINARY_DIR})



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -fsplit-stack -g -Werror=return-type -fvisibility=hidden -ggdb3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -fsplit-stack -Werror=return-type -fvisibility=hidden -ggdb3")




#source files
set(SOURCE_FILES
        RealChromosome.cpp
        RealChromosome.h
        RealGA.cpp
        RealGA.h
        BinChromosome.cpp
        BinChromosome.h
        BinGA.cpp
        BinGA.h
        cec17_test_func.cpp
        main.cpp
#        test.cpp
        )

add_executable(hybridGA ${SOURCE_FILES})

set(CURL_LIBRARY "-lcurl")

target_link_libraries(hybridGA -pthread ${CMAKE_THREAD_LIBS_INIT} )
