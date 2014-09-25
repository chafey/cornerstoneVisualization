if (${CMAKE_COMPILER_IS_GNUCXX})
  # Make gcc stop on errors
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -Wno-implicit-function-declaration")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wno-overflow")

  # Prevent missing symbols in the resulting shared library
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

  # Version script to publish only the plugin callbacks in the shared
  # library. This is mandatory for static builds: Otherwise, the
  # libpng and the zlib that are contained in the plugin would clash
  # with those contained in Orthanc.  
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--version-script=${CMAKE_SOURCE_DIR}/WadoPlugin.map")
endif()


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  # Link against standard system-wide libraries under Linux
  link_libraries(X11 pthread uuid)
endif()


if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

  set(STATIC_BUILD OFF)

  # Set runtime library to multi-threaded dll
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
  
  add_definitions(
	-D_WIN32_WINNT=0x0501
    -DWINVER=0x0501
    -D_CRT_SECURE_NO_WARNINGS=1
	-D_SCL_SECURE_NO_WARNINGS
    )
endif()
