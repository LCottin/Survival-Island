cmake_minimum_required(VERSION 3.15)

project(Survival-Island)

find_package(nlohmann_json REQUIRED)
find_package(SFML COMPONENTS graphics window REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Define directories
set(SOURCE_DIR  ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(BIN_DIR     ${CMAKE_BINARY_DIR})

# Collect source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Character.cpp
    ${SOURCE_DIR}/CharacterData.cpp
    ${SOURCE_DIR}/Player.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/Character.hpp
    ${INCLUDE_DIR}/CharacterData.hpp
    ${INCLUDE_DIR}/Player.hpp
)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Set the minimum OS X deployment version to 12.0
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum OS X deployment version" FORCE)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS} PRIVATE nlohmann_json::nlohmann_json)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)
