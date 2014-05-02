
file( GLOB IMAGE_DATA_SERVICE_SOURCES *.cpp)
source_group ("Source Files" FILES ${IMAGE_DATA_SERVICE_SOURCES})

file( GLOB IMAGE_DATA_SERVICE_HEADERS *.h)
source_group ("Header Files" FILES ${IMAGE_DATA_SERVICE_HEADERS})

file( GLOB IMAGE_DATA_WEB_FILES web/*)
source_group ("Web Files" FILES ${IMAGE_DATA_WEB_FILES})

#INCLUDE_DIRECTORIES("http_server")

LINK_DIRECTORIES(${http_server_BINARY_DIR})
INCLUDE_DIRECTORIES(${http_server_DIR})

#--------------------------------------------------------------------------------------------------
# Boost libraries.
#--------------------------------------------------------------------------------------------------

#set (Boost_MULTITHREADED TRUE)
SET(Boost_USE_STATIC_LIBS OFF)

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

ADD_EXECUTABLE(image_data_service ${IMAGE_DATA_SERVICE_SOURCES} ${IMAGE_DATA_WEB_FILES} ${IMAGE_DATA_SERVICE_HEADERS} )
if(VTK_LIBRARIES)
TARGET_LINK_LIBRARIES(image_data_service ${VTK_LIBRARIES} ${Boost_LIBRARIES} http_server)
else()
TARGET_LINK_LIBRARIES(image_data_service vtkHybrid ${Boost_LIBRARIES} http_server)
endif()
