#ifndef POSIX_TIMESTAMPS_PROFILE_QT_H
#define POSIX_TIMESTAMPS_PROFILE_QT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

extern "C" {
    #include "general.h"
    #include "interfaces.h"
    #include "utilities.h"

    #include "log.h"
    #include "misc.h"
    #include "time.h"
    #include "profile.h"
};

#include "p_qt_rename.h"
#include "p_qt_move.h"
#include "p_qt_copy.h"
#include "p_qt_create.h"
#include "p_qt_access.h"
#include "p_qt_modify.h"
#include "p_qt_change.h"
#include "p_qt_delete.h"
#include "p_qt_traversal.h"


void print_usage();
int main(int argc, char *argv[]);
int run_profile_qt();

void group_profile_qt_rename_file(testenv_struct* test_env);
void group_profile_qt_rename_directory(testenv_struct* test_env);

void group_profile_qt_move_file(testenv_struct* env);
void group_profile_qt_move_directory(testenv_struct* env);

void group_profile_qt_copy_file_new(testenv_struct* env);

void group_profile_qt_create_file(testenv_struct* env);

void group_profile_qt_create_file_symlink(testenv_struct* env);
void group_profile_qt_create_file_intoSymlinkDir(testenv_struct* env);
void group_profile_qt_create_directory(testenv_struct* env);
void group_profile_qt_create_directory_symlink(testenv_struct* env);

void group_profile_qt_access_file(testenv_struct* env);
void group_profile_qt_access_symlink(testenv_struct* env);

void group_profile_qt_modify_file(testenv_struct* env);
void group_profile_qt_modify_symlink(testenv_struct* env);

void group_profile_qt_change_file(testenv_struct* env);
void group_profile_qt_change_symlink_follow(testenv_struct* env);
void group_profile_qt_change_dir(testenv_struct* env);

void group_profile_qt_delete_last_File(testenv_struct* env);
void group_profile_qt_delete_notLast_file(testenv_struct* env);
void group_profile_qt_delete_symlink_file(testenv_struct* env);
void group_profile_qt_delete_directory(testenv_struct* env);
void group_profile_qt_delete_symlink_directory(testenv_struct* env);

void group_profile_qt_directory_traversal(testenv_struct* env);
void group_profile_qt_directory_traversal_symlink(testenv_struct* env);

void print_profile(struct profile_info_struct* pi, char** mask, testenv_struct* env, char* desc, char* func_name);
void process_profiles(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct** pi_list, int pi_num);
void process_profiles1(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1);
void process_profiles2(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2);
void process_profiles3(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3);
void process_profiles4(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4);
void process_profiles5(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5);
void process_profiles6(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6);
void process_profiles7(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7);
void process_profiles8(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7, struct profile_info_struct* pi8);


#endif //POSIX_TIMESTAMPS_PROFILE_QT_H
