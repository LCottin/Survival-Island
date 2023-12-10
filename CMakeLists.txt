cmake_minimum_required(VERSION 3.15)

project(Survival-Island)

find_package(nlohmann_json REQUIRED)
find_package(SFML 2.6.1 COMPONENTS graphics window REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Define directories
set(DEV_DIR ${CMAKE_SOURCE_DIR}/dev)
set(BIN_DIR ${CMAKE_BINARY_DIR})

# Collect source files
set(SOURCES
    ${DEV_DIR}/main.cpp
    ${DEV_DIR}/Character/src/Character.cpp
    ${DEV_DIR}/Character/src/CharacterData.cpp
    ${DEV_DIR}/Player/src/Player.cpp
    ${DEV_DIR}/Board/src/Board.cpp
)

# Collect header files
set(HEADERS
    ${DEV_DIR}/Character/include/Character.hpp
    ${DEV_DIR}/Character/include/CharacterData.hpp
    ${DEV_DIR}/Player/include/Player.hpp
    ${DEV_DIR}/Board/include/Board.hpp
)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Set the minimum OS X deployment version to 12.0
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum OS X deployment version" FORCE)

# Add the executable
add_executable(${PROJECT_NAME})

# Add source and header files to the target
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${DEV_DIR}/Character/include
    ${DEV_DIR}/Player/include
    ${DEV_DIR}/Board/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS} PRIVATE nlohmann_json::nlohmann_json)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)
