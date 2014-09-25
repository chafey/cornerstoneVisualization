file(GLOB HTTP_SERVER_SOURCES *.cpp)
source_group("Source Files" FILES ${HTTP_SERVER_SOURCES})

file(GLOB HTTP_SERVER_HEADERS *.hpp *.h)
source_group("Header Files" FILES ${HTTP_SERVER_HEADERS})

FIND_PACKAGE(Boost COMPONENTS system thread filesystem REQUIRED)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF(Boost_FOUND)

ADD_LIBRARY(http_server ${HTTP_SERVER_SOURCES} ${HTTP_SERVER_HEADERS})

# create a new list of the sources that use precompiled headers
set(HTTP_SERVER_SOURCES_USING_PCH ${HTTP_SERVER_SOURCES})
list(REMOVE_ITEM HTTP_SERVER_SOURCES_USING_PCH ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp)

# Setup precompiled headers for Microsoft Visual Studio
if (${MSVC})
  ADD_VISUAL_STUDIO_PRECOMPILED_HEADERS(
    "stdafx.h" "stdafx.cpp" HTTP_SERVER_SOURCES_USING_PCH)
endif()
