#ifndef MISC_C
#define MISC_C

#include "misc.h"

int VERBOSE;

int misc_invert_check_result(int res){
    if (res == 0){
        return 2;
    }
    else if (res == 2){
        return 0;
    }
    return res;
}

void misc_nanosleep(int ns){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = ns;
    nanosleep(ts_ns, NULL);
}

void misc_microsleep(int us){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = us*1000;
    nanosleep(ts_ns, NULL);
}

void misc_millisleep(int ms){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = ms*1000000;
    nanosleep(ts_ns, NULL);
}

void misc_sleep(int s){
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = s;
    ts_ns->tv_nsec = 0;
    nanosleep(ts_ns, NULL);
}

char* misc_concat(char* buf1, char* buf2){
    int len1 = strlen(buf1);
    int len2 = strlen(buf2);
    
    char* buf = calloc(sizeof(char), len1+len2+1);
    strcpy(buf, buf1);
    strcat(buf, buf2);
    
    return buf;
}

int misc_ensure_file_exists(char* buf){
    if( access( buf, F_OK ) != -1 ) {
        return 0;
    }
    return 1;
}

char* misc_concat_ensure_file_exists(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name){
  char* buf = misc_concat(buf1, buf2);
  if (misc_ensure_file_exists(buf) != 0){
    log_info(output_file, error_file, "misc_concat_ensure_file_exists in %s - Creating file %s", func_name, buf);
    
    FILE* fd = fopen(buf, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
    }
    fclose(fd);
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = sleep_s;
    ts_ns->tv_nsec = sleep_ns; 
    nanosleep(ts_ns, NULL);
    free(ts_ns);
  }
  
  
  return buf;
}

int stat_succeeds(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = stat(path, attr);
    if (res != 0){
        // stat failed
        return 1;
    }
    
    // stat succeeded
    return 0;
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

int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2){
    if (misc_timespec_leq(ts1, ts) == 0 && misc_timespec_leq(ts, ts2) == 0){
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

int result_MAC_updated(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat) {
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

int result_MAC_kept(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct stat* file_stat_before, struct stat* file_stat_after) {
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


int result_MAC_granularity(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, int divider_id, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat) {
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

#endif
