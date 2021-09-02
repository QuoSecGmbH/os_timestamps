struct testenv_struct;
#ifndef RUN_TESTS_C
#define RUN_TESTS_C

#include "run_tests.h"

int PROFILE_TREAT_DELAY_AS_COMMAND = 0;

char* POSIX_c181 = "POSIX_c181";
char* UNKNOWN = "UNKNOWN";
char* MANDATORY = "MANDATORY";
char* NEEDNOT = "NEEDNOT";
char* MAY = "MAY";

int OPTION_TEST_INPUT = 0;
int OPTION_DRYRUN = 0;

int REPEAT_WORST = 0;
int REPEAT_BEST = 1;

int runtest(testenv_struct* env, char* ref, int repeat, int repeatOperator, time_t sleep_s, long sleep_ns, int (*func)(FILE*, FILE*, FILE*, char*), char* func_name, char* spec, char* spec_name, char* speclevel, char* desc){
    int result = -1;
    int newresult = 0;
    char* curr_ref;
    int i;

    if (env->n_test != 0 && misc_str_in_list(ref, env->n_test, env->test_list) == 0){
        // Case: using a test whitelist and test ref is not listed
        return -1;
    }
    
    if (env->n_testnot != 0 && misc_str_in_list(ref, env->n_testnot, env->testnot_list) == 1){
        // Case: test ref is blacklisted
        return -1;
    }
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = sleep_s;
    ts_ns->tv_nsec = sleep_ns; 
    
    for (i=0; i<repeat; i++){
        nanosleep(ts_ns, CLOCK_REALTIME);
        
        if (OPTION_DRYRUN == 1){
            newresult = 1;
        }
        else {
            newresult = func(env->csv_file, env->output_file, env->error_file, env->dir_path);
        }
        
        if (result == -1){
            result = newresult;
        }
        
        if (repeat >= 2 && VERBOSE){
            curr_ref = (char*) calloc(strlen(ref)+20, 1);
            sprintf(curr_ref, "%s.%i", ref, i+1);
            log_csv_add_result(env->csv_file, env->output_file, env->error_file, newresult, desc, spec, spec_name, speclevel, curr_ref, func_name);
            free(curr_ref);
        }
        
        if (repeatOperator == REPEAT_BEST){
            if (newresult < result){
                result = newresult;
            }
        }
        else{
            if (newresult > result){
                result = newresult;
            }
        }
    }
    log_csv_add_result(env->csv_file, env->output_file, env->error_file, result, desc, spec, spec_name, speclevel, ref, func_name);
    
    free(ts_ns);
    
    return result;
}

void print_usage(){
    fprintf(stderr, "Usage: ./run_tests [options]\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -v, --verbose\n");
//     fprintf(stderr, "  --timewait / -t TIMEWAIT\n");
    fprintf(stderr, "  -d, --nodelay          Treat delays as command updates\n");
    fprintf(stderr, "  -i, --input-tests      Perform tests that require user input\n");
    fprintf(stderr, "  -a, --append           Append results to existing CSV file\n");
    fprintf(stderr, "  -t, --test             Whitelist test reference (will be run)\n");
    fprintf(stderr, "  -u, --test-not         Blacklist test reference (will not be run)\n");
    fprintf(stderr, "  -g, --group            Whitelist group reference (will be run)\n");
    fprintf(stderr, "  -h, --group-not        Blacklist group reference (will not be run)\n");
    fprintf(stderr, "  -0, --dry-run          Dry run (no test is actually run but it outputs the list of tests)\n");
}

int main (int argc, char **argv){  
    int OPTION_APPEND_CSV = 0;
  
    int i;
    char* dir_base_path = "tmp_tests";
    char* dir_path = NULL;
    for (i = 0; i <= 99; i++){
        char* buf = (char*) calloc(sizeof(char), strlen(dir_base_path)+6);
        sprintf(buf, "%s_%02d/", dir_base_path, i);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        if (stat(buf, attr) == -1) {
            mkdir(buf, 0700);
            dir_path = buf;
            free(attr);
            break;
        }
        free(buf);
        free(attr);
    }
    
    
    char** test_list = NULL;
    int n_test = 0;
    char** testnot_list = NULL;
    int n_testnot = 0;
    char** group_list = NULL;
    int n_group = 0;
    char** groupnot_list = NULL;
    int n_groupnot = 0;
    
    int c;
    while (1) {
        static struct option long_options[] =
            {
            {"verbose", no_argument,       0, 'v'},
            {"nodelay", no_argument,       0, 'd'},
            {"input-tests", no_argument, 0, 'i'},
            {"append", no_argument, 0, 'a'},
            {"dry-run", no_argument, 0, '0'},
//             {"timewait", required_argument, 0, 't'},
            {"test", required_argument, 0, 't'},
            {"test-not", required_argument, 0, 'u'},
            {"group", required_argument, 0, 'g'},
            {"group-not", required_argument, 0, 'h'},
            {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "vdia0t:u:g:h:",
                        long_options, &option_index);
        
            
        if (c == -1)
            break;

        switch (c)
            {
            case 'v': {
                VERBOSE = 1; 
                break;
            }            
            case 'd': {
                PROFILE_TREAT_DELAY_AS_COMMAND = 1; 
                break;
            }
            case 'i': {
                OPTION_TEST_INPUT = 1;
                break;
            }            
            case '0': {
                OPTION_DRYRUN = 1;
                break;
            }
            case 'a': {
                OPTION_APPEND_CSV = 1;
                break;
            }
            case 't': {
                if (VERBOSE) printf("Whitelisting test: %s\n", optarg);
//                 misc_add_to_list(optarg, &(test_env->n_test), &(test_env->test_list));
                misc_add_to_list(optarg, &(n_test), &(test_list));
                break;
            }
            case 'u': {
                if (VERBOSE) printf("Blacklisting test: %s\n", optarg);
//                 misc_add_to_list(optarg, &(test_env->n_testnot), &(test_env->testnot_list));
                misc_add_to_list(optarg, &(n_testnot), &(testnot_list));
                break;
            }
            case 'g': {
                if (VERBOSE) printf("Whitelisting group: %s\n", optarg);
//                 misc_add_to_list(optarg, &(test_env->n_group), &(test_env->group_list));
                misc_add_to_list(optarg, &(n_group), &(group_list));
                break;
            }
            case 'h': {
                if (VERBOSE) printf("Blacklisting group: %s\n", optarg);
//                 misc_add_to_list(optarg, &(test_env->n_groupnot), &(test_env->groupnot_list));
                misc_add_to_list(optarg, &(n_groupnot), &(groupnot_list));
                break;
            }
            default:
                fprintf(stderr, "Unknown argument.\n");
                print_usage();
                exit(EXIT_FAILURE);
            }
        }
    
        
    FILE* csv_file = NULL;
    if (OPTION_APPEND_CSV == 1){
        csv_file = log_open_csv_append("results.csv");
    }
    else {
        csv_file = log_open_csv("results.csv");
    }
    
//     FILE* output_file = stdout;
    FILE* output_file = fopen("output.txt", "wb");
//     FILE* error_file = stderr;
    FILE* error_file = fopen("error.txt", "wb");
    testenv_struct* test_env = testenv_alloc(csv_file, output_file, error_file, dir_path);
    test_env->n_test = n_test;
    test_env->test_list = test_list;
    test_env->n_testnot = n_testnot;
    test_env->testnot_list = testnot_list;
    test_env->n_group = n_group;
    test_env->group_list = group_list;
    test_env->n_groupnot = n_groupnot;
    test_env->groupnot_list = groupnot_list;
    
    if (dir_path == NULL){
        log_error(output_file, error_file, "%s", "Impossible to find suitable directory for tests, exiting.");
        return 1;
    }
    log_info(output_file, error_file, "Directory for tests is: %s", dir_path);
    
    current_time_setup_local_timemarker(output_file, error_file);
    current_time_setup_local_timemarkerdir(output_file, error_file);
    
    // pre-creating some of the test files
//     misc_concat_ensure_file_exists_free(dir_path, "/tmp/tmp_posixtest_timemarker", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.futimens", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.utimensat", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.utimes", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.utime", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fflush.write", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fflush.nowrite", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fseek.write", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fseek.nowrite", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fsync.write", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fsync.nowrite", s_0s, ns_0ns, output_file, error_file, __func__);
//     
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.writemode.w", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.writemode.wb", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.writemode.w+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.writemode.wb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.writemode.w+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.w", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.wb", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.w+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.wb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.w+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.r+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.rb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fwrite.existing.writemode.r+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.w", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.wb", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.w+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.wb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.w+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.r+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.rb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.dir.writemode.r+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.readmode.r", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.readmode.rb", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.readmode.r+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.readmode.rb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen.existing.readmode.r+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.readmode.r", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.readmode.rb", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.readmode.r+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.readmode.rb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.readmode.r+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.writemode.w+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.writemode.wb+", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.fopen_fread.existing.writemode.w+b", s_0s, ns_0ns, output_file, error_file, __func__);
//     
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.w.fprintf_fflush", s_0s, ns_0ns, output_file, error_file, __func__);
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.file.w.fprintf_ffclose", s_0s, ns_0ns, output_file, error_file, __func__);
    
    
        
    misc_concat_ensure_file_exists_free(dir_path, "run_test_pause", 2*s_1s, ns_0ns, output_file, error_file, __func__);
    
    if (OPTION_APPEND_CSV == 0) log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Level", "Ref", "Function");
    group_check_general_clock(test_env);
    group_check_general_new_file(test_env);
    group_check_general_update(test_env);
    
    group_check_interfaces_exec(test_env);
    group_check_interfaces_attr(test_env);
    group_check_interfaces_ts_futimens(test_env);
    group_check_interfaces_ts_utimensat(test_env);
    group_check_interfaces_ts_utimes(test_env);
    group_check_interfaces_ts_utime(test_env);
    group_check_interfaces_file(test_env);
    group_check_interfaces_file_fopen(test_env);
    group_check_interfaces_file_w(test_env);
    group_check_interfaces_file_r(test_env);
    group_check_interfaces_dir(test_env);
    group_check_interfaces_file_ln(test_env);
    group_check_interfaces_file_new(test_env);
    group_check_interfaces_file_mv(test_env);
    group_check_interfaces_file_rm(test_env);
    
    group_check_utilities_attr(test_env);
    group_check_utilities_cp(test_env);
    group_check_utilities_new(test_env);
    group_check_utilities_mv(test_env);
    group_check_utilities_rm(test_env);
    group_check_utilities_ln(test_env);
    group_check_utilities_ls(test_env);
    
    group_check_utilities_vi(test_env);
    group_check_utilities_ed(test_env);
    group_check_utilities_ex(test_env);
    
    free(test_env);
    free(dir_path);
    
    log_close_csv(csv_file);
}

