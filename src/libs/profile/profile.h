#ifndef PROFILE_H
#define PROFILE_H

#include "profile.h"
#include "log.h"
#include "misc.h"
#include "current_time.h"
#include "file_ts.h"

int get_profile_value(struct timespec* ts_before, struct timespec* ts_after, struct timespec* ts_after_delay, struct timespec* ts_file_before, struct timespec* ts_file_command, int macb_index, struct timespec** W0_before_4, struct timespec* ts_file_delay);
int** compute_profile(struct timespec* ts_before, struct timespec* ts_after, struct timespec* ts_after_delay, int watch_num, struct stat_macb** multi_stat_before, struct stat_macb** multi_stat_after, struct stat_macb** multi_stat_after_delay);
struct profile_info_struct* profile_command(FILE* output_file, FILE* error_file, char* pwd_dir, char* src_dir, char* target_dir, int watch_num, char** watch_array, char* precommand, time_t wait_pre_s, long wait_pre_ns, char* command, time_t wait_command_s, long wait_command_ns);
struct profile_init_struct* profile_init(int watch_num, char** watch_array);
struct profile_info_struct* profile_analyze(struct profile_init_struct* pis, int watch_num, char** watch_array, time_t wait_command_s, long wait_command_ns);


#endif
