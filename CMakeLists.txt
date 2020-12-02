cmake_minimum_required(VERSION 3.15)
project(untitledGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitledGL main.cpp Car.cpp Car.h ChristmasTree.cpp ChristmasTree.h)

#absolute paths to freeglut
#include_directories(/usr/local/Cellar/freeglut/3.2.1_1/include)
#target_link_libraries(untitledGL /usr/local/Cellar/freeglut/3.2.1_1/lib/libglut.dylib)

include_directories(/usr/local/include/)

#freeglut
target_link_libraries(untitledGL /usr/local/lib/libglut.dylib /usr/local/lib/libSOIL.dylib)

#Apple's GLUT
#target_link_libraries(untitledGL "-framework GLUT")

target_link_libraries(untitledGL "-framework OpenGL")

#include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
#target_link_libraries(untitledGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})