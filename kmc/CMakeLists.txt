# Assert the minimum cmake version
cmake_minimum_required(VERSION 3.22)

# Set the project name
project(kmc)

# Require a modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add FetchContent module
include(FetchContent)

# Find MPI package
find_package(MPI REQUIRED)
find_package(nlohmann_json 3.10.5 REQUIRED)

# Add an executable called Main built from src/main.cpp
add_library(KMC src/kmc.cpp src/kmc_utilities.cpp)
add_executable(Main src/main.cpp)

# Include MPI headers
target_include_directories(KMC PRIVATE ${MPI_CXX_INCLUDE_PATH})

# Link against MPI libraries
target_link_libraries(KMC PRIVATE ${MPI_CXX_LIBRARIES})
target_include_directories(KMC PRIVATE include)

# Link the Main executable target to the KMC library target
target_link_libraries(Main PRIVATE KMC)
target_include_directories(Main PRIVATE include)

# Add MPI compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS}")

# Add MPI link flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_CXX_LINK_FLAGS}")

#########################################
# BEGIN GoogleTest setup, DO NOT CHANGE #
#########################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")

# Set up GoogleTest according to: https://google.github.io/googletest/quickstart-cmake.html
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(KMCTest test/kmc_test.cpp)
target_link_libraries(KMCTest GTest::gtest_main)
target_link_libraries(KMCTest KMC)
target_include_directories(KMCTest PRIVATE include)

include(GoogleTest)
gtest_discover_tests(KMCTest)

##########################
# END   GoogleTest setup #
##########################