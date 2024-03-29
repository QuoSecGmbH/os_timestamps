#ifndef MISC_C
#define MISC_C

#include "misc.h"

int VERBOSE;

testenv_struct* testenv_alloc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  testenv_struct* env = (testenv_struct*) calloc(sizeof(testenv_struct), 1);
  env->csv_file = csv_file;
  env->output_file = output_file;
  env->error_file = error_file;
  env->dir_path = dir_path;
  env->dir_path_volume = NULL;
  env->csv_file_flags = NULL;
  env->test_list = NULL;
  env->n_test = 0;
  env->testnot_list = NULL;
  env->n_testnot = 0;
  env->group_list = NULL;
  env->n_group = 0;
  env->groupnot_list = NULL;
  env->n_groupnot = 0;
  env->csv_path = NULL;
  env->csv_path_flags = NULL;
  return env;
}

testenv_struct* testenv_alloc_csv(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* dir_path_volume, FILE* csv_file_flags){
  testenv_struct* env = (testenv_struct*) calloc(sizeof(testenv_struct), 1);
  env->csv_file = csv_file;
  env->output_file = output_file;
  env->error_file = error_file;
  env->dir_path = dir_path;
  env->dir_path_volume = dir_path_volume;
  env->csv_file_flags = csv_file_flags;
  env->test_list = NULL;
  env->n_test = 0;
  env->testnot_list = NULL;
  env->n_testnot = 0;
  env->group_list = NULL;
  env->n_group = 0;
  env->groupnot_list = NULL;
  env->n_groupnot = 0;
  env->csv_path = NULL;
  env->csv_path_flags = NULL;
  return env; 
}

int misc_add_to_list(char* e, int* n, char*** list){
    (*n)++;
    *list = (char**) realloc(*list, (*n)*sizeof(char*));
    (*list)[*n-1] = e;
}

int misc_exec(char* command){
    return system(command);
}

char** misc_char_array1(char* c1){
    char** char_array = (char**) calloc(sizeof(char*), 1);
    char_array[0] = c1;
    
    return char_array;
}

char** misc_char_array2(char* c1, char* c2){
    char** char_array = (char**) calloc(sizeof(char*), 2);
    char_array[0] = c1;
    char_array[1] = c2;
    
    return char_array;
}

char** misc_char_array3(char* c1, char* c2, char* c3){
    char** char_array = (char**) calloc(sizeof(char*), 3);
    char_array[0] = c1;
    char_array[1] = c2;
    char_array[2] = c3;
    
    return char_array;
}

char** misc_char_array4(char* c1, char* c2, char* c3, char* c4){
    char** char_array = (char**) calloc(sizeof(char*), 4);
    char_array[0] = c1;
    char_array[1] = c2;
    char_array[2] = c3;
    char_array[3] = c4;
    
    return char_array;
}

char** misc_char_array5(char* c1, char* c2, char* c3, char* c4, char* c5){
    char** char_array = (char**) calloc(sizeof(char*), 5);
    char_array[0] = c1;
    char_array[1] = c2;
    char_array[2] = c3;
    char_array[3] = c4;
    char_array[4] = c5;
    
    return char_array;
}

void misc_wait_for_input() {
    getchar();
}


int misc_invert_check_result(int res){
    if (res == 0){
        return 2;
    }
    else if (res == 2){
        return 0;
    }
    return res;
}

int misc_str_in_list(char* ref, int list_size, char** list){
    if (list_size == 0 || list == NULL){
        return 0;
    }
    
    int i;
    for (i=0; i<list_size; i++){
        if (strcmp(ref, list[i]) == 0){
            return 1;
        }
    }
    
    return 0;
}

void misc_nanosleep(long ns){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = (time_t) ns / ns_1s;
    ts_ns->tv_nsec = ns % ns_1s;
    nanosleep(ts_ns, CLOCK_REALTIME);
    free(ts_ns);
}

void misc_microsleep(long us){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = us*1000;
    nanosleep(ts_ns, CLOCK_REALTIME);
    free(ts_ns);
}

void misc_millisleep(long ms){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = ms*1000000;
    nanosleep(ts_ns, CLOCK_REALTIME);
    free(ts_ns);
}

void misc_sleep(int s){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = s;
    ts_ns->tv_nsec = 0;
    nanosleep(ts_ns, CLOCK_REALTIME);
    free(ts_ns);
}

