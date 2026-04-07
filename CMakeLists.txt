cmake_minimum_required(VERSION 3.10)
project(simple-platformer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

set(SOURCES 
    main.cpp
    thirdparty/glad/src/glad.c
)

include_directories(${CMAKE_SOURCE_DIR}/thirdparty/glad/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)
endif()