int should_group_run(testenv_struct* env, char* group){
    if (env->n_group != 0 && misc_str_in_list(group, env->n_group, env->group_list) == 0){
        // Case: using a group whitelist and group is not listed
        return 0;
    }
    
    if (env->n_groupnot != 0 && misc_str_in_list(group, env->n_groupnot, env->groupnot_list) == 1){
        // Case: group is blacklisted
        return 0;
    }
    
    return 1;
}

void group_check_general_clock(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "GENERAL.CLOCK.RES", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_clock_res, "check_general_clock_res", "Yes", POSIX_c181, MANDATORY, "Clock resolution shall be at least 0.02s (CLOCK_REALTIME)");
    runtest(env, "GENERAL.CLOCK.REALTIME.INCREMENTS", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_clock_realtime_increments, "check_general_clock_realtime_increments", "No", "", MANDATORY, "Clock CLOCK_REALTIME is incremental (increasing)");
    runtest(env, "GENERAL.CLOCK.FSLIKE.INCREMENTS", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_clock_ns_fslike_osspecific_increments, "check_general_clock_ns_fslike_osspecific_increments", "No", "", MANDATORY, "Clock (ns_fslike_osspecific) is incremental (increasing)");
}

void group_check_general_new_file(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "GENERAL.NEW_FILE", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_new_file, "check_general_new_file", "Yes", POSIX_c181, MANDATORY, "New file shall have MAC updated");
    runtest(env, "GENERAL.NEW_FILE_REALTIME", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_new_file_realtime, "check_general_new_file_realtime", "No", "", UNKNOWN, "New file shall have MAC updated (CLOCK_REALTIME)");
    runtest(env, "GENERAL.NEW_FILE.MAC_eq", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_new_file_mac_eq, "check_general_new_file_mac_eq", "No", "", MANDATORY, "New file shall have MAC set to same value");
}

void group_check_general_update(testenv_struct* env){ 
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "GENERAL.UPDATE.WRITE_CLOSE", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_write_close, "check_general_update_write_close", "Yes", POSIX_c181, MANDATORY, "fwrite+fclose shall update MC");
    runtest(env, "GENERAL.UPDATE.WRITE_STAT", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_write_stat, "check_general_update_write_stat", "No", "", UNKNOWN, "fwrite+stat shall update MC");
    runtest(env, "GENERAL.UPDATE.WRITE_FSTAT", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_write_fstat, "check_general_update_write_fstat", "No", "", UNKNOWN, "fwrite+fstat shall update MC");
    runtest(env, "GENERAL.UPDATE.WRITE", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_write, "check_general_update_write", "No", "", UNKNOWN, "fwrite shall update MC");
    runtest(env, "GENERAL.UPDATE.READ_CLOSE", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_read_close, "check_general_update_read_close", "Yes", POSIX_c181, MANDATORY, "fread+fclose shall update A");
    runtest(env, "GENERAL.UPDATE.READ_STAT", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_read_stat, "check_general_update_read_stat", "Yes", POSIX_c181, MANDATORY, "fread+stat shall update A");
    runtest(env, "GENERAL.UPDATE.READ", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_read, "check_general_update_read", "No", "", MANDATORY, "fread shall not update A");
    runtest(env, "GENERAL.UPDATE.MARK.READ", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_mark_read, "check_general_update_mark_read", "Yes", POSIX_c181, MANDATORY, "fread shall mark A for update");
    runtest(env, "GENERAL.UPDATE.READ_FSTAT", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_read_fstat, "check_general_update_read_fstat", "Yes", POSIX_c181, MANDATORY, "fread+fstat shall update A");
    runtest(env, "GENERAL.UPDATE.FOPEN_R", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_fopen_r, "check_general_update_fopen_r", "Yes", POSIX_c181, MANDATORY, "fopen(rb) shall not update MAC");
    runtest(env, "GENERAL.UPDATE.FOPEN_R_FSTAT_FCLOSE", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_fopen_r_fstat_fclose, "check_general_update_fopen_r_fstat_fclose", "Yes", POSIX_c181, MANDATORY, "fopen(rb)+fstat+fclose shall not update MAC");
}

void group_check_interfaces_exec(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.EXEC.EXECVP", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_exec_execvp, "check_interfaces_exec_execvp", "Yes", POSIX_c181, MANDATORY, "exec shall update A");
    runtest(env, "INTERFACES.EXEC.EXECVP_LOCAL", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_exec_execvp_local, "check_interfaces_exec_execvp_local", "Yes", POSIX_c181, MANDATORY, "exec shall update A (local)");
}

void group_check_interfaces_attr(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.ATTR.CHMOD", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chmod, "check_interfaces_attr_chmod", "Yes", POSIX_c181, MANDATORY, "chmod shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_GRP", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_grp, "check_interfaces_attr_chown_grp", "Yes", POSIX_c181, MANDATORY, "chown(-1, getgid()) shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_USR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_usr, "check_interfaces_attr_chown_usr", "Yes", POSIX_c181, MANDATORY, "chown(getuid(), -1) shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_GRP_USR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_grp_usr, "check_interfaces_attr_chown_grp_usr", "Yes", POSIX_c181, MANDATORY, "chown(getuid(), getgid()) shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_NOCHANGE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_nochange, "check_interfaces_attr_chown_nochange", "Yes", POSIX_c181, NEEDNOT, "chown(-1, -1) need not update MAC");
}

void group_check_interfaces_ts_futimens(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_ma, "check_interfaces_ts_futimens_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with futimens shall set MA and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_NS", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_ns, "check_interfaces_ts_futimens_now_ns", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with futimens shall give MA granularity to the nanoseconds");
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_MA_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_ma_eq, "check_interfaces_ts_futimens_now_ma_eq", "No", "", MANDATORY, "Setting MA to now with futimens shall set MA to same value");
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_MAC_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_mac_eq, "check_interfaces_ts_futimens_now_mac_eq", "No", "", MANDATORY, "Setting MA to now with futimens shall set MAC to same value");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.FUTURE.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_future_a, "check_interfaces_ts_futimens_set_future_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a future value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.PAST.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_past_a, "check_interfaces_ts_futimens_set_past_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a past value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.FUTURE.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_future_m, "check_interfaces_ts_futimens_set_future_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a future value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.PAST.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_past_m, "check_interfaces_ts_futimens_set_past_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a past value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_future_ma, "check_interfaces_ts_futimens_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_past_ma, "check_interfaces_ts_futimens_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.OMIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_omit, "check_interfaces_ts_futimens_set_omit", "Yes", POSIX_c181, NEEDNOT, "With UTIME_OMIT, C need not to be updated");
}

void group_check_interfaces_ts_utimensat(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_ma, "check_interfaces_ts_utimensat_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimensat shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_NS", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_ns, "check_interfaces_ts_utimensat_now_ns", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimensat shall give MA granularity to the nanoseconds");
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_MA_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_ma_eq, "check_interfaces_ts_utimensat_now_ma_eq", "No", "", MANDATORY, "Setting MA to now with utimensat shall set MA to same value");
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_MAC_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_mac_eq, "check_interfaces_ts_utimensat_now_mac_eq", "No", "", MANDATORY, "Setting MA to now with utimensat shall set MAC to same value");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.FUTURE.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_future_a, "check_interfaces_ts_utimensat_set_future_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a future value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.PAST.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_past_a, "check_interfaces_ts_utimensat_set_past_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a past value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.FUTURE.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_future_m, "check_interfaces_ts_utimensat_set_future_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a future value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.PAST.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_past_m, "check_interfaces_ts_utimensat_set_past_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a past value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_future_ma, "check_interfaces_ts_utimensat_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_past_ma, "check_interfaces_ts_utimensat_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.OMIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_omit, "check_interfaces_ts_utimensat_set_omit", "Yes", POSIX_c181, NEEDNOT, "With UTIME_OMIT, C need not to be updated");
}