char* misc_concat(char* buf1, char* buf2){
    int len1 = strlen(buf1);
    int len2 = strlen(buf2);
    
    char* buf = calloc(sizeof(char), len1+len2+1);
    strcpy(buf, buf1);
    strcat(buf, buf2);
    
    return buf;
}

int misc_file_exists(char* buf){
    if( access( buf, F_OK ) != -1 ) {
        return 0;
    }
    return 1;
}

int misc_dir_exists(char* buf){
//     DIR* dir = opendir(buf);
//     if (dir != NULL) {
//         closedir(dir);
//         return 0;
//     } else {
//         return 1;
//     }
//     
    return stat_succeeds(buf);
}


char* misc_ensure_dir_exists(char* buf_path, char macb, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  if (misc_dir_exists(buf_path) != 0){
    if (VERBOSE >= 1){
        log_info(output_file, error_file, "misc_ensure_dir_exists in %s - Creating dir %s", func_name, buf_path);
    }
    
    int ret = mkdir(buf_path, 0700);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating dir");
    }
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = sleep_s;
    ts_ns->tv_nsec = sleep_ns; 
    nanosleep(ts_ns, CLOCK_REALTIME);
    
    if (macb){
        // MACB was set
        // Set M (+C):
        misc_concat_ensure_file_exists(buf_path, "tmp_mc", 0, 0, output_file, error_file, func_name);
        nanosleep(ts_ns, CLOCK_REALTIME);
        
        // Set A:
        DIR *dp = opendir(buf_path);
        struct dirent *de;   
        int first = 0;

        while (de != NULL || first == 0){
            de = readdir(dp);
            first = 1;
        }
        closedir(dp);
        nanosleep(ts_ns, CLOCK_REALTIME);
        
        // Set C:
        chmod(buf_path, 0700);
        nanosleep(ts_ns, CLOCK_REALTIME);
    }
  }
  
  return buf_path;
}

char* misc_concat_ensure_dir_exists(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  char* buf_path = misc_concat(buf1, buf2);
  return misc_ensure_dir_exists(buf_path, 0, sleep_s, sleep_ns, output_file, error_file, func_name);
}

char* misc_concat_ensure_dir_exists_macb(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  char* buf_path = misc_concat(buf1, buf2);
  return misc_ensure_dir_exists(buf_path, 1, sleep_s, sleep_ns, output_file, error_file, func_name);
}

char* misc_concat_ensure_file_exists_generic(char* buf1, char* buf2, int written_size, char macb, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  char* buf_path = misc_concat(buf1, buf2);
  if (misc_file_exists(buf_path) != 0){
    if (VERBOSE >= 1){
        log_info(output_file, error_file, "misc_concat_ensure_file_exists in %s - Creating file %s", func_name, buf_path);
    }
    
    FILE* fd = fopen(buf_path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
    }
    
    if (written_size != 0){
      char buf[115] = "lorem ipsum dolor sit amety consectetur adipiscing elita nulla et purus pulvinari mollis sapien ato suscipit nisl";
      if (written_size > 115){
        fwrite(buf, 1, 115, fd);
      }
      else {
        fwrite(buf, 1, written_size, fd);
      }
    }
    
    fclose(fd);
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = sleep_s;
    ts_ns->tv_nsec = 0; 
    nanosleep(ts_ns, CLOCK_REALTIME);
    misc_nanosleep(sleep_ns);
    
    if (macb == 1){
        // MACB was set
        // Set M (+C):
        FILE* f = fopen(buf_path, "a");
        char buf2[1] = "M";
        fwrite(buf2, 1, 1, f);
        fclose(f);
        
        nanosleep(ts_ns, CLOCK_REALTIME);
        misc_nanosleep(sleep_ns);
        
        // Set A:
        FILE* fd = fopen(buf_path, "rb");
        char* buf3 = (char*) calloc(2, sizeof(char));
        int n_read = fread(buf3, 1, 1, fd);
        fclose(fd);
        
        nanosleep(ts_ns, CLOCK_REALTIME);
        misc_nanosleep(sleep_ns);
        
        // Set C:
        
        chmod(buf_path, 0700);
        
        nanosleep(ts_ns, CLOCK_REALTIME);
        misc_nanosleep(sleep_ns);
    }
    
    free(ts_ns);
  }
  
  return buf_path;
}

