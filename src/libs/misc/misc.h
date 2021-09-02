#ifndef MISC_H
#define MISC_H

#include "time.h"
#include "log.h"
#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "file_ts.h"
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
// #include "profile.h"

typedef struct testenv_struct{
    FILE* csv_file;
    FILE* output_file;
    FILE* error_file;
    FILE* csv_file_flags;
    char* dir_path;
    char* dir_path_volume;
    char** test_list;
    int n_test;
    char** testnot_list;
    int n_testnot;
    char** group_list;
    int n_group;
    char** groupnot_list;
    int n_groupnot;
} testenv_struct;

testenv_struct* testenv_alloc(FILE* csv_file, FILE* output_file, FILE* err_file, char* dir_path);
testenv_struct* testenv_alloc_csv(FILE* csv_file, FILE* output_file, FILE* err_file, char* dir_path, char* dir_path_volume, FILE* csv_file_flags);

static const int PROFILE_UPDATE_COMMAND = 0x01;
static const int PROFILE_UPDATE_DELAY = 0x02;
static const int PROFILE_SAMEAS_W0_BEFORE = 0x04;
static const int PROFILE_EARLIER = 0x08;
static const int PROFILE_LATER = 0x10;
static const int PROFILE_EQ_COMMAND = 0x20;
static const int PROFILE_ZERO = 0x40;
static const int PROFILE_SAMEAS_W0_M_BEFORE = 0x100;
static const int PROFILE_SAMEAS_W0_A_BEFORE = 0x200;
static const int PROFILE_SAMEAS_W0_C_BEFORE = 0x400;
static const int PROFILE_SAMEAS_W0_B_BEFORE = 0x800;

extern int PROFILE_TREAT_DELAY_AS_COMMAND;
extern gid_t CHOWN_GROUP_GID;

typedef struct profile_init_struct{
    struct stat_macb** multi_stat_before;
    struct timespec* ts_before;
} profile_init_struct;

typedef struct profile_info_struct{
    int** profile;
    int watch_num;
    char** watch_array;
    struct stat_macb** multi_stat_before;
    struct stat_macb** multi_stat_after;
    struct stat_macb** multi_stat_after_delay;
    struct timespec* ts_before;
    struct timespec* ts_after;
    struct timespec* ts_after_delay;
} profile_info_struct;

static const long ns_after_open = 100000000; //ns_100ms
// static const long ns_after_open = 1100000000; //ns_1.1s
static const long ns_DELAY = 1100000000; //ns_1.1s
// static const long ns_after_open = 10; //ns_100ms

static const time_t CMD_DELAY_S = 1;
// static const time_t CMD_DELAY_S = 0;
// static const long CMD_DELAY_NS = 0;
static const long CMD_DELAY_NS = 1100000000; // 1.1s

static const long ns_0ns = 0;
static const long ns_1ns = 1;
static const long ns_10ns = 10;
static const long ns_100ns = 100;
static const long ns_1us = 1000;
static const long ns_10us = 10000;
static const long ns_100us = 100000;
static const long ns_1ms = 1000000;
static const long ns_10ms = 10000000; // 10ms: smaller i / 10**i makes a difference with nanosleep + file write + *stat*
static const long ns_100ms = 100000000;
static const long ns_1s = 1000000000;

static const time_t s_0s = 0;
static const time_t s_1s = 1;
static const time_t s_10s = 10;

static const int UPDATE_MANDATORY = 1;
static const int UPDATE_OPTIONAL = 2;
static const int NOUPDATE_MANDATORY = 4;
static const int NOUPDATE_OPTIONAL = 8;
static const int UPDATE_NOCHECK = 16;

static const int KEEP_MANDATORY = 1;
static const int KEEP_OPTIONAL = 2;
static const int NOKEEP_MANDATORY = 4;
static const int NOKEEP_OPTIONAL = 8;
static const int KEEP_NOCHECK = 16;

static const int GRANULARITY_MANDATORY = 1;
static const int GRANULARITY_OPTIONAL = 2;
static const int GRANULARITY_NOCHECK = 4;

// static const int GRANULARITY_NS = 1000;
// static const int GRANULARITY_US = 1000000;
// static const int GRANULARITY_MS = 1000000000;


// static const long GRANULARITY_LIST[] = {ns_10ns, ns_100ns, ns_1us, ns_10us, ns_100us, ns_1ms, ns_10ms, ns_100ms, ns_1s}; // from 10ns to 1s
static const long GRANULARITY_LIST[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}; // from 10ns to 1s
static const int GRANULARITY_LIST_LEN = 9;

static const int GRANULARITY_NS = 0; // 10ns
static const int GRANULARITY_US = 3; // 10us
static const int GRANULARITY_MS = 6; // 10ms
static const int GRANULARITY_S = 9; // 10ms


extern int VERBOSE;

int misc_exec(char* command);

char** misc_char_array1(char* c1);
char** misc_char_array2(char* c1, char* c2);
char** misc_char_array3(char* c1, char* c2, char* c3);
char** misc_char_array4(char* c1, char* c2, char* c3, char* c4);
char** misc_char_array5(char* c1, char* c2, char* c3, char* c4, char* c5);

int misc_invert_check_result(int res);

int misc_str_in_list(char* ref, int list_size, char** list);

void misc_wait_for_input();

void misc_nanosleep(int ns);
void misc_microsleep(int us);
void misc_millisleep(int ms);
void misc_sleep(int s);

char* misc_concat(char* buf1, char* buf2);
int misc_file_exists(char* buf);
int misc_dir_exists(char* buf);

char* misc_ensure_dir_exists(char* buf_path, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);
char* misc_concat_ensure_dir_exists(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);
char* misc_concat_ensure_file_exists_generic(char* buf1, char* buf2, int written_size, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);
char* misc_concat_ensure_file_exists(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);
void misc_concat_ensure_file_exists_free(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);
char* misc_concat_ensure_file_exists_filled(char* buf1, char* buf2, int written_size, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);

void misc_cp_rwx_no_overwrite(char* path1, char* path2);

void misc_print_timespec(char* desc, struct timespec* ts);
int misc_timespec_zero(struct timespec* ts);
int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2);
int misc_timespec_l_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2);
int misc_timespec_leq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_l(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_geq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_eq(struct timespec* ts1, struct timespec* ts2);
struct timespec* misc_timespec_diff_ts2_ts1(struct timespec *ts1, struct timespec *ts2);
struct timespec* misc_timespec_diff_abs(struct timespec *ts1, struct timespec *ts2);

int result_MAC_updated(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct timespec* ts_before, struct timespec* ts_after, struct stat_macb* file_stat);
int result_MAC_granularity(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, int divider, struct timespec* ts_before, struct timespec* ts_after, struct stat_macb* file_stat);
int misc_check_profile_requirements(FILE* output_file, FILE* error_file, const char* func_name, profile_info_struct* pi, int** requirements);

void misc_print_profile(FILE* output_file, FILE* error_file, struct profile_info_struct* pi);
// void misc_print_profile_masked(FILE* output_file, FILE* error_file, struct profile_info_struct* pi, char** watch_names);
void misc_print_profile_masked(FILE* output_file, FILE* error_file, struct profile_info_struct* pi, char** watch_names, char* desc, char* func_name, FILE* csv_file_brief, FILE* csv_file_flags);
int misc_profile_eq(struct profile_info_struct* pi1, struct profile_info_struct* pi2);

int misc_min2(int a, int b);
int misc_min3(int a, int b, int c);
int misc_max2(int a, int b);
int misc_max3(int a, int b, int c);
int misc_max4(int a, int b, int c, int d);

#endif
