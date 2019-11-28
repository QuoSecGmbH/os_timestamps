cmake_minimum_required(VERSION 2.8)
project(os_timestamps)
CMAKE_POLICY(SET CMP0015 NEW)
set (OS_TIMESTAMPS_VERSION "0.0.1")

# Default build type: Release
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (default Release)" FORCE)
endif()


# Options
# Compiler------------------------------------------------------------------
# Less warnings in C in order to avoid warnings about flex/bison code
set(CMAKE_C_FLAGS " -std=gnu11 -O0 -pedantic -D__STDC_FORMAT_MACROS -DHAVE_STRUCT_TIMESPEC=1 -D_POSIX_C_SOURCE=200809L -D_hypot=hypot -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-result -Wno-implicit-function-declaration")
set(CMAKE_C_FLAGS_DEBUG " -O0 -g -fsanitize=address")
set(CMAKE_C_FLAGS_VALGRIND " -O0 -g")

include_directories(
  ./
  libs/current_time/
  libs/file_ts/
  libs/profile/
  libs/log/
  libs/misc/
  tests/profileos/
)

# Libraries-----------------------------------------------------------------
# Libs
#add_subdirectory(libs)


add_library(lib_log libs/log/log.h libs/log/log.c)
add_library(lib_file_ts libs/file_ts/file_ts.h libs/file_ts/file_ts.c)
add_library(lib_profile libs/profile/profile.h libs/profile/profile.c)

add_executable(prototype_file_ts tools/prototype_file_ts.h tools/prototype_file_ts.c)
target_link_libraries(prototype_file_ts lib_file_ts lib_log lib_misc)

add_library(lib_current_time libs/current_time/current_time.h libs/current_time/current_time_message.c libs/current_time/current_time.c)
target_link_libraries(lib_current_time lib_file_ts)

add_library(lib_misc libs/misc/misc.h libs/misc/misc.c)

add_library(lib_profileos
	tests/profileos/pos_filerename.h
	tests/profileos/pos_filerename.c
	tests/profileos/pos_localfilemove.h
	tests/profileos/pos_localfilemove.c
	tests/profileos/pos_volumefilemove.h
	tests/profileos/pos_volumefilemove.c
	tests/profileos/pos_filecopy.h
	tests/profileos/pos_filecopy.c
	tests/profileos/pos_fileaccess.h
	tests/profileos/pos_fileaccess.c
	tests/profileos/pos_filemodify.h
	tests/profileos/pos_filemodify.c
	tests/profileos/pos_filecreation.h
	tests/profileos/pos_filecreation.c
	tests/profileos/pos_filedelete.h
	tests/profileos/pos_filedelete.c
	tests/profileos/pos_dirlisting.h
	tests/profileos/pos_dirlisting.c
	tests/profileos/pos_dirtraversal.h
	tests/profileos/pos_dirtraversal.c
	tests/profileos/pos_execute.h
	tests/profileos/pos_execute.c
	tests/profileos/pos_filechange.h
	tests/profileos/pos_filechange.c
	)

add_executable(prototype_current_time tools/prototype_current_time.h tools/prototype_current_time.c)
target_link_libraries(prototype_current_time lib_file_ts lib_current_time lib_log lib_misc)

add_executable(profile_cmd profile_cmd.h profile_cmd.c)
target_link_libraries(profile_cmd lib_file_ts lib_profile lib_misc lib_log lib_current_time)

add_executable(profile_os profile_os.h profile_os.c)
target_link_libraries(profile_os lib_profileos lib_file_ts lib_profile lib_misc lib_log lib_current_time)
