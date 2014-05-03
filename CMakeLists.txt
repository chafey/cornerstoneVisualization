cmake_minimum_required(VERSION 2.8)

# Set the target win32 version for windows
if(${WIN32})
#this method adds the necessary compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0501 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS")
#this adds a preprocessor definition to the project
add_definitions(-D_WIN32_WINNT=0x0501)
# add boost paths for windows
set(BOOST_ROOT "c:/local/boost_1_55_0")
set(BOOST_LIBRARYDIR "C:/local/boost_1_55_0/lib64-msvc-10.0")
set(LINK_DIRECTORIES ${LINK_DIRECTORIES} "C:/local/boost_1_55_0/lib64-msvc-10.0")
endif()

add_definitions(-D_ELPP_THREAD_SAFE)

# force boost to build with multi-threaded shared/dynamic libraries
add_definitions(-DBOOST_ALL_DYN_LINK)
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_DEBUG OFF) 
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   

project(cornerstoneVisualizationService)

add_subdirectory(src/http_server)
add_subdirectory(src/image_data_service)

file(GLOB MISC_FILES *.txt *.md)


