cmake_minimum_required(VERSION 3.15)
project(KeyframeDemo CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
# On macOS we can use the system GLUT framework; find_package(GLUT) isn’t required
# but harmless if you prefer to keep it.

add_executable(keyframe
    src/main.cpp
    src/Renderer.cpp
    src/SplineMath.cpp   # renamed from Math.cpp
    src/Quaternion.cpp
    src/EulerAngle.cpp
    src/GlobalVariables.cpp
)

target_include_directories(keyframe PRIVATE include)

if(APPLE)
  # Use system frameworks
  target_link_libraries(keyframe PRIVATE "-framework OpenGL" "-framework GLUT")
  target_compile_definitions(keyframe PRIVATE GL_SILENCE_DEPRECATION)
else()
  find_package(GLUT REQUIRED)
  target_include_directories(keyframe PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
  target_link_libraries(keyframe PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif()
