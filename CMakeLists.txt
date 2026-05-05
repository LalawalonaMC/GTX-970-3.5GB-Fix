cmake_minimum_required(VERSION 3.10)
project(GTX970_35GB_Fix)

# Find the Vulkan SDK installed by the GitHub Action
find_package(Vulkan REQUIRED)

# 1. The Fix (The DLL Layer)
add_library(GTX970Fix SHARED layer.cpp)
target_include_directories(GTX970Fix PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(GTX970Fix PRIVATE ${Vulkan_LIBRARIES})

# 2. The Test Program (The EXE)
add_executable(VramTest main.cpp)
target_include_directories(VramTest PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(VramTest PRIVATE ${Vulkan_LIBRARIES})
