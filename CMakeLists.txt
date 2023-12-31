cmake_minimum_required(VERSION 3.15)

project(Survival-Island)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Provide options for the build type
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

find_package(nlohmann_json REQUIRED)
find_package(SFML 2.6.1 COMPONENTS graphics window REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Define directories
set(DEV_DIR ${CMAKE_SOURCE_DIR}/dev)
set(BIN_DIR ${CMAKE_BINARY_DIR})

# Define common and specific compile definitions and options
set(COMMON_COMPILE_DEFINITIONS DEBUG_MODE)
set(DEBUG_COMPILE_DEFINITIONS DEBUG_EXTRA)
set(RELEASE_COMPILE_DEFINITIONS RELEASE_EXTRA)

set(COMMON_COMPILE_OPTIONS  "-Wall" "-Wextra" "-march=native")
set(DEBUG_COMPILE_OPTIONS   "-g")
set(RELEASE_COMPILE_OPTIONS "-O3")

# Collect source files
set(SOURCES
    ${DEV_DIR}/main.cpp
    ${DEV_DIR}/Character/src/Character.cpp
    ${DEV_DIR}/Character/src/CharacterData.cpp
    ${DEV_DIR}/Player/src/Player.cpp
    ${DEV_DIR}/NPC/src/NPC.cpp
    ${DEV_DIR}/Board/src/Board.cpp
    ${DEV_DIR}/Screen/src/Screen.cpp
    ${DEV_DIR}/Random/src/Random.cpp
)

# Collect header files
set(HEADERS
    ${DEV_DIR}/Character/include/Character.hpp
    ${DEV_DIR}/Character/include/CharacterData.hpp
    ${DEV_DIR}/Player/include/Player.hpp
    ${DEV_DIR}/NPC/include/NPC.hpp
    ${DEV_DIR}/Board/include/Board.hpp
    ${DEV_DIR}/Board/include/BoardData.hpp
    ${DEV_DIR}/Board/include/TileType.hpp
    ${DEV_DIR}/Screen/include/Screen.hpp
    ${DEV_DIR}/Screen/include/ScreenData.hpp
    ${DEV_DIR}/Random/include/Random.hpp
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
    ${DEV_DIR}/Screen/include
    ${DEV_DIR}/NPC/include
    ${DEV_DIR}/Random/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS} PRIVATE nlohmann_json::nlohmann_json)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)

# Set compilation options based on the selected build type
target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_DEFINITIONS})

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEBUG_COMPILE_DEFINITIONS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS} ${DEBUG_COMPILE_OPTIONS})
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${RELEASE_COMPILE_DEFINITIONS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})
endif()

# Define a custom command to print build mode during the build process
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Compiled Survival-Island in ${CMAKE_BUILD_TYPE} mode"
)
