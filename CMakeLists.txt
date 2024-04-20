cmake_minimum_required(VERSION 3.15)
include(VersionConfig.cmake)

set(CMAKE_CXX_STANDARD 20)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Provide options for the build type
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

# Set the minimum OS X deployment version to 12.0
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum OS X deployment version" FORCE)

# Define common and specific compile definitions and options
set(COMMON_COMPILE_DEFINITIONS DEBUG_MODE)
set(DEBUG_COMPILE_DEFINITIONS DEBUG_EXTRA)
set(RELEASE_COMPILE_DEFINITIONS RELEASE_EXTRA)

set(COMMON_COMPILE_OPTIONS  "-Wall" "-Wextra" "-march=native")
set(DEBUG_COMPILE_OPTIONS   "-g")
set(RELEASE_COMPILE_OPTIONS "-O3" "-Werror")

# Set the output directory for the binary
set(BIN_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

project(Survival-Island)

    find_package(nlohmann_json REQUIRED)
    find_package(SFML 2.6.1 COMPONENTS graphics window REQUIRED)

    # Define directories
    set(DEV_CLIENT_DIR ${CMAKE_SOURCE_DIR}/dev/Client)
    set(DEV_SERVER_DIR ${CMAKE_SOURCE_DIR}/dev/Server)

    # Collect client source files
    set(CLIENT_SOURCES
        ${DEV_CLIENT_DIR}/main.cpp
        ${DEV_CLIENT_DIR}/Character/src/Character.cpp
        ${DEV_CLIENT_DIR}/Character/src/CharacterPrv.cpp
        ${DEV_CLIENT_DIR}/Player/src/Player.cpp
        ${DEV_CLIENT_DIR}/Game/src/Game.cpp
        ${DEV_CLIENT_DIR}/NPC/src/NPC.cpp
        ${DEV_CLIENT_DIR}/NPC/src/NPCPub.cpp
        ${DEV_CLIENT_DIR}/Board/src/Board.cpp
        ${DEV_CLIENT_DIR}/Screen/src/Screen.cpp
        ${DEV_CLIENT_DIR}/Random/src/Random.cpp
        ${DEV_CLIENT_DIR}/Config/src/ConfigDev.cpp
        ${DEV_CLIENT_DIR}/Config/src/ConfigUser.cpp
        ${DEV_CLIENT_DIR}/Config/src/ConfigUserPub.cpp
        ${DEV_CLIENT_DIR}/InfoPanel/src/InfoPanel.cpp
        ${DEV_CLIENT_DIR}/GenericView/src/GenericView.cpp)

    # Collect client header files
    set(CLIENT_HEADERS
        ${DEV_CLIENT_DIR}/Character/include/Character.hpp
        ${DEV_CLIENT_DIR}/Character/include/CharacterPub.hpp
        ${DEV_CLIENT_DIR}/Character/include/CharacterPrv.hpp
        ${DEV_CLIENT_DIR}/Player/include/Player.hpp
        ${DEV_CLIENT_DIR}/Player/include/PlayerPrv.hpp
        ${DEV_CLIENT_DIR}/Game/include/Game.hpp
        ${DEV_CLIENT_DIR}/Game/include/GamePub.hpp
        ${DEV_CLIENT_DIR}/Game/include/GamePrv.hpp
        ${DEV_CLIENT_DIR}/NPC/include/NPC.hpp
        ${DEV_CLIENT_DIR}/NPC/include/NPCPub.hpp
        ${DEV_CLIENT_DIR}/NPC/include/NPCPrv.hpp
        ${DEV_CLIENT_DIR}/Board/include/Board.hpp
        ${DEV_CLIENT_DIR}/Board/include/BoardPub.hpp
        ${DEV_CLIENT_DIR}/Board/include/TileType.hpp
        ${DEV_CLIENT_DIR}/Screen/include/Screen.hpp
        ${DEV_CLIENT_DIR}/Screen/include/ScreenPrv.hpp
        ${DEV_CLIENT_DIR}/Random/include/Random.hpp
        ${DEV_CLIENT_DIR}/Config/include/ConfigDev.hpp
        ${DEV_CLIENT_DIR}/Config/include/ConfigUser.hpp
        ${DEV_CLIENT_DIR}/Config/include/ConfigUserPub.hpp
        ${DEV_CLIENT_DIR}/FastNoise/include/FastNoiseLite.hpp
        ${DEV_CLIENT_DIR}/InfoPanel/include/InfoPanel.hpp
        ${DEV_CLIENT_DIR}/GenericView/include/GenericView.hpp)

    # Collect server source files
    set(SERVER_SOURCES
        ${DEV_SERVER_DIR}/main.cpp)

    # Collect server headers files
    set(SERVER_HEADERS)

    # Define binaries
    set(CLIENT_EXE ${PROJECT_NAME}_Client)
    set(SERVER_EXE ${PROJECT_NAME}_Server)

    # Add the executable
    add_executable(${CLIENT_EXE})
    add_executable(${SERVER_EXE})

    # Add source and header files to the target
    target_sources(${CLIENT_EXE} PRIVATE ${CLIENT_SOURCES} ${CLIENT_HEADERS})
    target_sources(${SERVER_EXE} PRIVATE ${SERVER_SOURCES} ${SERVER_HEADERS})

    # Add include directories
    target_include_directories(${CLIENT_EXE} PRIVATE
                               ${DEV_CLIENT_DIR}/Character/include
                               ${DEV_CLIENT_DIR}/Player/include
                               ${DEV_CLIENT_DIR}/Board/include
                               ${DEV_CLIENT_DIR}/Screen/include
                               ${DEV_CLIENT_DIR}/Game/include
                               ${DEV_CLIENT_DIR}/NPC/include
                               ${DEV_CLIENT_DIR}/Random/include
                               ${DEV_CLIENT_DIR}/Config/include
                               ${DEV_CLIENT_DIR}/FastNoise/include
                               ${DEV_CLIENT_DIR}/InfoPanel/include
                               ${DEV_CLIENT_DIR}/GenericView/include)

    # Link libraries
    target_link_libraries(${CLIENT_EXE} PRIVATE
                          ${CMAKE_DL_LIBS}
                          nlohmann_json::nlohmann_json
                          sfml-graphics sfml-window)

    target_link_libraries(${SERVER_EXE} PRIVATE)

    # Set compilation options based on the selected build type
    target_compile_definitions(${CLIENT_EXE} PRIVATE ${COMMON_COMPILE_DEFINITIONS})
    target_compile_definitions(${SERVER_EXE} PRIVATE ${COMMON_COMPILE_DEFINITIONS})

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_definitions(${CLIENT_EXE} PRIVATE ${DEBUG_COMPILE_DEFINITIONS})
        target_compile_options(${CLIENT_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${DEBUG_COMPILE_OPTIONS})
        target_compile_definitions(${SERVER_EXE} PRIVATE ${DEBUG_COMPILE_DEFINITIONS})
        target_compile_options(${SERVER_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${DEBUG_COMPILE_OPTIONS})
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        target_compile_definitions(${CLIENT_EXE} PRIVATE ${RELEASE_COMPILE_DEFINITIONS})
        target_compile_options(${CLIENT_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})
        target_compile_definitions(${SERVER_EXE} PRIVATE ${RELEASE_COMPILE_DEFINITIONS})
        target_compile_options(${SERVER_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})
    endif()

    # Define a custom command to print build mode during the build process
    add_custom_command(TARGET ${CLIENT_EXE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Compiled Survival-Island_Client version ${SURVIVAL_ISLAND_CLIENT_VERSION} in ${CMAKE_BUILD_TYPE} mode.")
    add_custom_command(TARGET ${SERVER_EXE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Compiled Survival-Island_Server version ${SURVIVAL_ISLAND_SERVER_VERSION} in ${CMAKE_BUILD_TYPE} mode.")
