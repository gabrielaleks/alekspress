cmake_minimum_required(VERSION 3.10)
project(alekspress)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatic file discovery (more convenient but less recommended)
file(GLOB_RECURSE PROJECT_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Main executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include directories (this will recursively add all subdirectories under src)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include 
        ${CMAKE_SOURCE_DIR}/exceptions
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# Optional: Add compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()