cmake_minimum_required(VERSION 3.10)

project( canvas )

include_directories(./include)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)


set(SRCS
  ./src/canvas.cpp
  ./src/export_tga.cpp
)

add_library( canvas STATIC ${SRCS} )
