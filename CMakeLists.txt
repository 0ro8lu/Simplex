cmake_minimum_required(VERSION 3.16)
project(ZombieGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file(GLOB_RECURSE MY_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp
                             ${CMAKE_SOURCE_DIR}/Libs/glad/src/glad.c)

add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

#TODO: Add support for other platforms.

# include dirs for libraries.
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/glad/include/glad)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/stb_image)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/glad/include/KHR)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/GLFW/includes)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/TinyXML2/includes)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/glm)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/Box2D/includes)

# inlcude dirs for game code.
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/View)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Events)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Events/EventTypes)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

#----------------------- OpenGL Related libs ---------------------------------

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/GLFW/bin/Linux/libglfw3.a)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -lGL)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -lX11)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -lpthread)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -lXrandr)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -lXi)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -ldl)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/TinyXML2/bin/Linux/libtinyxml2.so)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Libs/Box2D/bin/Linux/Debug/libbox2d.a)