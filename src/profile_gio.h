#ifndef PROFILE_GIO_H
#define PROFILE_GIO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "misc.h"
#include "time.h"
#include "profile.h"

#include "p_gio_create.h"
#include "p_gio_rename.h"
#include "p_gio_copy.h"
#include "p_gio_delete.h"
#include "p_gio_modify.h"
#include "p_gio_move.h"
#include "p_gio_access.h"
#include "p_gio_change.h"
#include "p_gio_volume_fileMove.h"
// #include "nautilus_test.h"

#include "log.h"
#include "general.h"
#include "interfaces.h"
#include "utilities.h"
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "profile.h"


void print_usage();
int main(int argc, char *argv[]);
int run_profile_gio();

void group_profile_gio_rename_file(testenv_struct* env);
void group_profile_gio_rename_directory(testenv_struct* env);

void group_profile_gio_move_file(testenv_struct* env);
void group_profile_gio_move_directory(testenv_struct* env);

void group_profile_gio_create_file(testenv_struct* env);
void group_profile_gio_create_file_symlink(testenv_struct* env);
void group_profile_gio_create_file_intoSymlinkDir(testenv_struct* env);
void group_profile_gio_create_directory(testenv_struct* env);
void group_profile_gio_create_directory_symlink(testenv_struct* env);

void group_profile_gio_copy_file_new(testenv_struct* env);
void group_profile_gio_copy_file_existing(testenv_struct* env);

void group_profile_gio_delete_last_File(testenv_struct* env);
void group_profile_gio_delete_notLast_file(testenv_struct* env);
void group_profile_gio_delete_symlink_file(testenv_struct* env);
void group_profile_gio_delete_directory(testenv_struct* env);
void group_profile_gio_delete_symlink_directory(testenv_struct* env);

void group_profile_gio_access_file(testenv_struct* env);
void group_profile_gio_access_symlink(testenv_struct* env);

void group_profile_gio_modify_file(testenv_struct* env);
void group_profile_gio_modify_symlink(testenv_struct* env);

void group_profile_gio_change_file(testenv_struct* env);

void group_profile_gio_change_symlink_follow(testenv_struct* env);
void group_profile_gio_change_symlink_notFollow(testenv_struct* env);

void group_profile_gio_change_dir(testenv_struct* env);

void group_profile_gio_volume_fileMove(testenv_struct* env);
void group_profile_gio_volume_directoryMove(testenv_struct* env);

void group_profile_gio_nautilus_tests(testenv_struct* env);


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


#endif //PROFILE_GIO_H