char* misc_concat_ensure_file_exists(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  return misc_concat_ensure_file_exists_generic(buf1, buf2, 0, 0, sleep_s, sleep_ns, output_file, error_file, func_name);
}

void misc_concat_ensure_file_exists_free(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  char* buf = misc_concat_ensure_file_exists_generic(buf1, buf2, 0, 0, sleep_s, sleep_ns, output_file, error_file, func_name);
  free(buf);
}

char* misc_concat_ensure_file_exists_filled(char* buf1, char* buf2, int written_size, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  return misc_concat_ensure_file_exists_generic(buf1, buf2, written_size, 0, sleep_s, sleep_ns, output_file, error_file, func_name);
}

char* misc_concat_ensure_file_exists_filled_macb(char* buf1, char* buf2, int written_size, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  return misc_concat_ensure_file_exists_generic(buf1, buf2, written_size, 1, sleep_s, sleep_ns, output_file, error_file, func_name);
}

void misc_cp_rwx_no_overwrite(char* path1, char* path2){
    if (stat_succeeds(path2) == 1){
        // Case: path2 does not exist
        
        printf("Copying file\n");
    
        FILE* fd1 = fopen(path1, "rb"); 
        FILE* fd2 = fopen(path2, "wb"); 
        if (fd1 == NULL || fd2 == NULL) 
        { 
            return;
        } 
    
        unsigned long file_len;
        unsigned long counter;

        fseek(fd1, 0, SEEK_END);
        file_len=ftell(fd1);
        fseek(fd1, 0, SEEK_SET);
        
        char c;
        for(counter=0; counter < file_len; counter++) { 
            c = fgetc(fd1);
            fputc(c, fd2);  
        } 
    
        fclose(fd1); 
        fclose(fd2); 
        
        char mode[] = "0700";
        int i;
        i = strtol(mode, 0, 8);
        chmod(path2,i) ;
    }
}


void misc_print_timespec(char* desc, struct timespec* ts){
    time_t s = ts->tv_sec;
    long ns = ts->tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("%s: %s - s: %9ld - ns: %9ld\n", desc, buf, s, ns);
}

int misc_timespec_zero(struct timespec* ts){
    if (ts->tv_sec == 0 && ts->tv_nsec == 0){
        return 0;
    }
    return 1;
}

int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2){
    if (misc_timespec_leq(ts1, ts) == 0 && misc_timespec_leq(ts, ts2) == 0){
        return 0;
    }
    return 1;
}

int misc_timespec_l_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2){
    if (misc_timespec_l(ts1, ts) == 0 && misc_timespec_leq(ts, ts2) == 0){
        return 0;
    }
    return 1;
}

int misc_timespec_leq(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec < ts2->tv_sec){
        return 0;
    }
    else if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec <= ts2->tv_nsec){
        return 0;
    }
    return 1;
}

int misc_timespec_l(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec < ts2->tv_sec){
        return 0;
    }
    else if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec < ts2->tv_nsec){
        return 0;
    }
    return 1;
}

int misc_timespec_geq(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec > ts2->tv_sec){
        return 0;
    }
    else if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec >= ts2->tv_nsec){
        return 0;
    }
    return 1;
}

int misc_timespec_eq(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec == ts2->tv_nsec){
        return 0;
    }
    return 1;
}

struct timespec* misc_timespec_diff_ts2_ts1(struct timespec *ts1, struct timespec *ts2){
    struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec), 1);
    // ts2 > ts1 (ts2 is later than ts1)
    
    ts->tv_sec = ts2->tv_sec - ts1->tv_sec;
    if (ts2->tv_nsec >= ts1->tv_nsec){
        ts->tv_nsec = ts2->tv_nsec - ts1->tv_nsec;
    }
    else {
        ts->tv_nsec = 1000000000UL - (ts1->tv_nsec - ts2->tv_nsec);
        ts->tv_sec -= 1;
    }

    return ts;
}

struct timespec* misc_timespec_diff_abs(struct timespec *ts1, struct timespec *ts2){
    if (misc_timespec_geq(ts1, ts2) == 1){
        return misc_timespec_diff_ts2_ts1(ts1, ts2);
    }
    else {
        return misc_timespec_diff_ts2_ts1(ts2, ts1);
    }
}

