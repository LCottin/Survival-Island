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

set(COMMON_COMPILE_OPTIONS  "-Wall" "-Wextra" "-march=native" "-mtune=native" "-std=c++20")
set(DEBUG_COMPILE_OPTIONS   "-g")
set(RELEASE_COMPILE_OPTIONS "-O3" "-Werror")

# Set the output directory for the binary
set(BIN_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

project(Survival-Island)

    find_package(nlohmann_json REQUIRED)
    find_package(SFML 2.6.1 COMPONENTS graphics window network REQUIRED)

    # Define directories
    set(DEV_COMMON_DIR ${CMAKE_SOURCE_DIR}/dev/common)
    set(DEV_CLIENT_DIR ${CMAKE_SOURCE_DIR}/dev/Client)
    set(DEV_SERVER_DIR ${CMAKE_SOURCE_DIR}/dev/Server)

    # Collect common source files
    set(COMMON_SOURCES
        ${DEV_COMMON_DIR}/main.cpp
        ${DEV_COMMON_DIR}/Character/src/Character.cpp
        ${DEV_COMMON_DIR}/Character/src/CharacterPrv.cpp
        ${DEV_COMMON_DIR}/Character/src/CharacterPub.cpp
        ${DEV_COMMON_DIR}/Player/src/Player.cpp
        ${DEV_COMMON_DIR}/NPC/src/NPC.cpp
        ${DEV_COMMON_DIR}/NPC/src/NPCPub.cpp
        ${DEV_COMMON_DIR}/Board/src/Board.cpp
        ${DEV_COMMON_DIR}/Random/src/Random.cpp
        ${DEV_COMMON_DIR}/Config/src/ConfigDev.cpp
        ${DEV_COMMON_DIR}/Config/src/ConfigUser.cpp
        ${DEV_COMMON_DIR}/Config/src/ConfigUserPub.cpp
        ${DEV_COMMON_DIR}/Config/src/ConfigNetwork.cpp)

    # Collect common header files
    set(COMMON_HEADERS
        ${DEV_COMMON_DIR}/Character/include/Character.hpp
        ${DEV_COMMON_DIR}/Character/include/CharacterPub.hpp
        ${DEV_COMMON_DIR}/Character/include/CharacterPrv.hpp
        ${DEV_COMMON_DIR}/Player/include/Player.hpp
        ${DEV_COMMON_DIR}/Player/include/PlayerPrv.hpp
        ${DEV_COMMON_DIR}/NPC/include/NPC.hpp
        ${DEV_COMMON_DIR}/NPC/include/NPCPub.hpp
        ${DEV_COMMON_DIR}/NPC/include/NPCPrv.hpp
        ${DEV_COMMON_DIR}/Random/include/Random.hpp
        ${DEV_COMMON_DIR}/Config/include/ConfigDev.hpp
        ${DEV_COMMON_DIR}/Config/include/ConfigUser.hpp
        ${DEV_COMMON_DIR}/Config/include/ConfigUserPub.hpp
        ${DEV_COMMON_DIR}/Config/include/ConfigNetwork.hpp
        ${DEV_COMMON_DIR}/FastNoise/include/FastNoiseLite.hpp)

    # Collect client source files
    set(CLIENT_SOURCES
        ${DEV_CLIENT_DIR}/main.cpp
        ${DEV_CLIENT_DIR}/Game/src/Game.cpp
        ${DEV_CLIENT_DIR}/Screen/src/Screen.cpp
        ${DEV_CLIENT_DIR}/InfoPanel/src/InfoPanel.cpp
        ${DEV_CLIENT_DIR}/ClientNetwork/src/ClientNetwork.cpp
        ${DEV_CLIENT_DIR}/GenericView/src/GenericView.cpp)

    # Collect client header files
    set(CLIENT_HEADERS
        ${DEV_CLIENT_DIR}/Game/include/Game.hpp
        ${DEV_CLIENT_DIR}/Game/include/GamePub.hpp
        ${DEV_CLIENT_DIR}/Game/include/GamePrv.hpp
        ${DEV_CLIENT_DIR}/Screen/include/Screen.hpp
        ${DEV_CLIENT_DIR}/Screen/include/ScreenPrv.hpp
        ${DEV_CLIENT_DIR}/InfoPanel/include/InfoPanel.hpp
        ${DEV_CLIENT_DIR}/GenericView/include/GenericView.hpp
        ${DEV_CLIENT_DIR}/ClientNetwork/include/ClientNetwork.hpp)

    # Collect server source files
    set(SERVER_SOURCES
        ${DEV_SERVER_DIR}/main.cpp
        ${DEV_SERVER_DIR}/ServerNetwork/src/ServerNetwork.cpp
        ${DEV_SERVER_DIR}/Game/src/Game.cpp)

    # Collect server headers files
    set(SERVER_HEADERS
        ${DEV_SERVER_DIR}/ServerNetwork/include/ServerNetwork.hpp
        ${DEV_SERVER_DIR}/Game/include/Game.hpp)

    # Define include directories
    set(INCLUDE_COMMON
        ${DEV_COMMON_DIR}/Board/include
        ${DEV_COMMON_DIR}/Character/include
        ${DEV_COMMON_DIR}/Config/include
        ${DEV_COMMON_DIR}/FastNoise/include
        ${DEV_COMMON_DIR}/NPC/include
        ${DEV_COMMON_DIR}/Player/include
        ${DEV_COMMON_DIR}/Random/include)
    set(INCLUDE_CLIENT
        ${DEV_CLIENT_DIR}/Game/include
        ${DEV_CLIENT_DIR}/InfoPanel/include
        ${DEV_CLIENT_DIR}/GenericView/include
        ${DEV_CLIENT_DIR}/ClientNetwork/include
        ${DEV_CLIENT_DIR}/Screen/include)
    set(INCLUDE_SERVER
        ${DEV_SERVER_DIR}/ServerNetwork/include
        ${DEV_SERVER_DIR}/Game/include)

    # Define binaries
    set(COMMON_LIB ${PROJECT_NAME}_Lib)
    set(COMMON_EXE ${PROJECT_NAME}_Common)
    set(CLIENT_EXE ${PROJECT_NAME}_Client)
    set(SERVER_EXE ${PROJECT_NAME}_Server)

    # Add the executable
    add_executable(${COMMON_EXE})
    add_executable(${CLIENT_EXE})
    add_executable(${SERVER_EXE})

    # Create library for common files
    add_library(${COMMON_LIB})

    # Add common include directories
    foreach(INCLUDE_DIR ${INCLUDE_COMMON})
        target_include_directories(${COMMON_EXE} PRIVATE ${INCLUDE_DIR})
        target_include_directories(${COMMON_LIB} PRIVATE ${INCLUDE_DIR})
        target_include_directories(${CLIENT_EXE} PRIVATE ${INCLUDE_DIR})
        target_include_directories(${SERVER_EXE} PRIVATE ${INCLUDE_DIR})
    endforeach()

    # Add client include directories
    foreach(INCLUDE_DIR ${INCLUDE_CLIENT})
        target_include_directories(${CLIENT_EXE} PRIVATE ${INCLUDE_DIR})
    endforeach()

    # Add server include directories
    foreach(INCLUDE_DIR ${INCLUDE_SERVER})
        target_include_directories(${SERVER_EXE} PRIVATE ${INCLUDE_DIR})
    endforeach()

    # Link libraries
    target_link_libraries(${COMMON_LIB} PRIVATE
                          nlohmann_json::nlohmann_json
                          sfml-graphics sfml-window)

    target_link_libraries(${COMMON_EXE} PRIVATE
                          nlohmann_json::nlohmann_json
                          sfml-graphics sfml-window)

    target_link_libraries(${CLIENT_EXE} PRIVATE
                        ${CMAKE_DL_LIBS}
                        ${COMMON_LIB}
                        nlohmann_json::nlohmann_json
                        sfml-graphics sfml-window sfml-network)

    target_link_libraries(${SERVER_EXE} PRIVATE
                        ${CMAKE_DL_LIBS}
                        ${COMMON_LIB}
                        nlohmann_json::nlohmann_json
                        sfml-network)

    # Add source and header files to the target
    target_sources(${COMMON_LIB} PRIVATE ${COMMON_SOURCES} ${COMMON_HEADERS})
    target_sources(${COMMON_EXE} PRIVATE ${COMMON_SOURCES} ${COMMON_HEADERS})
    target_sources(${CLIENT_EXE} PRIVATE ${CLIENT_SOURCES} ${CLIENT_HEADERS})
    target_sources(${SERVER_EXE} PRIVATE ${SERVER_SOURCES} ${SERVER_HEADERS})

    # Set compilation options based on the selected build type
    target_compile_definitions(${COMMON_EXE} PRIVATE ${COMMON_COMPILE_DEFINITIONS})
    target_compile_definitions(${CLIENT_EXE} PRIVATE ${COMMON_COMPILE_DEFINITIONS})
    target_compile_definitions(${SERVER_EXE} PRIVATE ${COMMON_COMPILE_DEFINITIONS})

    # Set C++ standard
    target_compile_features(${COMMON_EXE} PRIVATE cxx_std_20)
    target_compile_features(${CLIENT_EXE} PRIVATE cxx_std_20)
    target_compile_features(${SERVER_EXE} PRIVATE cxx_std_20)

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_definitions(${COMMON_EXE} PRIVATE ${DEBUG_COMPILE_DEFINITIONS})
        target_compile_options(${COMMON_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${DEBUG_COMPILE_OPTIONS})

        target_compile_definitions(${CLIENT_EXE} PRIVATE ${DEBUG_COMPILE_DEFINITIONS})
        target_compile_options(${CLIENT_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${DEBUG_COMPILE_OPTIONS})

        target_compile_definitions(${SERVER_EXE} PRIVATE ${DEBUG_COMPILE_DEFINITIONS})
        target_compile_options(${SERVER_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${DEBUG_COMPILE_OPTIONS})

    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        target_compile_definitions(${COMMON_EXE} PRIVATE ${RELEASE_COMPILE_DEFINITIONS})
        target_compile_options(${COMMON_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})

        target_compile_definitions(${CLIENT_EXE} PRIVATE ${RELEASE_COMPILE_DEFINITIONS})
        target_compile_options(${CLIENT_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})

        target_compile_definitions(${SERVER_EXE} PRIVATE ${RELEASE_COMPILE_DEFINITIONS})
        target_compile_options(${SERVER_EXE} PRIVATE ${COMMON_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})

    endif()

    # Define a custom command to print build mode during the build process
    add_custom_command(TARGET ${COMMON_EXE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Compiled Survival-Island_Common in ${CMAKE_BUILD_TYPE} mode.")
    add_custom_command(TARGET ${CLIENT_EXE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Compiled Survival-Island_Client version ${SURVIVAL_ISLAND_CLIENT_VERSION} in ${CMAKE_BUILD_TYPE} mode.")
    add_custom_command(TARGET ${SERVER_EXE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E echo "Compiled Survival-Island_Server version ${SURVIVAL_ISLAND_SERVER_VERSION} in ${CMAKE_BUILD_TYPE} mode.")
