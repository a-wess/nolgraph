cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project( rays )

include_directories(
  src/
)

find_package(Threads)

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

set(ACC_STRUCTS
  ./src/acc_structs/bvh.cpp
  ./src/acc_structs/bbox.cpp
  ./src/acc_structs/primitive.cpp
)

set(CORE
  ./src/core/camera.cpp
  ./src/core/renderer.cpp
  ./src/core/scene.cpp
  ./src/core/primitives/triangle.cpp
  ./src/core/primitives/quad.cpp
)

set(IO_SYSTEM
  ./src/io/canvas.cpp
  ./src/io/export_tga.cpp
  ./src/io/obj_loader.cpp
)

set(SRCS
  ./src/main.cpp
  ${CORE}
  ${IO_SYSTEM}
  ${ACC_STRUCTS}
)

add_executable(rays ${SRCS})
target_compile_features(rays PUBLIC cxx_std_17)
target_link_libraries(rays ${CMAKE_THREAD_LIBS_INIT})

#Tests
set(TESTS
  src/test/test_define.cpp
  src/test/primitives.cpp
)
add_executable(test ${TESTS} ${CORE} ${ACC_STRUCTS})
target_link_libraries(test ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(test PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)