cmake_minimum_required(VERSION 3.17)
project(OpenGLabs)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab11 lab11/main.cpp lab11/Car.cpp lab11/Car.h)
add_executable(lab12 lab12/main.cpp)
add_executable(lab13 lab13/main.cpp common/model3D.cpp common/model3D.h)
add_executable(ind3kostikova ind3kostikova/main.cpp)

# MAIN PATHS AND LIBS
set(OPENGL_DIRS C:/Users/Lereena/gl)
set(FREEGLUT_DIRS ${OPENGL_DIRS}/freeglut/)
set(GLEW_DIRS ${OPENGL_DIRS}/glew-1.11.0/)

include_directories(lab12 ${FREEGLUT_DIRS}/include/)
include_directories(lab12 ${GLEW_DIRS}/include/)

include_directories(ind3kostikova ${FREEGLUT_DIRS}/include/)
include_directories(ind3kostikova ${GLEW_DIRS}/include/)

set(LIBS_DIRS ${FREEGLUT_DIRS}/lib/freeglut.lib ${GLEW_DIRS}/lib/glew32.lib)

# ADDITIONAL PATHS AND LIBS
set(SOIL2_DIR D:/MyLibraries/SOIL2/)
include_directories(lab12 ${SOIL2_DIR}/include/)
set(SOIL2_LIB ${SOIL2_DIR}/lib/SOIL.lib)

# ADD SIMILAR LINES WHEN CREATING NEW EXECUTABLE
target_link_libraries (lab11 ${LIBS_DIRS} ${SOIL2_LIB})
target_link_libraries (lab12 ${LIBS_DIRS})
target_link_libraries (lab13 ${LIBS_DIRS})
target_link_libraries (ind3kostikova ${LIBS_DIRS})
