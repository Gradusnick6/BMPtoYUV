cmake_minimum_required (VERSION 3.17)
project (BMPtoYUV)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(
    SRC
    src/main.cpp
    src/Bitmap24.cpp
    src/YUV_CIF.cpp
)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)
add_executable(${PROJECT_NAME} ${SRC})