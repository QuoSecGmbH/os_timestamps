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
set(CMAKE_C_FLAGS " -std=gnu11 -pedantic -D__STDC_FORMAT_MACROS -DHAVE_STRUCT_TIMESPEC=1 -D_POSIX_C_SOURCE=200809L -D_hypot=hypot -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-result")

include_directories(
  ./
  libs/current_time/
  libs/file_ts/
  libs/log/
  libs/misc/
  tests/general/
)

# Libraries-----------------------------------------------------------------
# Libs
#add_subdirectory(libs)


add_library(lib_log libs/log/log.h libs/log/log.c)
add_library(lib_file_ts libs/file_ts/file_ts.h libs/file_ts/file_ts.c)
add_executable(prototype_file_ts tools/prototype_file_ts.h tools/prototype_file_ts.c)
target_link_libraries(prototype_file_ts lib_file_ts lib_log)

add_library(lib_current_time libs/current_time/current_time.h libs/current_time/current_time.c)
#add_executable(prototype_current_time tools/prototype_current_time.h tools/prototype_current_time.c)
#target_link_libraries(prototype_current_time lib_current_time lib_log)

add_library(lib_misc libs/misc/misc.h libs/misc/misc.c)
add_library(lib_general tests/general/general.h tests/general/general.c)

add_executable(run_tests run_tests.h run_tests.c)
target_link_libraries(run_tests lib_general lib_file_ts lib_current_time lib_log lib_misc)
