#ifndef RUN_TESTS_C
#define RUN_TESTS_C

#include "run_tests.h"

char* POSIX_c181 = "POSIX_c181";

int main (){
    FILE* csv_file = log_open_csv("results.csv");
    FILE* output_file = stdout;
    FILE* error_file = stderr;
  
    int i;
    char* dir_base_path = "tmp_tests";
    char* dir_path = NULL;
    for (i = 0; i <= 100; i++){
        char* buf = (char*) calloc(sizeof(char), strlen(dir_base_path)+6);
        sprintf(buf, "%s_%03d/", dir_base_path, i);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        if (stat(buf, attr) == -1) {
            mkdir(buf, 0700);
            dir_path = buf;
            break;
        }
    }
    
    if (dir_path == NULL){
        log_error(output_file, error_file, "%s", "Impossible to find suitable directory for tests, exiting.");
        return 1;
    }
    log_info(output_file, error_file, "Directory for tests is: %s", dir_path);
    
    log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Ref", "Function");
    group_check_general_clock(csv_file, output_file, error_file);
    group_check_general_update(csv_file, output_file, error_file, dir_path);

    log_close_csv(csv_file);
}

void group_check_general_clock(FILE* csv_file, FILE* output_file, FILE* error_file){
    int result;
    
    result = check_general_clock_res(csv_file, output_file, error_file);
    log_csv_add_result(csv_file, output_file, error_file, result, "Clock resolution shall be at max 0.02s", "Yes", POSIX_c181, "GENERAL.CLOCK.RES", "check_clock_res");
}

void group_check_general_update(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    int result;
    
    result = check_general_new_file(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "New file shall have MAC updated", "Yes", POSIX_c181, "GENERAL.NEW_FILE", "check_general_new_file");
    result = check_general_new_file_mac_eq(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "New file shall have MAC set to same time", "No", "", "GENERAL.NEW_FILE.MAC_eq", "check_general_new_file_mac_eq");
}


#endif