void group_check_interfaces_ts_utimes(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.TS.UTIMES_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimes_now_ma, "check_interfaces_ts_utimes_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimes shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMES_NOW_US", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_utimes_now_us, "check_interfaces_ts_utimes_now_us", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimes shall give MA granularity to the microsecond");

    runtest(env, "INTERFACES.TS.UTIMES.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimes_set_future_ma, "check_interfaces_ts_utimes_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMES.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimes_set_past_ma, "check_interfaces_ts_utimes_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
}

void group_check_interfaces_ts_utime(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.TS.UTIME_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utime_now_ma, "check_interfaces_ts_utime_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utime shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIME_NOW_S", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_utime_now_s, "check_interfaces_ts_utime_now_us", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utime shall give MA granularity to the second");

    runtest(env, "INTERFACES.TS.UTIME.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utime_set_future_ma, "check_interfaces_ts_utime_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIME.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utime_set_past_ma, "check_interfaces_ts_utime_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
}

void group_check_interfaces_file(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.FILE.FFLUSH.WRITE.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fflush_write_imm, "check_interfaces_file_fflush_write_imm", "No", "", MANDATORY, "fflush with unwritten data shall update MC");
    runtest(env, "INTERFACES.FILE.FFLUSH.WRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fflush_write, "check_interfaces_file_fflush_write", "Yes", POSIX_c181, MANDATORY, "fflush with unwritten data shall mark MC for update");
    runtest(env, "INTERFACES.FILE.FFLUSH.NOWRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fflush_nowrite, "check_interfaces_file_fflush_nowrite", "No", "", MANDATORY, "fflush with no unwritten data shall not update MAC");
    runtest(env, "INTERFACES.FILE.FSEEK.WRITE.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fseek_write_imm, "check_interfaces_file_fseek_write_imm", "No", "", MANDATORY, "fseek with unwritten data shall update MC");
    runtest(env, "INTERFACES.FILE.FSEEK.WRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fseek_write, "check_interfaces_file_fseek_write", "Yes", POSIX_c181, MANDATORY, "fseek with unwritten data shall mark MC for update");
    runtest(env, "INTERFACES.FILE.FSEEK.NOWRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fseek_nowrite, "check_interfaces_file_fseek_nowrite", "No", "", MANDATORY, "fseek with no unwritten data shall not update MAC");
    runtest(env, "INTERFACES.FILE.FSYNC.WRITE.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fsync_write_imm, "check_interfaces_file_fsync_write_imm", "Yes", POSIX_c181, MANDATORY, "fsync with unwritten data shall update MC");
    runtest(env, "INTERFACES.FILE.FSYNC.WRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fsync_write, "check_interfaces_file_fsync_write", "Yes", "", MANDATORY, "fsync with unwritten data shall mark MC for update");
    runtest(env, "INTERFACES.FILE.FSYNC.NOWRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fsync_nowrite, "check_interfaces_file_fsync_nowrite", "No", "", MANDATORY, "fsync with no unwritten data shall not update MAC");
}

void group_check_interfaces_file_fopen(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.W", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_W, "check_interfaces_file_fopen_new_W", "Yes", POSIX_c181, MANDATORY, "fopen(w) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.WB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_WB, "check_interfaces_file_fopen_new_WB", "Yes", POSIX_c181, MANDATORY, "fopen(wb) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_A, "check_interfaces_file_fopen_new_A", "Yes", POSIX_c181, MANDATORY, "fopen(a) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.AB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_AB, "check_interfaces_file_fopen_new_AB", "Yes", POSIX_c181, MANDATORY, "fopen(ab) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.W+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_WP, "check_interfaces_file_fopen_new_WP", "Yes", POSIX_c181, MANDATORY, "fopen(w+) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.WB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_WBP, "check_interfaces_file_fopen_new_WBP", "Yes", POSIX_c181, MANDATORY, "fopen(wb+) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.W+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_WPB, "check_interfaces_file_fopen_new_WPB", "Yes", POSIX_c181, MANDATORY, "fopen(w+b) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.A+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_AP, "check_interfaces_file_fopen_new_AP", "Yes", POSIX_c181, MANDATORY, "fopen(a+) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.AB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_ABP, "check_interfaces_file_fopen_new_ABP", "Yes", POSIX_c181, MANDATORY, "fopen(ab+) on non existing file shall create file, update file MAC and parent directory MC");
    runtest(env, "INTERFACES.FILE.FOPEN.NEW.A+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_new_APB, "check_interfaces_file_fopen_new_APB", "Yes", POSIX_c181, MANDATORY, "fopen(a+b) on non existing file shall create file, update file MAC and parent directory MC");
    
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.W", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_W, "check_interfaces_file_fopen_existing_W", "Yes", POSIX_c181, MANDATORY, "fopen(w) on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.WB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_WB, "check_interfaces_file_fopen_existing_WB", "Yes", POSIX_c181, MANDATORY, "fopen(wb) on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.W+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_WP, "check_interfaces_file_fopen_existing_WP", "Yes", POSIX_c181, MANDATORY, "fopen(w+) on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.WB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_WBP, "check_interfaces_file_fopen_existing_WBP", "Yes", POSIX_c181, MANDATORY, "fopen(wb+) on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.W+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_WPB, "check_interfaces_file_fopen_existing_WPB", "Yes", POSIX_c181, MANDATORY, "fopen(w+b) on existing file shall update file MC");
    
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.W", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_W, "check_interfaces_file_fopen_fwrite_existing_W", "Yes", POSIX_c181, MANDATORY, "fopen(w)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.WB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_WB, "check_interfaces_file_fopen_fwrite_existing_WB", "Yes", POSIX_c181, MANDATORY, "fopen(wb)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.W+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_WP, "check_interfaces_file_fopen_fwrite_existing_WP", "Yes", POSIX_c181, MANDATORY, "fopen(w+)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.WB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_WBP, "check_interfaces_file_fopen_fwrite_existing_WBP", "Yes", POSIX_c181, MANDATORY, "fopen(wb+)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.W+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_WPB, "check_interfaces_file_fopen_fwrite_existing_WPB", "Yes", POSIX_c181, MANDATORY, "fopen(w+b)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.R+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_RP, "check_interfaces_file_fopen_fwrite_existing_RP", "Yes", "", MANDATORY, "fopen(r+)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.RB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_RBP, "check_interfaces_file_fopen_fwrite_existing_RBP", "Yes", "", MANDATORY, "fopen(rb+)+fwrite on existing file shall update file MC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.R+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_RPB, "check_interfaces_file_fopen_fwrite_existing_RPB", "Yes", "", MANDATORY, "fopen(r+b)+fwrite on existing file shall update file MC");
    
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.W", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_W, "check_interfaces_file_fopen_fwrite_existing_dir_W", "Yes", "", MANDATORY, "fopen(w)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.WB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_WB, "check_interfaces_file_fopen_fwrite_existing_dir_WB", "Yes", "", MANDATORY, "fopen(wb)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.W+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_WP, "check_interfaces_file_fopen_fwrite_existing_dir_WP", "Yes", "", MANDATORY, "fopen(w+)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.WB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_WBP, "check_interfaces_file_fopen_fwrite_existing_dir_WBP", "Yes", "", MANDATORY, "fopen(wb+)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.W+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_WPB, "check_interfaces_file_fopen_fwrite_existing_dir_WPB", "Yes", "", MANDATORY, "fopen(w+b)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.R+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_RP, "check_interfaces_file_fopen_fwrite_existing_dir_RP", "Yes", "", MANDATORY, "fopen(r+)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.RB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_RBP, "check_interfaces_file_fopen_fwrite_existing_dir_RBP", "Yes", "", MANDATORY, "fopen(rb+)+fwrite on existing file shall not update parent directory MAC");
    runtest(env, "INTERFACES.FILE.FOPEN_FWRITE.EXISTING.DIR.R+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fwrite_existing_dir_RPB, "check_interfaces_file_fopen_fwrite_existing_dir_RPB", "Yes", "", MANDATORY, "fopen(r+b)+fwrite on existing file shall not update parent directory MAC");
    
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.R", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_R, "check_interfaces_file_fopen_existing_R", "Yes", POSIX_c181, MANDATORY, "fopen(r) on existing file shall not update MAC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.RB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_RB, "check_interfaces_file_fopen_existing_RB", "Yes", POSIX_c181, MANDATORY, "fopen(rb) on existing file shall not update MAC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.R+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_RP, "check_interfaces_file_fopen_existing_RP", "Yes", POSIX_c181, MANDATORY, "fopen(r+) on existing file shall not update MAC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.RB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_RBP, "check_interfaces_file_fopen_existing_RBP", "Yes", POSIX_c181, MANDATORY, "fopen(rb+) on existing file shall not update MAC");
    runtest(env, "INTERFACES.FILE.FOPEN.EXISTING.R+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_existing_RPB, "check_interfaces_file_fopen_existing_RPB", "Yes", POSIX_c181, MANDATORY, "fopen(r+b) on existing file shall not update MAC");
    
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.R", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_R, "check_interfaces_file_fopen_fread_existing_R", "Yes", POSIX_c181, MANDATORY, "fopen(r)+fread on existing file shall update A");
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.RB", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_RB, "check_interfaces_file_fopen_fread_existing_RB", "Yes", POSIX_c181, MANDATORY, "fopen(rb)+fread on existing file shall update A");
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.R+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_RP, "check_interfaces_file_fopen_fread_existing_RP", "Yes", POSIX_c181, MANDATORY, "fopen(r+)+fread on existing file shall update A");
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.RB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_RBP, "check_interfaces_file_fopen_fread_existing_RBP", "Yes", POSIX_c181, MANDATORY, "fopen(rb+)+fread on existing file shall update A");
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.R+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_RPB, "check_interfaces_file_fopen_fread_existing_RPB", "Yes", POSIX_c181, MANDATORY, "fopen(r+b)+fread on existing file shall update A");
    
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.W+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_WP, "check_interfaces_file_fopen_fread_existing_WP", "Yes", POSIX_c181, MANDATORY, "fopen(w+)+fread (nmemb>0) on existing file shall update A");
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.WB+", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_WBP, "check_interfaces_file_fopen_fread_existing_WBP", "Yes", POSIX_c181, MANDATORY, "fopen(wb+)+fread (nmemb>0) on existing file shall update A");
    runtest(env, "INTERFACES.FILE.FOPEN_FREAD.EXISTING.W+B", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_fopen_fread_existing_WPB, "check_interfaces_file_fopen_fread_existing_WPB", "Yes", POSIX_c181, MANDATORY, "fopen(w+b)+fread (nmemb>0) on existing file shall update A");
}

void group_check_interfaces_file_w(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.FILE.W.FPRINTF_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fprintf_fflush_imm, "check_interfaces_file_w_fprintf_fflush_imm", "No", "", MANDATORY, "fprintf + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPRINTF_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fprintf_fflush, "check_interfaces_file_w_fprintf_fflush", "Yes", POSIX_c181, MANDATORY, "fprintf + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FPRINTF_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fprintf_fclose, "check_interfaces_file_w_fprintf_fclose", "Yes", POSIX_c181, MANDATORY, "fprintf + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FPRINTF_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fprintf_exit, "check_interfaces_file_w_fprintf_exit", "Yes", POSIX_c181, MANDATORY, "fprintf + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPRINTF_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fprintf_abort, "check_interfaces_file_w_fprintf_abort", "Yes", POSIX_c181, MANDATORY, "fprintf + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.PRINTF_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_printf_fflush, "check_interfaces_file_w_printf_fflush", "Yes", POSIX_c181, MANDATORY, "printf + fflush (stdout) shall mark MC for update");
//     runtest(env, "INTERFACES.FILE.W.PRINTF_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_printf_exit, "check_interfaces_file_w_printf_exit", "Yes", POSIX_c181, MANDATORY, "printf + exit (stdout) shall update MC");
    runtest(env, "INTERFACES.FILE.W.PRINTF_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_printf_abort, "check_interfaces_file_w_printf_abort", "Yes", POSIX_c181, MANDATORY, "printf + abort (stdout) shall mark MC for update");
    
    runtest(env, "INTERFACES.FILE.W.DPRINTF", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_dprintf, "check_interfaces_file_w_dprintf", "Yes", POSIX_c181, MANDATORY, "dprintf shall mark MC for update");
    
    runtest(env, "INTERFACES.FILE.W.FPUTC_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputc_fflush_imm, "check_interfaces_file_w_fputc_fflush_imm", "No", "", MANDATORY, "fputc + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTC_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputc_fflush, "check_interfaces_file_w_fputc_fflush", "Yes", POSIX_c181, MANDATORY, "fputc + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FPUTC_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputc_fclose, "check_interfaces_file_w_fputc_fclose", "Yes", POSIX_c181, MANDATORY, "fputc + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FPUTC_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputc_exit, "check_interfaces_file_w_fputc_exit", "Yes", POSIX_c181, MANDATORY, "fputc + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTC_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputc_abort, "check_interfaces_file_w_fputc_abort", "Yes", POSIX_c181, MANDATORY, "fputc + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.FPUTS_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputs_fflush_imm, "check_interfaces_file_w_fputs_fflush_imm", "No", "", MANDATORY, "fputs + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTS_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputs_fflush, "check_interfaces_file_w_fputs_fflush", "Yes", POSIX_c181, MANDATORY, "fputs + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FPUTS_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputs_fclose, "check_interfaces_file_w_fputs_fclose", "Yes", POSIX_c181, MANDATORY, "fputs + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FPUTS_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputs_exit, "check_interfaces_file_w_fputs_exit", "Yes", POSIX_c181, MANDATORY, "fputs + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTS_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputs_abort, "check_interfaces_file_w_fputs_abort", "Yes", POSIX_c181, MANDATORY, "fputs + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.FPUTWC_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputwc_fflush_imm, "check_interfaces_file_w_fputwc_fflush_imm", "No", "", MANDATORY, "fputwc + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTWC_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputwc_fflush, "check_interfaces_file_w_fputwc_fflush", "Yes", POSIX_c181, MANDATORY, "fputwc + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FPUTWC_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputwc_fclose, "check_interfaces_file_w_fputwc_fclose", "Yes", POSIX_c181, MANDATORY, "fputwc + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FPUTWC_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputwc_exit, "check_interfaces_file_w_fputwc_exit", "Yes", POSIX_c181, MANDATORY, "fputwc + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTWC_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputwc_abort, "check_interfaces_file_w_fputwc_abort", "Yes", POSIX_c181, MANDATORY, "fputwc + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.FPUTWS_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputws_fflush_imm, "check_interfaces_file_w_fputws_fflush_imm", "No", "", MANDATORY, "fputws + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTWS_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputws_fflush, "check_interfaces_file_w_fputws_fflush", "Yes", POSIX_c181, MANDATORY, "fputws + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FPUTWS_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputws_fclose, "check_interfaces_file_w_fputws_fclose", "Yes", POSIX_c181, MANDATORY, "fputws + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FPUTWS_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputws_exit, "check_interfaces_file_w_fputws_exit", "Yes", POSIX_c181, MANDATORY, "fputws + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FPUTWS_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fputws_abort, "check_interfaces_file_w_fputws_abort", "Yes", POSIX_c181, MANDATORY, "fputws + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.FWPRINTF_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwprintf_fflush_imm, "check_interfaces_file_w_fwprintf_fflush_imm", "No", "", MANDATORY, "fwprintf + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FWPRINTF_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwprintf_fflush, "check_interfaces_file_w_fwprintf_fflush", "Yes", POSIX_c181, MANDATORY, "fwprintf + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FWPRINTF_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwprintf_fclose, "check_interfaces_file_w_fwprintf_fclose", "Yes", POSIX_c181, MANDATORY, "fwprintf + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FWPRINTF_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwprintf_exit, "check_interfaces_file_w_fwprintf_exit", "Yes", POSIX_c181, MANDATORY, "fwprintf + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FWPRINTF_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwprintf_abort, "check_interfaces_file_w_fwprintf_abort", "Yes", POSIX_c181, MANDATORY, "fwprintf + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.WPRINTF_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_wprintf_fflush, "check_interfaces_file_w_wprintf_fflush", "Yes", POSIX_c181, MANDATORY, "wprintf + fflush (stdout) shall update MC");
//     runtest(env, "INTERFACES.FILE.W.WPRINTF_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_wprintf_exit, "check_interfaces_file_w_wprintf_exit", "Yes", POSIX_c181, MANDATORY, "wprintf + exit (stdout) shall update MC");
    runtest(env, "INTERFACES.FILE.W.WPRINTF_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_wprintf_abort, "check_interfaces_file_w_wprintf_abort", "Yes", POSIX_c181, MANDATORY, "wprintf + abort (stdout) shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.FWRITE_FFLUSH.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwrite_fflush_imm, "check_interfaces_file_w_fwrite_fflush_imm", "No", "", MANDATORY, "fwrite + fflush shall update MC");
    runtest(env, "INTERFACES.FILE.W.FWRITE_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwrite_fflush, "check_interfaces_file_w_fwrite_fflush", "Yes", POSIX_c181, MANDATORY, "fwrite + fflush shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.FWRITE_FCLOSE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwrite_fclose, "check_interfaces_file_w_fwrite_fclose", "Yes", POSIX_c181, MANDATORY, "fwrite + fclose shall update MC");
//     runtest(env, "INTERFACES.FILE.W.FWRITE_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwrite_exit, "check_interfaces_file_w_fwrite_exit", "Yes", POSIX_c181, MANDATORY, "fwrite + exit shall update MC");
    runtest(env, "INTERFACES.FILE.W.FWRITE_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_fwrite_abort, "check_interfaces_file_w_fwrite_abort", "Yes", POSIX_c181, MANDATORY, "fwrite + abort shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.PUTS_FFLUSH", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_puts_fflush, "check_interfaces_file_w_puts_fflush", "Yes", POSIX_c181, MANDATORY, "puts + fflush (stdout) shall update MC");
//     runtest(env, "INTERFACES.FILE.W.PUTS_EXIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_puts_exit, "check_interfaces_file_w_puts_exit", "Yes", POSIX_c181, MANDATORY, "puts + exit (stdout) shall update MC");
    runtest(env, "INTERFACES.FILE.W.PUTS_ABORT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_puts_abort, "check_interfaces_file_w_puts_abort", "Yes", POSIX_c181, MANDATORY, "puts + abort (stdout) shall update MC");
    
    runtest(env, "INTERFACES.FILE.W.FTRUNCATE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_ftruncate, "check_interfaces_file_w_ftruncate", "Yes", POSIX_c181, MANDATORY, "ftruncate on regular file shall mark MC for update");
    
    runtest(env, "INTERFACES.FILE.W.WRITE.IMM", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_write_imm, "check_interfaces_file_w_write_imm", "No", "", MANDATORY, "With nbyte greater than 0, write shall update MC");
    runtest(env, "INTERFACES.FILE.W.WRITE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_write, "check_interfaces_file_w_write", "Yes", POSIX_c181, MANDATORY, "With nbyte greater than 0, write shall mark MC for update");
    runtest(env, "INTERFACES.FILE.W.WRITE.ZERO", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_w_write_zero, "check_interfaces_file_w_write_zero", "Yes", "", MANDATORY, "With nbyte 0, write shall not update MAC");
}

void group_check_interfaces_file_r(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "INTERFACES.FILE.R.FREAD", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fread, "check_interfaces_file_r_fread", "Yes", POSIX_c181, MANDATORY, "fread returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.FREAD.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fread_ungetc, "check_interfaces_file_r_fread_ungetc", "Yes", POSIX_c181, MAY, "fread returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.FREAD.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fread_ungetc_both, "check_interfaces_file_r_fread_ungetc_both", "Yes", POSIX_c181, MANDATORY, "fread returning both data supplied and not supplied by ungetc shall mark A for update");
    
    runtest(env, "INTERFACES.FILE.R.FGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgetc, "check_interfaces_file_r_fgetc", "Yes", POSIX_c181, MANDATORY, "fgetc returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.FGETC.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgetc_ungetc, "check_interfaces_file_r_fgetc_ungetc", "Yes", POSIX_c181, MAY, "fgetc returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.FGETC.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgetc_ungetc_both, "check_interfaces_file_r_fgetc_ungetc_both", "Yes", POSIX_c181, MANDATORY, "fgetc returning both data supplied and not supplied by ungetc shall mark A for update");
    
    runtest(env, "INTERFACES.FILE.R.GETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getc, "check_interfaces_file_r_getc", "Yes", POSIX_c181, MANDATORY, "getc returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.GETC.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getc_ungetc, "check_interfaces_file_r_getc_ungetc", "Yes", "", MAY, "getc returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.GETC.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getc_ungetc_both, "check_interfaces_file_r_getc_ungetc_both", "Yes", POSIX_c181, MANDATORY, "getc returning both data supplied and not supplied by ungetc shall mark A for update");
    
    runtest(env, "INTERFACES.FILE.R.FGETS.IMM", 10, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgets_imm, "check_interfaces_file_r_fgets_imm", "No", "", MANDATORY, "fgets returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.FGETS", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgets, "check_interfaces_file_r_fgets", "Yes", POSIX_c181, MANDATORY, "fgets returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.FGETS.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgets_ungetc, "check_interfaces_file_r_fgets_ungetc", "Yes", POSIX_c181, MAY, "fgets returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.FGETS.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fgets_ungetc_both, "check_interfaces_file_r_fgets_ungetc_both", "Yes", POSIX_c181, MANDATORY, "fgets returning both data supplied and not supplied by ungetc shall mark A for update");

#ifndef __OpenBSD__
#ifndef __FreeBSD__
    if (OPTION_TEST_INPUT == 1){
        runtest(env, "INTERFACES.FILE.R.GETS", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_gets, "check_interfaces_file_r_gets", "Yes", POSIX_c181, MANDATORY, "gets (stdin) returning data not supplied by ungetc shall mark A for update");
        runtest(env, "INTERFACES.FILE.R.GETS.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_gets_ungetc, "check_interfaces_file_r_gets_ungetc", "Yes", POSIX_c181, MAY, "gets (stdin) returning data supplied by ungetc may mark A for update");
        runtest(env, "INTERFACES.FILE.R.GETS.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_gets_ungetc_both, "check_interfaces_file_r_gets_ungetc_both", "Yes", POSIX_c181, MANDATORY, "gets (stdin) returning both data supplied and not supplied by ungetc shall mark A for update");
    }
#endif
#endif

    if (OPTION_TEST_INPUT == 1){
        runtest(env, "INTERFACES.FILE.R.GETCHAR", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getchar, "check_interfaces_file_r_getchar", "Yes", POSIX_c181, MANDATORY, "getchar (stdin) returning data not supplied by ungetc shall mark A for update");
        runtest(env, "INTERFACES.FILE.R.GETCHAR.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getchar_ungetc, "check_interfaces_file_r_getchar_ungetc", "Yes", POSIX_c181, MAY, "getchar (stdin) returning data supplied by ungetc may mark A for update");
        runtest(env, "INTERFACES.FILE.R.GETCHAR.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getchar_ungetc_both, "check_interfaces_file_r_getchar_ungetc_both", "Yes", POSIX_c181, MANDATORY, "getchar (stdin) returning both data supplied and not supplied by ungetc shall mark A for update");
    }
    
    runtest(env, "INTERFACES.FILE.R.GETDELIM", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getdelim, "check_interfaces_file_r_getdelim", "Yes", POSIX_c181, MANDATORY, "getdelim returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.GETDELIM.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getdelim_ungetc, "check_interfaces_file_r_getdelim_ungetc", "Yes", POSIX_c181, MAY, "getdelim returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.GETDELIM.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getdelim_ungetc_both, "check_interfaces_file_r_getdelim_ungetc_both", "Yes", POSIX_c181, MANDATORY, "getdelim returning both data supplied and not supplied by ungetc shall mark A for update");
   
    runtest(env, "INTERFACES.FILE.R.GETLINE", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getline, "check_interfaces_file_r_getline", "Yes", POSIX_c181, MANDATORY, "getline returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.GETLINE.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getline_ungetc, "check_interfaces_file_r_getline_ungetc", "Yes", POSIX_c181, MAY, "getline returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.GETLINE.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_getline_ungetc_both, "check_interfaces_file_r_getline_ungetc_both", "Yes", POSIX_c181, MANDATORY, "getline returning both data supplied and not supplied by ungetc shall mark A for update");

    runtest(env, "INTERFACES.FILE.R.FSCANF", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fscanf, "check_interfaces_file_r_fscanf", "Yes", POSIX_c181, MANDATORY, "fscanf returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.FSCANF.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fscanf_ungetc, "check_interfaces_file_r_fscanf_ungetc", "Yes", POSIX_c181, MAY, "fscanf returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.FSCANF.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fscanf_ungetc_both, "check_interfaces_file_r_fscanf_ungetc_both", "Yes", POSIX_c181, MANDATORY, "fscanf returning both data supplied and not supplied by ungetc shall mark A for update");
 
    if (OPTION_TEST_INPUT == 1){
        runtest(env, "INTERFACES.FILE.R.SCANF", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_scanf, "check_interfaces_file_r_scanf", "Yes", POSIX_c181, MANDATORY, "scanf (stdin) returning data not supplied by ungetc shall mark A for update");
        runtest(env, "INTERFACES.FILE.R.SCANF.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_scanf_ungetc, "check_interfaces_file_r_scanf_ungetc", "Yes", POSIX_c181, MAY, "scanf (stdin) returning data supplied by ungetc may mark A for update");
        runtest(env, "INTERFACES.FILE.R.SCANF.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_scanf_ungetc_both, "check_interfaces_file_r_scanf_ungetc_both", "Yes", POSIX_c181, MANDATORY, "scanf (stdin) returning both data supplied and not supplied by ungetc shall mark A for update");
    }
 
    runtest(env, "INTERFACES.FILE.R.FWSCANF", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fwscanf, "check_interfaces_file_r_fwscanf", "Yes", POSIX_c181, MANDATORY, "fwscanf returning data not supplied by ungetc shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.FWSCANF.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fwscanf_ungetc, "check_interfaces_file_r_fwscanf_ungetc", "Yes", POSIX_c181, MAY, "fwscanf returning data supplied by ungetc may mark A for update");
    runtest(env, "INTERFACES.FILE.R.FWSCANF.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_fwscanf_ungetc_both, "check_interfaces_file_r_fwscanf_ungetc_both", "Yes", POSIX_c181, MANDATORY, "fwscanf returning both data supplied and not supplied by ungetc shall mark A for update");

    if (OPTION_TEST_INPUT == 1){
        // WARNING: it messes with stdin, I could not find a solution...
        runtest(env, "INTERFACES.FILE.R.WSCANF", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_wscanf, "check_interfaces_file_r_wscanf", "Yes", POSIX_c181, MANDATORY, "wscanf returning data not supplied by ungetc shall mark A for update");
        runtest(env, "INTERFACES.FILE.R.WSCANF.UNGETC", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_wscanf_ungetc, "check_interfaces_file_r_wscanf_ungetc", "Yes", POSIX_c181, MAY, "wscanf returning data supplied by ungetc may mark A for update");
        runtest(env, "INTERFACES.FILE.R.WSCANF.UNGETC.BOTH", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_wscanf_ungetc_both, "check_interfaces_file_r_wscanf_ungetc_both", "Yes", POSIX_c181, MANDATORY, "wscanf returning both data supplied and not supplied by ungetc shall mark A for update");
    }

    runtest(env, "INTERFACES.FILE.R.READ.IMM", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_read_imm, "check_interfaces_file_r_read_imm", "No", "", MANDATORY, "With nbyte greater than 0, read shall update A");
    runtest(env, "INTERFACES.FILE.R.READ", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_read, "check_interfaces_file_r_read", "Yes", POSIX_c181, MANDATORY, "With nbyte greater than 0, read shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.READ.ZERO", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_read_zero, "check_interfaces_file_r_read_zero", "Yes", "", MANDATORY, "With nbyte equal to 0, read shall not update MAC");
    runtest(env, "INTERFACES.FILE.R.PREAD", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_pread, "check_interfaces_file_r_pread", "Yes", POSIX_c181, MANDATORY, "With nbyte greater than 0, pread shall mark A for update");
    runtest(env, "INTERFACES.FILE.R.PREAD.ZERO", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_r_pread_zero, "check_interfaces_file_r_pread_zero", "Yes", "", MANDATORY, "With nbyte equal to 0, pread shall not mark MAC for update");
}

void group_check_interfaces_dir(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;

    runtest(env, "INTERFACES.DIR.READDIR", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_dir_readdir, "check_interfaces_dir_readdir", "Yes", "", MANDATORY, "readdir on a directory shall update A");
    runtest(env, "INTERFACES.DIR.READDIR.FILES", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_dir_readdir_files, "check_interfaces_dir_readdir_files", "Yes", "", MANDATORY, "readdir on a directory shall not update MAC of files in the directory");
    runtest(env, "INTERFACES.DIR.READDIR_R", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_dir_readdir_r, "check_interfaces_dir_readdir_r", "Yes", "", MANDATORY, "readdir_r on a directory shall update A");
    runtest(env, "INTERFACES.DIR.READDIR_R.FILES", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_dir_readdir_r_files, "check_interfaces_dir_readdir_r_files", "Yes", "", MANDATORY, "readdir_r on a directory shall not update MAC of files in the directory");
}

void group_check_interfaces_file_ln(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;

    runtest(env, "INTERFACES.FILE.LN.LINK", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_ln_link, "check_interfaces_file_ln_link", "Yes", POSIX_c181, MANDATORY, "link shall mark for update C and MC of the directory containing the new entry");
    runtest(env, "INTERFACES.FILE.LN.LINKAT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_ln_linkat, "check_interfaces_file_ln_linkat", "Yes", POSIX_c181, MANDATORY, "linkat shall mark for update C and MC of the directory containing the new entry");
    runtest(env, "INTERFACES.FILE.LN.SYMLINK", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_ln_symlink, "check_interfaces_file_ln_symlink", "Yes", POSIX_c181, MANDATORY, "symlink shall mark for update C and MC of the directory containing the new entry");
    runtest(env, "INTERFACES.FILE.LN.SYMLINKAT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_ln_symlinkat, "check_interfaces_file_ln_symlinkat", "Yes", POSIX_c181, MANDATORY, "symlinkat shall mark for update C and MC of the directory containing the new entry");
    runtest(env, "INTERFACES.FILE.LN.READLINK", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_ln_readlink, "check_interfaces_file_ln_readlink", "Yes", POSIX_c181, MANDATORY, "readlink shall mark for update A");
    runtest(env, "INTERFACES.FILE.LN.READLINKAT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_ln_readlinkat, "check_interfaces_file_ln_readlinkat", "Yes", POSIX_c181, MANDATORY, "readlinkat shall mark for update A");
}

void group_check_interfaces_file_new(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;

    runtest(env, "INTERFACES.FILE.NEW.MKDTEMP.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdtemp_new, "check_interfaces_file_new_mkdtemp_new", "Yes", POSIX_c181, MANDATORY, "mkdtemp shall create new directory with updated MAC");
    runtest(env, "INTERFACES.FILE.NEW.MKDTEMP.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdtemp_mac, "check_interfaces_file_new_mkdtemp_mac", "Yes", "", MANDATORY, "mkdtemp shall create new directory with MAC equal");
    runtest(env, "INTERFACES.FILE.NEW.MKDTEMP.MAC_1S", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdtemp_mac_1s, "check_interfaces_file_new_mkdtemp_mac_1s", "Yes", "", MANDATORY, "mkdtemp shall create new directory with MAC equal after 1s");
    runtest(env, "INTERFACES.FILE.NEW.MKDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdir, "check_interfaces_file_new_mkdir", "Yes", POSIX_c181, MANDATORY, "mkdir shall update MAC of the directory and MC of the parent of the new directory");
    runtest(env, "INTERFACES.FILE.NEW.MKDIR.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdir_mac, "check_interfaces_file_new_mkdir_mac", "Yes", "", MANDATORY, "mkdir shall create new directory with MAC equal");
    runtest(env, "INTERFACES.FILE.NEW.MKDIR.MAC_1S", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdir_mac_1s, "check_interfaces_file_new_mkdir_mac_1s", "Yes", "", MANDATORY, "mkdir shall create new directory with MAC equal 1s after creation");
    runtest(env, "INTERFACES.FILE.NEW.MKDIRAT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdirat, "check_interfaces_file_new_mkdirat", "Yes", POSIX_c181, MANDATORY, "mkdirat shall update MAC of the directory and MC of the parent of the new directory");
    runtest(env, "INTERFACES.FILE.NEW.MKDIRAT.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdirat_mac, "check_interfaces_file_new_mkdirat_mac", "Yes", "", MANDATORY, "mkdirat shall create new directory with MAC equal");
    runtest(env, "INTERFACES.FILE.NEW.MKDIRAT.MAC_1S", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkdirat_mac_1s, "check_interfaces_file_new_mkdirat_mac_1s", "Yes", "", MANDATORY, "mkdirat shall create new directory with MAC equal 1s after creation");
    runtest(env, "INTERFACES.FILE.NEW.MKFIFO", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkfifo, "check_interfaces_file_new_mkfifo", "Yes", POSIX_c181, MANDATORY, "mkfifo shall update MAC of the directory and MC of the parent of the new directory");
    runtest(env, "INTERFACES.FILE.NEW.MKFIFO.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkfifo_mac, "check_interfaces_file_new_mkfifo_mac", "Yes", "", MANDATORY, "mkfifo shall create new directory with MAC equal");
    runtest(env, "INTERFACES.FILE.NEW.MKFIFO.MAC_1S", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkfifo_mac_1s, "check_interfaces_file_new_mkfifo_mac_1s", "Yes", "", MANDATORY, "mkfifo shall create new directory with MAC equal 1s after creation");
    runtest(env, "INTERFACES.FILE.NEW.MKFIFOAT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkfifoat, "check_interfaces_file_new_mkfifoat", "Yes", POSIX_c181, MANDATORY, "mkfifoat shall update MAC of the directory and MC of the parent of the new directory");
    runtest(env, "INTERFACES.FILE.NEW.MKFIFOAT.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkfifoat_mac, "check_interfaces_file_new_mkfifoat_mac", "Yes", "", MANDATORY, "mkfifoat shall create new directory with MAC equal");
    runtest(env, "INTERFACES.FILE.NEW.MKFIFOAT.MAC_1S", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkfifoat_mac_1s, "check_interfaces_file_new_mkfifoat_mac_1s", "Yes", "", MANDATORY, "mkfifoat shall create new directory with MAC equal 1s after creation");
    runtest(env, "INTERFACES.FILE.NEW.MKPIPE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_new_mkpipe, "check_interfaces_file_new_mkpipe", "Yes", POSIX_c181, MANDATORY, "pipe shall update MAC of the pipe");
}

void group_check_interfaces_file_mv(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;

    runtest(env, "INTERFACES.FILE.MV.RENAME.FILE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_rename_file, "check_interfaces_file_mv_rename_file", "No", "", MANDATORY, "rename on a file shall update C");
    runtest(env, "INTERFACES.FILE.MV.RENAME.FILE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_rename_file_ma, "check_interfaces_file_mv_rename_file_ma", "No", "", MANDATORY, "rename on a file shall keep MA");
    runtest(env, "INTERFACES.FILE.MV.RENAME.FILE.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_rename_file_dir, "check_interfaces_file_mv_rename_file_dir", "Yes", POSIX_c181, MANDATORY, "rename on a file shall update MC of parent directory");
    runtest(env, "INTERFACES.FILE.MV.RENAME.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_rename_dir, "check_interfaces_file_mv_rename_dir", "No", "", MANDATORY, "rename on a dir shall update C");
    runtest(env, "INTERFACES.FILE.MV.RENAME.DIR.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_rename_dir_ma, "check_interfaces_file_mv_rename_dir_ma", "No", "", MANDATORY, "rename on a dir shall keep MA");
    runtest(env, "INTERFACES.FILE.MV.RENAME.DIR.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_rename_dir_dir, "check_interfaces_file_mv_rename_dir_dir", "Yes", POSIX_c181, MANDATORY, "rename on a dir shall update MC of parent directory");
    
    runtest(env, "INTERFACES.FILE.MV.RENAMEAT.FILE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_renameat_file, "check_interfaces_file_mv_renameat_file", "No", "", MANDATORY, "renameat on a file shall update C");
    runtest(env, "INTERFACES.FILE.MV.RENAMEAT.FILE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_renameat_file_ma, "check_interfaces_file_mv_renameat_file_ma", "No", "", MANDATORY, "renameat on a file shall keep MA");
    runtest(env, "INTERFACES.FILE.MV.RENAMEAT.FILE.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_renameat_file_dir, "check_interfaces_file_mv_renameat_file_dir", "Yes", POSIX_c181, MANDATORY, "renameat on a file shall update MC of parent directory");
    runtest(env, "INTERFACES.FILE.MV.RENAMEAT.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_renameat_dir, "check_interfaces_file_mv_renameat_dir", "No", "", MANDATORY, "renameat on a dir shall update C");
    runtest(env, "INTERFACES.FILE.MV.RENAMEAT.DIR.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_renameat_dir_ma, "check_interfaces_file_mv_renameat_dir_ma", "No", "", MANDATORY, "renameat on a dir shall keep MA");
    runtest(env, "INTERFACES.FILE.MV.RENAMEAT.DIR.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_mv_renameat_dir_dir, "check_interfaces_file_mv_renameat_dir_dir", "Yes", POSIX_c181, MANDATORY, "renameat on a dir shall update MC of parent directory");
}

void group_check_interfaces_file_rm(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;

    runtest(env, "INTERFACES.FILE.RM.UNLINK.LAST.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_unlink_last_dir, "check_interfaces_file_rm_unlink_last_dir", "Yes", POSIX_c181, MANDATORY, "unlink when file’s link count is 0 shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.UNLINK.NOTLAST.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_unlink_notlast_dir, "check_interfaces_file_rm_unlink_notlast_dir", "Yes", POSIX_c181, MANDATORY, "unlink when file’s link count is not 0 shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.UNLINK.NOTLAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_unlink_notlast, "check_interfaces_file_rm_unlink_notlast", "Yes", POSIX_c181, MANDATORY, "unlink when file’s link count is not 0 shall update C");
    
    runtest(env, "INTERFACES.FILE.RM.UNLINKAT.LAST.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_unlinkat_last_dir, "check_interfaces_file_rm_unlinkat_last_dir", "Yes", POSIX_c181, MANDATORY, "unlinkat when file’s link count is 0 shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.UNLINKAT.NOTLAST.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_unlinkat_notlast_dir, "check_interfaces_file_rm_unlinkat_notlast_dir", "Yes", POSIX_c181, MANDATORY, "unlinkat when file’s link count is not 0 shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.UNLINKAT.NOTLAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_unlinkat_notlast, "check_interfaces_file_rm_unlinkat_notlast", "Yes", POSIX_c181, MANDATORY, "unlinkat when file’s link count is not 0 shall update C");
    
    runtest(env, "INTERFACES.FILE.RM.REMOVE.DIR.EMPTY.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_remove_dir_empty_parentdir, "check_interfaces_file_rm_remove_dir_empty_parentdir", "Yes", POSIX_c181, MANDATORY, "remove on an empty dir shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.REMOVE.DIR.NOTEMPTY.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_remove_dir_notempty_parentdir, "check_interfaces_file_rm_remove_dir_notempty_parentdir", "Yes", POSIX_c181, MANDATORY, "remove on a not empty dir shall not update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.REMOVE.DIR.NOTEMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_remove_dir_notempty, "check_interfaces_file_rm_remove_dir_notempty", "Yes", POSIX_c181, MANDATORY, "remove on a not empty dir shall update C");
    
    runtest(env, "INTERFACES.FILE.RM.REMOVE.FILE.LAST.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_remove_file_last_parentdir, "check_interfaces_file_rm_remove_file_last_parentdir", "Yes", POSIX_c181, MANDATORY, "remove on a file who’s link count is 0 shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.REMOVE.FILE.NOLAST.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_remove_file_notlast_parentdir, "check_interfaces_file_rm_remove_file_notlast_parentdir", "Yes", POSIX_c181, MANDATORY, "remove on a file who’s link count is not 0 shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.REMOVE.FILE.NOLAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_remove_file_notlast, "check_interfaces_file_rm_remove_file_notlast", "Yes", POSIX_c181, MANDATORY, "remove on a file who’s link count is not 0 shall update the file C");
    
    runtest(env, "INTERFACES.FILE.RM.RMDIR.EMPTY.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_rmdir_empty_parentdir, "check_interfaces_file_rm_rmdir_empty_parentdir", "Yes", POSIX_c181, MANDATORY, "rmdir on an empty dir shall update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.RMDIR.NOTEMPTY.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_rmdir_notempty_parentdir, "check_interfaces_file_rm_rmdir_notempty_parentdir", "Yes", "", MANDATORY, "rmdir on a not empty dir shall not update parent directory MC");
    runtest(env, "INTERFACES.FILE.RM.RM.DIR.NOTEMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_file_rm_rmdir_notempty, "check_interfaces_file_rm_rmdir_notempty", "Yes", "", MANDATORY, "rmdir on a not empty dir shall not update C");
}

void group_check_utilities_attr(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
                                           
    // TODO
    runtest(env, "UTILITIES.ATTR.CHMOD.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_attr_chmod_new, "check_utilities_attr_chmod_new", "Yes", POSIX_c181, MANDATORY, "chmod with different mode shall update C");
    runtest(env, "UTILITIES.ATTR.CHMOD.SAME", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_attr_chmod_same, "check_utilities_attr_chmod_same", "Yes", POSIX_c181, MANDATORY, "chmod with same mode shall update C");
}

void group_check_utilities_cp(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "UTILITIES.CP.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_new, "check_utilities_cp_new", "Yes", POSIX_c181, MANDATORY, "cp with destination not existing shall update MAC");
    runtest(env, "UTILITIES.CP.NEW.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_new_mac, "check_utilities_cp_new_mac", "No", "", MANDATORY, "cp with destination not existing shall set MAC equal");
    runtest(env, "UTILITIES.CP.NEW.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_new_dir, "check_utilities_cp_new_dir", "No", "", MANDATORY, "cp with destination not existing shall update MC of dest’s parent dir and not update MAC of src’s parent dir");
    runtest(env, "UTILITIES.CP.NEW.DIR.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_new_dir_mc, "check_utilities_cp_new_dir_mc", "No", "", MANDATORY, "cp with destination not existing shall set MC of dest’s parent dir equal");
     
    runtest(env, "UTILITIES.CP.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_existing, "check_utilities_cp_existing", "Yes", POSIX_c181, MANDATORY, "cp with destination existing shall update MC");
    runtest(env, "UTILITIES.CP.EXISTING.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_existing_mc, "check_utilities_cp_existing_mc", "No", "", MANDATORY, "cp with destination existing shall set MC equal");
    runtest(env, "UTILITIES.CP.EXISTING.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_cp_existing_dir, "check_utilities_cp_existing_dir", "No", "", MANDATORY, "cp with destination existing shall not update MAC of dest’s parent dir and not update MAC of src’s parent dir");
}

void group_check_utilities_new(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "UTILITIES.NEW.TOUCH.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_new, "check_utilities_new_touch_new", "Yes", POSIX_c181, MANDATORY, "touch on non existing file shall update MAC");
    runtest(env, "UTILITIES.NEW.TOUCH.NEW.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_new_mac, "check_utilities_new_touch_new_mac", "No", "", MANDATORY, "touch on non existing file shall set MAC equal");
    runtest(env, "UTILITIES.NEW.TOUCH.NEW.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_new_dir, "check_utilities_new_touch_new_dir", "Yes", POSIX_c181, MANDATORY, "touch on non existing file shall update MC of parent directory");
    runtest(env, "UTILITIES.NEW.TOUCH.NEW.DIR.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_new_dir_mc, "check_utilities_new_touch_new_dir_mc", "No", "", MANDATORY, "touch on non existing file shall set MC of parent directory equal");
    runtest(env, "UTILITIES.NEW.TOUCH.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_existing, "check_utilities_new_touch_existing", "Yes", POSIX_c181, MANDATORY, "touch on existing file shall update MAC");
    runtest(env, "UTILITIES.NEW.TOUCH.EXISTING.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_existing_mac, "check_utilities_new_touch_existing_mac", "No", "", MANDATORY, "touch on existing file shall set MAC equal");
    runtest(env, "UTILITIES.NEW.TOUCH.EXISTING.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_touch_existing_dir, "check_utilities_new_touch_existing_dir", "No", "", MANDATORY, "touch on existing file shall not update MAC of parent directory");
    
    runtest(env, "UTILITIES.NEW.MKDIR.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_mkdir_new, "check_utilities_new_mkdir_new", "Yes", POSIX_c181, MANDATORY, "mkdir on a non existing dir shall update MAC of the directory and MC of the parent of the new directory");
    runtest(env, "UTILITIES.NEW.MKDIR.NEW.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_mkdir_new_mac, "check_utilities_new_mkdir_new_mac", "No", "", MANDATORY, "mkdir on a non existing dir shall create new directory with MAC equal");
    runtest(env, "UTILITIES.NEW.MKDIR.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_mkdir_existing, "check_utilities_new_mkdir_existing", "No", "", MANDATORY, "mkdir on an existing dir shall not update MAC of the directory nor MAC of the parent directory");
    
    runtest(env, "UTILITIES.NEW.MKFIFO.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_mkfifo_new, "check_utilities_new_mkfifo_new", "Yes", POSIX_c181, MANDATORY, "mkfifo on a non existing mkfifo shall update MAC of the directory and MC of the parent of the new directory");
    runtest(env, "UTILITIES.NEW.MKFIFO.NEW.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_mkfifo_new_mac, "check_utilities_new_mkfifo_new_mac", "No", "", MANDATORY, "mkfifo on a non existing mkfifo shall create new directory with MAC equal");
    runtest(env, "UTILITIES.NEW.MKFIFO.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_new_mkfifo_existing, "check_utilities_new_mkfifo_existing", "No", "", MANDATORY, "mkfifo on an existing mkfifo shall not update MAC of the directory nor MAC of the parent directory");
}
    
void group_check_utilities_mv(testenv_struct* env){    
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "UTILITIES.MV.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_mv_new, "check_utilities_mv_new", "Yes", POSIX_c181, MANDATORY, "mv when destination is a new file shall update C, MC of src’s parent directory and MC of dest’s parent directory");
    runtest(env, "UTILITIES.MV.NEW.EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_mv_new_eq, "check_utilities_mv_new_eq", "Yes", "", MANDATORY, "mv when destination is a new file shall update the 5 MC with the same value");
    runtest(env, "UTILITIES.MV.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_mv_existing, "check_utilities_mv_existing", "Yes", POSIX_c181, MANDATORY, "mv when destination is an existing file shall update C, MC of src’s parent directory and MC of dest’s parent directory");
    runtest(env, "UTILITIES.MV.EXISTING.EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_mv_existing_eq, "check_utilities_mv_existing_eq", "Yes", "", MANDATORY, "mv when destination is an existing file shall update the 5 MC with the same value");
}

void group_check_utilities_rm(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "UTILITIES.RM.RM.DIR.EMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rm_dir_empty, "check_utilities_rm_rm_dir_empty", "Yes", POSIX_c181, MANDATORY, "rm on an empty dir shall not update MAC of the directory nor of its parent dir");
    runtest(env, "UTILITIES.RM.R.RM.DIR.EMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rm_r_dir_empty, "check_utilities_rm_rm_r_dir_empty", "Yes", POSIX_c181, MANDATORY, "rm -r on an empty dir shall update parent directory MC");
    runtest(env, "UTILITIES.RM.R.RM.DIR.NOTEMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rm_r_dir_notempty, "check_utilities_rm_rm_r_dir_notempty", "Yes", POSIX_c181, MANDATORY, "rm -r on a not empty dir shall update parent directory MC");
    runtest(env, "UTILITIES.RM.RM.FILE.LAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rm_file_last, "check_utilities_rm_rm_file_last", "Yes", POSIX_c181, MANDATORY, "rm when file’s link count is 0 shall update parent directory MC");
    runtest(env, "UTILITIES.RM.RM.FILE.NOTLAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rm_file_notlast, "check_utilities_rm_rm_file_notlast", "Yes", POSIX_c181, MANDATORY, "rm when file’s link count is not 0 shall update C");
    runtest(env, "UTILITIES.RM.RM.FILE.NOTLAST.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rm_file_notlast_dir, "check_utilities_rm_rm_file_notlast_dir", "Yes", POSIX_c181, MANDATORY, "rm when file’s link count is not 0 shall update MC of parent dir");
    
    runtest(env, "UTILITIES.RM.RMDIR.EMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rmdir_empty, "check_utilities_rm_rmdir_empty", "Yes", POSIX_c181, MANDATORY, "rmdir on an empty dir shall update parent directory MC");
    runtest(env, "UTILITIES.RM.RMDIR.NOTEMPTY", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rmdir_notempty, "check_utilities_rm_rmdir_notempty", "No", "", MANDATORY, "rmdir on a not empty dir shall not update MAC");
    runtest(env, "UTILITIES.RM.RMDIR.NOTEMPTY.PARENTDIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_rmdir_notempty_parentdir, "check_utilities_rm_rmdir_notempty_parentdir", "No", "", MANDATORY, "rmdir on a not empty dir shall not update parent directory MAC");
    
    runtest(env, "UTILITIES.RM.UNLINK.LAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_unlink_last, "check_utilities_rm_unlink_last", "Yes", POSIX_c181, MANDATORY, "unlink when file’s link count is 0 shall update parent directory MC");
    runtest(env, "UTILITIES.RM.UNLINK.NOTLAST", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_unlink_notlast, "check_utilities_rm_unlink_notlast", "Yes", POSIX_c181, MANDATORY, "unlink when file’s link count is not 0 shall update the file C");
    runtest(env, "UTILITIES.RM.UNLINK.NOTLAST.DIR", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_rm_unlink_notlast_dir, "check_utilities_rm_unlink_notlast_dir", "Yes", POSIX_c181, MANDATORY, "unlink when file’s link count is not 0 shall update parent directory MC");
}

void group_check_utilities_ln(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "UTILITIES.LN.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ln_new, "check_utilities_ln_new", "Yes", POSIX_c181, MANDATORY, "ln when the target does not exist shall update C and MC of the directory containing the new entry");
    runtest(env, "UTILITIES.LN.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ln_existing, "check_utilities_ln_existing", "Yes", POSIX_c181, MANDATORY, "ln when the target exists shall not update MAC of the target nor of its parent directory");
    runtest(env, "UTILITIES.LN.S.NEW", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ln_s_new, "check_utilities_ln_s_new", "Yes", POSIX_c181, MANDATORY, "ln -s when the target does not exist shall update MAC of the link and MC of the directory containing the link");
    runtest(env, "UTILITIES.LN.S.EXISTING", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ln_s_existing, "check_utilities_ln_s_existing", "Yes", POSIX_c181, MANDATORY, "ln -s when the target exists shall not update MAC of the target nor of its parent directory");
}

void group_check_utilities_ls(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    runtest(env, "UTILITIES.LS", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ls, "check_utilities_ls", "No", "", MANDATORY, "ls shall update A of target directory");
    runtest(env, "UTILITIES.LS.FILES", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ls_files, "check_utilities_ls_files", "No", "", MANDATORY, "ls shall not update MAC of files in target directory");
}

void group_check_utilities_vi(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
//     fseek(stdin, 0, SEEK_END);
    
    if (OPTION_TEST_INPUT == 1){
        runtest(env, "UTILITIES.VI.NEW.I.W.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_new_i_w_q, "check_utilities_vi_new_i_w_q", "No", "", MANDATORY, "vi on new file (w then q) shall update MAC on write command and update MC of parent directory");
        runtest(env, "UTILITIES.VI.NEW.I.W.Q.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_new_i_w_q_mac, "check_utilities_vi_new_i_w_q_mac", "No", "", MANDATORY, "vi on new file (w then q) shall update set MAC equal");
        runtest(env, "UTILITIES.VI.EXISTING.I.W.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_w_q, "check_utilities_vi_existing_i_w_q", "No", "", MANDATORY, "vi on existing file (w then q) shall update A on launch, MC on write command");
        runtest(env, "UTILITIES.VI.EXISTING.I.W.Q.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_w_q_mc, "check_utilities_vi_existing_i_w_q_mc", "No", "", MANDATORY, "vi on existing file (w then q) shall set MC equal");
        runtest(env, "UTILITIES.VI.EXISTING.I.WQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_wq, "check_utilities_vi_existing_i_wq", "No", "", MANDATORY, "vi on existing file (wq) shall update A on launch MC on write command");
        runtest(env, "UTILITIES.VI.EXISTING.I.WQ.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_wq_mc, "check_utilities_vi_existing_i_wq_mc", "No", "", MANDATORY, "vi on existing file (wq) shall set MC equal");
        runtest(env, "UTILITIES.VI.EXISTING.I.X", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_x, "check_utilities_vi_existing_i_x", "No", "", MANDATORY, "vi on existing file (x) shall update A on launch MC on write command");
        runtest(env, "UTILITIES.VI.EXISTING.I.X.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_x_mc, "check_utilities_vi_existing_i_x_mc", "No", "", MANDATORY, "vi on existing file (x) shall set MC equal");
        runtest(env, "UTILITIES.VI.EXISTING.I.Q!", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_vi_existing_i_qEM, "check_utilities_vi_existing_i_qEM", "No", "", MANDATORY, "vi on existing file with no write (q!) shall up date A on launch and not MC");
    }
}

void group_check_utilities_ed(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    if (OPTION_TEST_INPUT == 1){
        runtest(env, "UTILITIES.ED.NEW.I.W.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_new_i_w_q, "check_utilities_ed_new_i_w_q", "No", "", MANDATORY, "ed on new file (w then q) shall update MAC on write command and update MC of parent directory");
        runtest(env, "UTILITIES.ED.NEW.I.W.Q.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_new_i_w_q_mac, "check_utilities_ed_new_i_w_q_mac", "No", "", MANDATORY, "ed on new file (w then q) shall update set MAC equal");
        runtest(env, "UTILITIES.ED.EXISTING.I.W.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_existing_i_w_q, "check_utilities_ed_existing_i_w_q", "No", "", MANDATORY, "ed on existing file (w then q) shall update A on launch, MC on write command");
        runtest(env, "UTILITIES.ED.EXISTING.I.W.Q.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_existing_i_w_q_mc, "check_utilities_ed_existing_i_w_q_mc", "No", "", MANDATORY, "ed on existing file (w then q) shall set MC equal");
        runtest(env, "UTILITIES.ED.EXISTING.I.WQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_existing_i_wq, "check_utilities_ed_existing_i_wq", "No", "", MANDATORY, "ed on existing file (wq) shall update A on launch MC on write command");
        runtest(env, "UTILITIES.ED.EXISTING.I.WQ.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_existing_i_wq_mc, "check_utilities_ed_existing_i_wq_mc", "No", "", MANDATORY, "ed on existing file (wq) shall set MC equal");
        runtest(env, "UTILITIES.ED.EXISTING.I.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ed_existing_i_Q, "check_utilities_ed_existing_i_Q", "No", "", MANDATORY, "ed on existing file with no write (q!) shall up date A on launch and not MC");
    }
}

void group_check_utilities_ex(testenv_struct* env){
    if (should_group_run(env, __func__) == 0) return;
    
    if (OPTION_TEST_INPUT == 1){
        runtest(env, "UTILITIES.EX.NEW.I.W.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_new_i_w_q, "check_utilities_ex_new_i_w_q", "No", "", MANDATORY, "ex on new file (w then q) shall update MAC on write command and update MC of parent directory");
        runtest(env, "UTILITIES.EX.NEW.I.W.Q.MAC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_new_i_w_q_mac, "check_utilities_ex_new_i_w_q_mac", "No", "", MANDATORY, "ex on new file (w then q) shall update set MAC equal");
        runtest(env, "UTILITIES.EX.EXISTING.I.W.Q", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_w_q, "check_utilities_ex_existing_i_w_q", "No", "", MANDATORY, "ex on existing file (w then q) shall update A on launch, MC on write command");
        runtest(env, "UTILITIES.EX.EXISTING.I.W.Q.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_w_q_mc, "check_utilities_ex_existing_i_w_q_mc", "No", "", MANDATORY, "ex on existing file (w then q) shall set MC equal");
        runtest(env, "UTILITIES.EX.EXISTING.I.WQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_wq, "check_utilities_ex_existing_i_wq", "No", "", MANDATORY, "ex on existing file (wq) shall update A on launch MC on write command");
        runtest(env, "UTILITIES.EX.EXISTING.I.WQ.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_wq_mc, "check_utilities_ex_existing_i_wq_mc", "No", "", MANDATORY, "ex on existing file (wq) shall set MC equal");
        runtest(env, "UTILITIES.EX.EXISTING.I.X", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_x, "check_utilities_ex_existing_i_x", "No", "", MANDATORY, "ex on existing file (x) shall update A on launch MC on write command");
        runtest(env, "UTILITIES.EX.EXISTING.I.X.MC", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_x_mc, "check_utilities_ex_existing_i_x_mc", "No", "", MANDATORY, "ex on existing file (x) shall set MC equal");
        runtest(env, "UTILITIES.EX.EXISTING.I.Q!", 1, REPEAT_WORST, s_0s, ns_10ms, check_utilities_ex_existing_i_qEM, "check_utilities_ex_existing_i_qEM", "No", "", MANDATORY, "ex on existing file with no write (q!) shall up date A on launch and not MC");
    }
}

#endif
    
