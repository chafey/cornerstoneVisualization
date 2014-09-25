
file( GLOB IMAGE_DATA_SERVICE_SOURCES *.cpp)
source_group ("Source Files" FILES ${IMAGE_DATA_SERVICE_SOURCES})

file( GLOB IMAGE_DATA_SERVICE_HEADERS *.h)
source_group ("Header Files" FILES ${IMAGE_DATA_SERVICE_HEADERS})

file( GLOB IMAGE_DATA_WEB_FILES web/*)
source_group ("Web Files" FILES ${IMAGE_DATA_WEB_FILES})

source_group ("Misc Files" FILES ${MISC_FILES})

LINK_DIRECTORIES(${LINK_DIRECTORIES} ${http_server_BINARY_DIR})
INCLUDE_DIRECTORIES(${http_server_DIR})

#--------------------------------------------------------------------------------------------------
# Boost libraries.
#--------------------------------------------------------------------------------------------------

FIND_PACKAGE(Boost COMPONENTS system thread filesystem timer regex REQUIRED)
IF (Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  ADD_DEFINITIONS("-DHAS_BOOST")
  #ADD_DEFINITIONS("-DBOOST_LOG_DYN_LINK")
ENDIF(Boost_FOUND)

#--------------------------------------------------------------------------------------------------
# VTK libraries.
#--------------------------------------------------------------------------------------------------

FIND_PACKAGE(VTK)
IF (VTK_FOUND)
  INCLUDE(${VTK_USE_FILE})
ENDIF(VTK_FOUND)

#--------------------------------------------------------------------------------------------------
# ImageDataService
#--------------------------------------------------------------------------------------------------

ADD_EXECUTABLE(image_data_service ${IMAGE_DATA_SERVICE_SOURCES} ${IMAGE_DATA_WEB_FILES} ${IMAGE_DATA_SERVICE_HEADERS}  ${MISC_FILES})
if(VTK_LIBRARIES)
TARGET_LINK_LIBRARIES(image_data_service debug ${VTK_LIBRARIES} ${Boost_LIBRARIES} http_server)
TARGET_LINK_LIBRARIES(image_data_service ${VTK_LIBRARIES} ${Boost_LIBRARIES} http_server)
else()
TARGET_LINK_LIBRARIES(image_data_service vtkHybrid ${Boost_LIBRARIES} http_server)
endif()

# create a new list of the sources that use precompiled headers
set(IMAGE_DATA_SERVICE_SOURCES_USING_PCH ${IMAGE_DATA_SERVICE_SOURCES})
list(REMOVE_ITEM IMAGE_DATA_SERVICE_SOURCES_USING_PCH ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp)

# Setup precompiled headers for Microsoft Visual Studio
if (${MSVC})
  ADD_VISUAL_STUDIO_PRECOMPILED_HEADERS(
    "stdafx.h" "stdafx.cpp" IMAGE_DATA_SERVICE_SOURCES_USING_PCH)
endif()
