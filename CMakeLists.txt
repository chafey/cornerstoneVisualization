cmake_minimum_required(VERSION 2.8)

project(cornerstoneVisualizationService)

add_subdirectory(src/http_server)
add_subdirectory(src/image_data_service)

file(GLOB MISC_FILES *.txt *.md)

ADD_EXECUTABLE(Misc ${MISC_FILES})
SET_TARGET_PROPERTIES(Misc PROPERTIES LINKER_LANGUAGE C)


