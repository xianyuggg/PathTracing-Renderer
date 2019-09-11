cmake_minimum_required(VERSION 3.13)
project(PathTracing)

set(CMAKE_CXX_STANDARD 11)


# 设置编译选项
# 允许c++11标准、O3优化、多线程。match选项可避免一些cpu上的问题
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -O3 -pthread")
add_executable(PathTracing main.cpp const/Constant.cpp const/Constant.h object/Object.h const/Ray.h const/Vec.cpp const/Vec.h object/Plane.cpp object/Plane.h object/Spheres.cpp object/Spheres.h world&camera/World.cpp world&camera/World.h world&camera/Camera.h object/Texture.cpp object/Texture.h object/Obj.cpp object/Obj.h object/KdTree.cpp object/KdTree.h object/AABB.cpp object/AABB.h object/Face.h)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(PathTracing ${OpenCV_LIBS})