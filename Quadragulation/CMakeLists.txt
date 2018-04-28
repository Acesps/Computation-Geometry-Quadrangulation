cmake_minimum_required(VERSION 3.2)
project(ComputationalGeometry)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES
    include/*.h
    include/*.hpp
    src/*.cpp
    main.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )

add_executable(ComputationalGeometry ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(ComputationalGeometry ${OpenCV_LIBS} )
