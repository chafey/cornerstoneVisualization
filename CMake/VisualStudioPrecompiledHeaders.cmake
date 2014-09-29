macro(ADD_VISUAL_STUDIO_PRECOMPILED_HEADERS PrecompiledHeaders PrecompiledSource Sources)
  get_filename_component(PrecompiledBasename ${PrecompiledHeaders} NAME_WE)
  set(PrecompiledBinary "$(IntDir)/${PrecompiledBasename}.pch")

  set_source_files_properties(${PrecompiledSource}
    PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeaders}\" /Fp\"${PrecompiledBinary}\""
    OBJECT_OUTPUTS "${PrecompiledBinary}")

  set_source_files_properties(${${Sources}}
    PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeaders}\" /FI\"${PrecompiledHeaders}\" /Fp\"${PrecompiledBinary}\""
    OBJECT_DEPENDS "${PrecompiledBinary}")

  # Add /Zm256 compiler option to Visual Studio to fix PCH errors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm512")
	
  list(APPEND ${Sources} ${PrecompiledSource})
endmacro()
