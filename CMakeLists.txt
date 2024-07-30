cmake_minimum_required(VERSION 3.10)

project(chess)

FILE(GLOB_RECURSE CURRENT_SOURCES src/*.cpp) 

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_package(Threads)
find_package(OpenCV REQUIRED)

add_executable(chess ${CURRENT_SOURCES})

target_include_directories(chess
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(chess ${OpenCV_LIBS})
target_link_libraries(chess ${WIRINGPI_LIBRARIES}) 
target_link_libraries(chess pthread) 
