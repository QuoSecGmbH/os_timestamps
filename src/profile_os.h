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
#include "pos_dirlisting.h"

#include "log.h"
#include "general.h"
#include "interfaces.h"
#include "utilities.h"
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "profile.h"
#include "misc.h"

int main (int argc, char **argv);
void group_profileos_filerename(testenv_struct* env);
void group_profileos_dirrename(testenv_struct* env);
void group_profileos_localfilemove(testenv_struct* env);
void group_profileos_localdirmove(testenv_struct* env);
void group_profileos_filecopy_new(testenv_struct* env);
void group_profileos_filecopy_existing(testenv_struct* env);
void group_profileos_dircopy(testenv_struct* env);
void group_profileos_fileaccess(testenv_struct* env);
void group_profileos_filemodify(testenv_struct* env);

void print_profile(struct profile_info_struct* pi, char** mask, testenv_struct* env);
void process_profiles(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct** pi_list, int pi_num);
void process_profiles1(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1);
void process_profiles2(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2);


#endif
