cmake_minimum_required(VERSION 2.8)
project(posix_timestamps)
CMAKE_POLICY(SET CMP0015 NEW)
set (POSIX_TIMESTAMPS_VERSION "0.0.1")

# Default build type: Release
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (default Release)" FORCE)
endif()


# Options
# Compiler------------------------------------------------------------------
# Less warnings in C in order to avoid warnings about flex/bison code
set(CMAKE_C_FLAGS " -D__STDC_FORMAT_MACROS -DHAVE_STRUCT_TIMESPEC=1 -D_POSIX_C_SOURCE=200809L -D_hypot=hypot -pedantic -Wall")

include_directories(
  ./
)

# Libraries-----------------------------------------------------------------
# Libs
#add_subdirectory(libs)


add_executable(current_time current_time.h current_time.c)
add_executable(file_ts file_ts.h file_ts.c)
