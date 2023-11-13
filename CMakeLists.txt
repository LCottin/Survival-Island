cmake_minimum_required(VERSION 3.15)

project(Survival-Island)

set(CMAKE_CXX_STANDARD 20)

# Define directories
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(BIN_DIR ${CMAKE_BINARY_DIR})

# Collect source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
)

set(HEADERS
)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS})