int result_MAC_updated(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct timespec* ts_before, struct timespec* ts_after, struct stat_macb* file_stat) {
    int result = 0;
    
    if (ts_before == NULL || ts_after == NULL || file_stat == NULL){
        return 1;
    }
    
    if (M==UPDATE_MANDATORY || M==UPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M not updated");
            if (M==UPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    else if (M==NOUPDATE_MANDATORY || M==NOUPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M updated");
            if (M==NOUPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (A==UPDATE_MANDATORY || A==UPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A not updated");
            if (A==UPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    else if (A==NOUPDATE_MANDATORY || A==NOUPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A updated");
            if (A==NOUPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (C==UPDATE_MANDATORY || C==UPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C not updated");
            if (C==UPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    else if (C==NOUPDATE_MANDATORY || C==NOUPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C updated");
            if (C==NOUPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    
    return result;
}

int result_MAC_kept(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct stat_macb* file_stat_before, struct stat_macb* file_stat_after) {
    int result = 0;
    
    if (file_stat_before == NULL || file_stat_after == NULL){
        return 1;
    }
    
    if (M==KEEP_MANDATORY || M==KEEP_OPTIONAL){
        if (misc_timespec_eq(&(file_stat_before->st_mtim), &(file_stat_after->st_mtim)) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M not kept");
            if (M==KEEP_MANDATORY){
                result = 2;
            }
        }
    }
    else if (M==NOKEEP_MANDATORY || M==NOKEEP_OPTIONAL){
        if (misc_timespec_eq(&(file_stat_before->st_mtim), &(file_stat_after->st_mtim)) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M kept");
            if (M==NOKEEP_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (A==KEEP_MANDATORY || A==KEEP_OPTIONAL){
        if (misc_timespec_eq(&(file_stat_before->st_atim), &(file_stat_after->st_atim)) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A not kept");
            if (A==KEEP_MANDATORY){
                result = 2;
            }
        }
    }
    else if (A==NOKEEP_MANDATORY || A==NOKEEP_OPTIONAL){
        if (misc_timespec_eq(&(file_stat_before->st_atim), &(file_stat_after->st_atim)) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A kept");
            if (A==NOKEEP_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (C==KEEP_MANDATORY || C==KEEP_OPTIONAL){
        if (misc_timespec_eq(&(file_stat_before->st_ctim), &(file_stat_after->st_ctim)) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C not kept");
            if (C==KEEP_MANDATORY){
                result = 2;
            }
        }
    }
    else if (C==NOKEEP_MANDATORY || C==NOKEEP_OPTIONAL){
        if (misc_timespec_eq(&(file_stat_before->st_ctim), &(file_stat_after->st_ctim)) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C kept");
            if (C==NOKEEP_MANDATORY){
                result = 2;
            }
        }
    }
    
    return result;
}


int result_MAC_granularity(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, int divider_id, struct timespec* ts_before, struct timespec* ts_after, struct stat_macb* file_stat) {
    int result = 0;
    
    if (ts_before == NULL || ts_after == NULL || file_stat == NULL){
        return 1;
    }
    
    if (M==GRANULARITY_MANDATORY || M==GRANULARITY_OPTIONAL){
        if ((divider_id < GRANULARITY_LIST_LEN) && file_stat->st_mtim.tv_nsec % GRANULARITY_LIST[divider_id] == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M less accurate than expected");
            if (M==GRANULARITY_MANDATORY){
                result = 2;
            }
        }
        if ((divider_id != 0) && file_stat->st_mtim.tv_nsec % GRANULARITY_LIST[divider_id-1] != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M more accurate than expected");
            if (M==GRANULARITY_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (A==GRANULARITY_MANDATORY || A==GRANULARITY_OPTIONAL){
        if ((divider_id < GRANULARITY_LIST_LEN) && file_stat->st_atim.tv_nsec % GRANULARITY_LIST[divider_id] == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A less accurate than expected");
            if (A==GRANULARITY_MANDATORY){
                result = 2;
            }
        }
        if ((divider_id != 0) && file_stat->st_atim.tv_nsec % GRANULARITY_LIST[divider_id-1] != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A more accurate than expected");
            if (A==GRANULARITY_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (C==GRANULARITY_MANDATORY || C==GRANULARITY_OPTIONAL){
        if ((divider_id < GRANULARITY_LIST_LEN) && file_stat->st_ctim.tv_nsec % GRANULARITY_LIST[divider_id] == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C less accurate than expected");
            if (C==GRANULARITY_MANDATORY){
                result = 2;
            }
        }
        if ((divider_id != 0) && file_stat->st_ctim.tv_nsec % GRANULARITY_LIST[divider_id-1] != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C more accurate than expected");
            if (C==GRANULARITY_MANDATORY){
                result = 2;
            }
        }
    }
    
    return result;
}

int misc_check_profile_requirements(FILE* output_file, FILE* error_file, const char* func_name, struct profile_info_struct* pi, int** requirements){
    int result = 0;
    
    int i;
    for (i = 0; i < pi->watch_num; i++){
        char* path = pi->watch_array[i];
        int** profile = pi->profile;
        int* mac_result = profile[i];
        int* requirement = requirements[i];
        char* mac_string = "MAC";
        int error_printed = 0;
        
        int mac;
        for (mac = 0; mac < 3; mac++){
            if (requirement[mac] & UPDATE_NOCHECK){
                continue;
            }
            
            if (mac_result[mac] == -1){
                if (error_printed == 0){
                    log_info(output_file, error_file, "%s - %s %s", func_name, path, "Error in profile (non-existing file?)");
                    error_printed = 1;
                }
                continue;
            }
            
            if (mac_result[mac] & PROFILE_UPDATE_DELAY){
                log_warning(output_file, error_file, "%s - %s %c %s", func_name, path, mac_string[mac], "updated after command (during delay time)");
            }
            
            
            if (requirement[mac] & UPDATE_MANDATORY || requirement[mac] & UPDATE_OPTIONAL){
                if ((mac_result[mac] & PROFILE_UPDATE_COMMAND) == 0){
                    // Case: timestamp updated
                    log_warning(output_file, error_file, "%s - %s %c %s", func_name, path, mac_string[mac], "not updated");
                    
                    if (requirement[mac] & UPDATE_MANDATORY){
                        result = 2;
                    }
                }
            }
            
            if (requirement[mac] & NOUPDATE_MANDATORY || requirement[mac] & NOUPDATE_OPTIONAL){
                if ((mac_result[mac] & PROFILE_UPDATE_COMMAND) != 0){
                    // Case: timestamp not updated
                    log_warning(output_file, error_file, "%s - %s %c %s", func_name, path, mac_string[mac], "updated");
                    
                    if (requirement[mac] & NOUPDATE_MANDATORY){
                        result = 2;
                    }
                }
            }
        }
    }
    
    return result;
}

void misc_print_profile(FILE* output_file, FILE* error_file, struct profile_info_struct* pi){
    return misc_print_profile_masked(output_file, error_file, pi, pi->watch_array, NULL, NULL, NULL, NULL);
}


void misc_print_profile_masked(FILE* output_file, FILE* error_file, struct profile_info_struct* pi, char** watch_names, char* desc, char* func_name, FILE* csv_file_brief, FILE* csv_file_flags){
    if (watch_names == NULL){
        watch_names = pi->watch_array;
    }
    
    
    int i;
    for (i = 0; i < pi->watch_num; i++){
        char* path = watch_names[i];
        int** profile = pi->profile;
        int* macb_result = profile[i];
        char* macb_string = "MACB";
        char** macb_strings = calloc(5, sizeof(char*));
        macb_strings[0] = "M";
        macb_strings[1] = "A";
        macb_strings[2] = "C";
        macb_strings[3] = "B";
        
        fprintf(output_file, "%s\n", path);
//         printf("%s\n", path);
//         fprintf(output_file, "  ");
//         printf("  Command: ");
        
        int macb;
        char printed_verbose = 0;
        char* res_char = (char*) calloc(5, sizeof(char));
        for (macb = 0; macb < 4; macb++){
            if (macb_result[macb] == -1){
//                 printf("!");
                res_char[macb] = '!';
                continue;
            }
            
            char c = 0;
            char* flag = "";
            if (macb_result[macb] & PROFILE_ZERO){
//                 fprintf(output_file, "d", mac_string[mac]);
                if (c == 0){
                    c = '0';
                }           
                flag = "PROFILE_ZERO";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
                
//                 printf("%c", mac_string[mac]);
            }
            if (macb_result[macb] & PROFILE_UPDATE_DELAY){
//                 fprintf(output_file, "d", mac_string[mac]);
                if (c == 0){
                    c = 'd';
                }           
                flag = "PROFILE_UPDATE_DELAY";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
                
//                 printf("%c", mac_string[mac]);
            }
            if (macb_result[macb] & PROFILE_UPDATE_COMMAND){
//                 fprintf(output_file, "%c", mac_string[mac]);
                if (c == 0){
                    c = macb_string[macb];
                }
                flag = "PROFILE_UPDATE_COMMAND";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
//                 printf("%c", mac_string[mac]);
            }
            
            int inherit_flags_macb = PROFILE_SAMEAS_W0_M_BEFORE | PROFILE_SAMEAS_W0_A_BEFORE | PROFILE_SAMEAS_W0_C_BEFORE | PROFILE_SAMEAS_W0_B_BEFORE;
            int macb_results_inherit_macb = macb_result[macb] & inherit_flags_macb;
            
            if (macb_result[macb] & PROFILE_SAMEAS_W0_BEFORE){            
                if (macb_results_inherit_macb == 0 && c == 0){
                    // This should never happen, if PROFILE_SAMEAS_W0_BEFORE is set then at least one another (MACB) is also set
                    c = '>';
                }
                flag = "PROFILE_SAMEAS_W0_BEFORE";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (macb_result[macb] & PROFILE_EQ_COMMAND){
                flag = "PROFILE_EQ_COMMAND";
                if (c == 0){
                    c = '.';
                }
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (macb_result[macb] & PROFILE_SAMEAS_W0_M_BEFORE){             
                if (macb_results_inherit_macb == PROFILE_SAMEAS_W0_M_BEFORE && c == 0){
                    // If only one from MACB is the same
                    if (macb == 0) {
                        // If this is the same as before (directly inherited)
                        c = '>';
                    }
                    else {
                        c = 'm';
                    }
                }
                flag = "PROFILE_SAMEAS_W0_M_BEFORE";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (macb_result[macb] & PROFILE_SAMEAS_W0_A_BEFORE){             
                if (macb_results_inherit_macb == PROFILE_SAMEAS_W0_A_BEFORE && c == 0){
                    // If only one from MACB is the same
                    if (macb == 1) {
                        // If this is the same as before (directly inherited)
                        c = '>';
                    }
                    else {
                        c = 'a';
                    }
                }
                flag = "PROFILE_SAMEAS_W0_A_BEFORE";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (macb_result[macb] & PROFILE_SAMEAS_W0_C_BEFORE){             
                if (macb_results_inherit_macb == PROFILE_SAMEAS_W0_C_BEFORE && c == 0){
                    // If only one from MACB is the same
                    if (macb == 2) {
                        // If this is the same as before (directly inherited)
                        c = '>';
                    }
                    else {
                        c = 'c';
                    }
                }
                flag = "PROFILE_SAMEAS_W0_C_BEFORE";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (macb_result[macb] & PROFILE_SAMEAS_W0_B_BEFORE){             
                if (macb_results_inherit_macb == PROFILE_SAMEAS_W0_B_BEFORE && c == 0){
                    // If only one from MACB is the same
                    if (macb == 3) {
                        // If this is the same as before (directly inherited)
                        c = '>';
                    }
                    else {
                        c = 'b';
                    }
                }
                flag = "PROFILE_SAMEAS_W0_B_BEFORE";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            
            if (macb_result[macb] & PROFILE_SAMEAS_W0_BEFORE || macb_results_inherit_macb != 0){
                // If macb is inherited from PROFILE_SAMEAS_W0_BEFORE and at least one of macb, or multiple or macb
                if (c == 0){
                    c = 's';
                }
            }
            
            if (macb_result[macb] & PROFILE_EARLIER){
//                 fprintf(output_file, "-", mac_string[mac]);
//                 printf("%c", mac_string[mac]);                
                if (c == 0){
                    c = '-';
                }
                flag = "PROFILE_EARLIER";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (macb_result[macb] & PROFILE_LATER){
//                 fprintf(output_file, "+", mac_string[mac]);
//                 printf("%c", mac_string[mac]);                
                if (c == 0){
                    c = '+';
                }
                flag = "PROFILE_LATER";
                if (desc != NULL && csv_file_flags != NULL){
                    log_csv_add_line(csv_file_flags, 4, desc, path, macb_strings[macb], flag);
                }
                if (VERBOSE){
                    fprintf(output_file, "  %c %s\n", macb_string[macb], flag);
                    printed_verbose = 1;
                }
            }
            if (c == 0) {
//                 fprintf(output_file, ".");
                c = '?';
//                 printf("-");
            }
            
            res_char[macb] = c;
        }
//         if (printed_verbose) fprintf(output_file, "\n");
        fprintf(output_file, "  %c%c%c%c\n", res_char[0], res_char[1], res_char[2], res_char[3]);
        if (desc != NULL && csv_file_brief != NULL){
//             log_csv_add_line(csv_file_brief, 3, desc, path, res_char);
            log_csv_add_line(csv_file_brief, 2, misc_concat(misc_concat(desc, "."), path), res_char);
        }
//         printf("\n");
        
        
//         char delay_found = 0;
//         if (VERBOSE) fprintf(output_file, "  Delay:   ");
// //         printf("  Delay:   ");
//         for (mac = 0; mac < 3; mac++){
//             if (mac_result[mac] == -1){
//                 if (VERBOSE) fprintf(output_file, "!");
// //                 printf("!");
//                 continue;
//             }
//             
//             if (mac_result[mac] & PROFILE_UPDATE_DELAY){
//                 if (VERBOSE) fprintf(output_file, "%c", mac_string[mac]);
//                 delay_found = 1;
// //                 printf("%c", mac_string[mac]);
//             }
//             else {
//                 if (VERBOSE) fprintf(output_file, ".");
// //                 printf("-");
//             }
//         }
//         if (VERBOSE) fprintf(output_file, "\n");
// //         printf("\n");
//         if (delay_found == 1 && VERBOSE == 0){
//             log_warning(output_file, error_file, "Delay profiling would be necessary; please rerun with verbose option.");
//         }
    }
}

int misc_profile_eq(struct profile_info_struct* pi1, struct profile_info_struct* pi2){
    int** p1 = pi1->profile;
    int** p2 = pi2->profile;
    
    if (pi1->watch_num != pi2->watch_num){
        return 1;
    }
    
    int i;
    for (i = 0; i < pi1->watch_num; i++){
        int* mac_result1 = p1[i];
        int* mac_result2 = p2[i];
        
        int macb;
        for (macb = 0; macb < 4; macb++){
            if ((mac_result1[macb] & PROFILE_ZERO) != 0 && (mac_result2[macb] & PROFILE_ZERO) != 0){
                continue;
            }
            
            if ((mac_result1[macb] & PROFILE_UPDATE_DELAY) != (mac_result2[macb] & PROFILE_UPDATE_DELAY)){
                return 1;
            }
            
            int mask1 = PROFILE_UPDATE_COMMAND | PROFILE_SAMEAS_W0_BEFORE | PROFILE_EQ_COMMAND | PROFILE_ZERO;
            int mask2 = PROFILE_SAMEAS_W0_M_BEFORE | PROFILE_SAMEAS_W0_A_BEFORE | PROFILE_SAMEAS_W0_C_BEFORE | PROFILE_SAMEAS_W0_B_BEFORE;
            
            if ((mac_result1[macb] & mask1) != 0 && (mac_result1[macb] & mask1) == (mac_result2[macb] & mask1)){
                continue;
            }
            else if ((mac_result1[macb] & mask2) != 0 && (mac_result1[macb] & mask2) == (mac_result2[macb] & mask2)){
                continue;
            }
            else if (mac_result1[macb] != mac_result2[macb]){
                return 1;
            }
        }
    }
    return 0;
}

int misc_min2(int a, int b){
    if (a < b) return a;
    return b;
}

int misc_min3(int a, int b, int c){
    return misc_min2(misc_min2(a, b), c);
}

int misc_max2(int a, int b){
    if (a > b) return a;
    return b;
}

int misc_max3(int a, int b, int c){
    return misc_max2(misc_max2(a, b), c);
}

int misc_max4(int a, int b, int c, int d){
    return misc_max3(misc_max2(a, b), c, d);
}

void misc_file_copy(char* src, char* dst){
    FILE* srcFile = fopen(src, "rb");
    FILE* dstFile = fopen(dst,   "wb");

    char ch = fgetc(srcFile);
    while (ch != EOF) {
        fputc(ch, dstFile);
        ch = fgetc(srcFile);
    }
    
    fclose(srcFile);
    fclose(dstFile);
}

#endif
