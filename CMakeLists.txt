cmake_minimum_required(VERSION 3.17)
project(OpenGLabs)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab11 lab11/main.cpp
        lab11/Car.cpp
        lab11/Car.h
        )

add_executable(lab12 lab12/main.cpp
        )

# CHANGE THIS PATH TO YOURS
set(OPENGL_DIRS D:/MyLibraries/gl/)

set(FREEGLUT_DIRS ${OPENGL_DIRS}/freeglut/)
set(GLEW_DIRS ${OPENGL_DIRS}/glew-1.11.0/)

include_directories(lab12 ${FREEGLUT_DIRS}/include/)
include_directories(lab12 ${GLEW_DIRS}/include/)

set(LIBS_DIRS ${FREEGLUT_DIRS}/lib/freeglut.lib ${GLEW_DIRS}/lib/glew32.lib)

# ADD SIMILAR LINES WHEN CREATING NEW EXECUTABLE
target_link_libraries (lab12 ${LIBS_DIRS})
