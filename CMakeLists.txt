cmake_minimum_required(VERSION 2.8)
project(CornerstoneVisualizationServer)

# disable static build
set(STATIC_BUILD OFF)



# Advanced parameters to fine-tune linking against system libraries
SET(USE_SYSTEM_BOOST ON CACHE BOOL "Use the system version of Boost")

# Configure the compiler
include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)
include(${CMAKE_SOURCE_DIR}/CMake/Compiler.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/VisualStudioPrecompiledHeaders.cmake)

# disable boost auto linking
add_definitions(-DBOOST_ALL_NO_LIB)

# prevent using boost static libraries
set(Boost_USE_STATIC_LIBS OFF)

# disable thread safety in easy logger since we are single threaded
add_definitions(-D_ELPP_THREAD_SAFE)

add_subdirectory(src/http_server)
add_subdirectory(src/image_data_service)

file(GLOB MISC_FILES *.txt *.md)


