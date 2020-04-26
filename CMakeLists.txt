cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project( rays )

include_directories(
  include/
)

find_package(Threads)

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

set(CORE
  ./src/core/camera.cpp
  ./src/core/renderer.cpp
  ./src/core/scene.cpp
)

set(IO_SYSTEM
  ./src/io_system/canvas.cpp
  ./src/io_system/export_tga.cpp
  ./src/io_system/gltf.cpp
  ./src/io_system/json.cpp
  )

set(PRIMITIVES
  ./src/primitives/triangle.cpp
 )

set(SRCS
  ./src/main.cpp
  ${CORE}
  ${IO_SYSTEM}
  ${PRIMITIVES}
)

add_executable(rays ${SRCS})
target_compile_features(rays PUBLIC cxx_std_17)
target_link_libraries(rays ${CMAKE_THREAD_LIBS_INIT})
#set(TEST
#  ./src/camera.cpp
# ./src/renderer.cpp
#./src/json.cpp
#./src/gltf.cpp
#)

#add_executable(test ${TEST})
#target_compile_features(test PUBLIC cxx_std_17)

#target_link_libraries( rays canvas )
