# Usage:  configureBuildType( "Release" )
# This will switch to Release build type by default if no -DCMAKE_BUILD_TYPE is given during configuration.
# Also, this fonction:
#  - create a 'Profile' build type to analyse perf using gprof for example.
#  - facilitate the build type selection when using ccmake or any graphical cmake client

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# easy build type selection
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Release Debug RelWithDebInfo)

# generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# colored compiler output
add_compile_options(
  $<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always>
  $<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics>
)

# create profile for profiling with gprof
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS_PROFILE
    "${CMAKE_C_FLAGS_RELWITHDEBINFO} -p" CACHE STRING "")
  set(CMAKE_CXX_FLAGS_PROFILE
    "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -p" CACHE STRING "")
  set(CMAKE_EXE_LINKER_FLAGS_PROFILE
    "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -p" CACHE STRING "")
  set(CMAKE_SHARED_LINKER_FLAGS_PROFILE
    "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} -p" CACHE STRING "")
  set(CMAKE_STATIC_LINKER_FLAGS_PROFILE
    "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "")
  set(CMAKE_MODULE_LINKER_FLAGS_PROFILE
    "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} -p" CACHE STRING "")
  mark_as_advanced(FORCE CMAKE_C_FLAGS_PROFILE CMAKE_CXX_FLAGS_PROFILE CMAKE_EXE_LINKER_FLAGS_PROFILE CMAKE_SHARED_LINKER_FLAGS_PROFILE CMAKE_STATIC_LINKER_FLAGS_PROFILE CMAKE_MODULE_LINKER_FLAGS_PROFILE)
  ## set postfix for binaries
  set(CMAKE_PROFILE_POSTFIX _profile)

  ## Add Profile to selectable build types
  set_property(CACHE CMAKE_BUILD_TYPE APPEND PROPERTY STRINGS Profile)
endif()

if(!MSVC)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
      option(ENABLE_NATIVE_BUILD "Build with -march=native" ON)
      if(ENABLE_NATIVE_BUILD)
        add_compile_options(-march=native)
     endif()
    endif()
endif()

function(setDefaultBuildType default_build_type)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Choose between you prefered build type." FORCE)
  endif()
endfunction()