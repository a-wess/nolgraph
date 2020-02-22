cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project( rays )

include_directories(
  ./include
  ./canvas/include
)

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

add_subdirectory(canvas)

set(SRCS 
  ./src/main.cpp
)

add_executable( rays ${SRCS} )
target_link_libraries( rays canvas )
