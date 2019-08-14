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
set(CMAKE_C_FLAGS " -std=gnu11 -O0 -pedantic -D__STDC_FORMAT_MACROS -DHAVE_STRUCT_TIMESPEC=1 -D_POSIX_C_SOURCE=200809L -D_hypot=hypot -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-result -Wno-implicit-function-declaration")
set(CMAKE_C_FLAGS_DEBUG " -O0 -g -fsanitize=address")
set(CMAKE_C_FLAGS_VALGRIND " -O0 -g")

include_directories(
  ./
  libs/current_time/
  libs/file_ts/
  libs/log/
  libs/misc/
  tests/general/
  tests/interfaces/
  tests/interfaces/file/
  tests/interfaces/file/w/
  tests/interfaces/file/r/
  tests/interfaces/file/new/
  tests/interfaces/file/ln/
)

# Libraries-----------------------------------------------------------------
# Libs
#add_subdirectory(libs)


add_library(lib_log libs/log/log.h libs/log/log.c)
add_library(lib_file_ts libs/file_ts/file_ts.h libs/file_ts/file_ts.c)

add_executable(prototype_file_ts tools/prototype_file_ts.h tools/prototype_file_ts.c)
target_link_libraries(prototype_file_ts lib_file_ts lib_log lib_misc)

add_executable(prototype_std_ts tools/prototype_std_ts.h tools/prototype_std_ts.c)
target_link_libraries(prototype_std_ts lib_file_ts lib_log lib_misc)

add_library(lib_current_time libs/current_time/current_time.h libs/current_time/current_time_message.c libs/current_time/current_time.c)
target_link_libraries(lib_current_time lib_file_ts)

add_library(lib_misc libs/misc/misc.h libs/misc/misc.c)
add_library(lib_general tests/general/general.h tests/general/general.c)
add_library(lib_interfaces 
	tests/interfaces/interfaces.h
       	tests/interfaces/interfaces.c 
	tests/interfaces/i_futimens.h
       	tests/interfaces/i_futimens.c 
	tests/interfaces/i_utimensat.h
       	tests/interfaces/i_utimensat.c
	tests/interfaces/i_utimes.h
	tests/interfaces/i_utimes.c
	tests/interfaces/i_utime.h
	tests/interfaces/i_utime.c
	tests/interfaces/file/i_file.h
	tests/interfaces/file/i_file.c
	tests/interfaces/file/i_fopen.h
	tests/interfaces/file/i_fopen.c
	tests/interfaces/file/w/i_file_w.h
	tests/interfaces/file/w/i_file_w.c
	tests/interfaces/file/w/i_file_w_fprintf.h
	tests/interfaces/file/w/i_file_w_fprintf.c
	tests/interfaces/file/w/i_file_w_printf.h
	tests/interfaces/file/w/i_file_w_printf.c
	tests/interfaces/file/w/i_file_w_fputc.h
	tests/interfaces/file/w/i_file_w_fputc.c
	tests/interfaces/file/w/i_file_w_fputs.h
	tests/interfaces/file/w/i_file_w_fputs.c
	tests/interfaces/file/w/i_file_w_fputwc.c
	tests/interfaces/file/w/i_file_w_fputwc.h
	tests/interfaces/file/w/i_file_w_fputws.c
	tests/interfaces/file/w/i_file_w_fputws.h
	tests/interfaces/file/w/i_file_w_fwprintf.c
	tests/interfaces/file/w/i_file_w_wprintf.h
	tests/interfaces/file/w/i_file_w_wprintf.c
	tests/interfaces/file/w/i_file_w_fwrite.h
	tests/interfaces/file/w/i_file_w_fwrite.c
	tests/interfaces/file/w/i_file_w_puts.h
	tests/interfaces/file/w/i_file_w_puts.c
	tests/interfaces/file/r/i_file_r.h
	tests/interfaces/file/r/i_file_r.c
	tests/interfaces/file/r/i_file_r_fread.h
	tests/interfaces/file/r/i_file_r_fread.c
	tests/interfaces/file/r/i_file_r_fgetc.h
	tests/interfaces/file/r/i_file_r_fgetc.c
	tests/interfaces/file/r/i_file_r_getc.h
	tests/interfaces/file/r/i_file_r_getc.c
	tests/interfaces/file/r/i_file_r_fgets.h
	tests/interfaces/file/r/i_file_r_fgets.c
	tests/interfaces/file/r/i_file_r_gets.h
	tests/interfaces/file/r/i_file_r_gets.c
	tests/interfaces/file/r/i_file_r_getchar.h
	tests/interfaces/file/r/i_file_r_getchar.c
	tests/interfaces/file/r/i_file_r_getdelim.h
	tests/interfaces/file/r/i_file_r_getdelim.c
	tests/interfaces/file/r/i_file_r_getline.h
	tests/interfaces/file/r/i_file_r_getline.c
	tests/interfaces/file/r/i_file_r_fscanf.h
	tests/interfaces/file/r/i_file_r_fscanf.c
	tests/interfaces/file/r/i_file_r_scanf.h
	tests/interfaces/file/r/i_file_r_scanf.c
	tests/interfaces/file/r/i_file_r_fwscanf.h
	tests/interfaces/file/r/i_file_r_fwscanf.c
	tests/interfaces/file/r/i_file_r_wscanf.h
	tests/interfaces/file/r/i_file_r_wscanf.c
	tests/interfaces/file/new/i_file_new.h
	tests/interfaces/file/new/i_file_new.c
	tests/interfaces/file/ln/i_file_ln.h
	tests/interfaces/file/ln/i_file_ln.c
	)

add_executable(prototype_current_time tools/prototype_current_time.h tools/prototype_current_time.c)
target_link_libraries(prototype_current_time lib_file_ts lib_current_time lib_log lib_misc)

add_executable(run_tests run_tests.h run_tests.c)
target_link_libraries(run_tests lib_general lib_interfaces lib_file_ts lib_current_time lib_log lib_misc)
