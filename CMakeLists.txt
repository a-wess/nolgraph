cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project( rays )

include_directories(
  ./
)

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

set(CORE
  ./core/camera.cpp
  ./core/renderer.cpp
)

set(IO_UTILS
  ./io_utils/canvas.cpp
  ./io_utils/export_tga.cpp
  ./io_utils/gltf.cpp
  ./io_utils/json.cpp
)

set(MATH)

set(SRCS
  ./main.cpp
  ${CORE}
  ${IO_UTILS}
  ${MATH}
)

add_executable(rays ${SRCS})
target_compile_features(rays PUBLIC cxx_std_17)

#set(TEST
#  ./src/camera.cpp
# ./src/renderer.cpp
#./src/json.cpp
#./src/gltf.cpp
#)

#add_executable(test ${TEST})
#target_compile_features(test PUBLIC cxx_std_17)

#target_link_libraries( rays canvas )
