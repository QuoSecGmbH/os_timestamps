#ifndef PROFILE_OS_H
#define PROFILE_OS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "misc.h"
#include "time.h"
#include "profile.h"

#include "pos_filerename.h"
#include "pos_localfilemove.h"
#include "pos_volumefilemove.h"
#include "pos_filecopy.h"
#include "pos_filecreation.h"
#include "pos_fileaccess.h"
#include "pos_filemodify.h"
#include "pos_filedelete.h"
#include "pos_filechange.h"
#include "pos_dirlisting.h"
#include "pos_dirtraversal.h"
#include "pos_execute.h"

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
int main (int argc, char **argv);
int run_profileos();

void group_profileos_filerename(testenv_struct* env);
void group_profileos_dirrename(testenv_struct* env);

void group_profileos_localfilemove(testenv_struct* env);
void group_profileos_localdirmove(testenv_struct* env);
void group_profileos_volumefilemove(testenv_struct* env);
void group_profileos_volumedirmove(testenv_struct* env);

void group_profileos_filecopy_new(testenv_struct* env);
void group_profileos_filecopy_existing(testenv_struct* env);
void group_profileos_dircopy_notempty(testenv_struct* env);
void group_profileos_dircopy_empty(testenv_struct* env);

void group_profileos_filecreation(testenv_struct* env);
void group_profileos_filecreation_newhardlink(testenv_struct* env);
void group_profileos_filesymlink_creation(testenv_struct* env);
void group_profileos_filecreation_intosymlinkdir(testenv_struct* env);
void group_profileos_dircreation(testenv_struct* env);
void group_profileos_dirsymlink_creation(testenv_struct* env);
void group_profileos_symlinkfile_creation(testenv_struct* env);
void group_profileos_symlinkdir_creation(testenv_struct* env);

void group_profileos_fileaccess(testenv_struct* env);
void group_profileos_fileaccess_symlink(testenv_struct* env);
void group_profileos_symlink_readlink(testenv_struct* env);

void group_profileos_filemodify_symlink(testenv_struct* env);
void group_profileos_filemodify(testenv_struct* env);

void group_profileos_filechange(testenv_struct* env);
void group_profileos_symlinkchange(testenv_struct* env);
void group_profileos_symlinkchange_nofollow(testenv_struct* env);
void group_profileos_dirchange(testenv_struct* env);

void group_profileos_filedelete_last(testenv_struct* env);
void group_profileos_filedelete_notlast(testenv_struct* env);
void group_profileos_filedelete_symlink(testenv_struct* env);
void group_profileos_dirdelete(testenv_struct* env);
void group_profileos_dirdelete_symlink(testenv_struct* env);

void group_profileos_dirlisting_notempty(testenv_struct* env);
void group_profileos_dirlisting_empty(testenv_struct* env);
void group_profileos_dirlisting_symlink(testenv_struct* env);

void group_profileos_dirtraversal(testenv_struct* env);
void group_profileos_dirtraversal_symlink(testenv_struct* env);

void group_profileos_execute(testenv_struct* env);
void group_profileos_execute_symlink(testenv_struct* env);
void group_profileos_execute_intosymlinkdir(testenv_struct* env);

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


#endif
