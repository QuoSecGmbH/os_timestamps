#ifndef PROFILE_OS_C
#define PROFILE_OS_C

#include "profile_os.h"

int main (int argc, char **argv){
    if (argc >= 2){
        VERBOSE=1;
    }
  
    FILE* csv_file = log_open_csv("os_profile_results.csv");
    FILE* output_file = stdout;
//     FILE* output_file = fopen("os_profile_output.txt", "wb");
    FILE* error_file = stderr;
//     FILE* error_file = fopen("os_profile_error.txt", "wb");
  
    int i;
    char* dir_base_path = "tmp_os_profile";
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
    
    if (dir_path == NULL){
        log_error(output_file, error_file, "%s", "Impossible to find suitable directory for tests, exiting.");
        return 1;
    }
    log_info(output_file, error_file, "Directory for tests is: %s", dir_path);
    
    // pre-creating some of the test files
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.futimens", s_0s, ns_0ns, output_file, error_file, __func__);

//     misc_concat_ensure_file_exists_free(dir_path, "profile_os_pause", 2*s_1s, ns_0ns, output_file, error_file, __func__);
    
    testenv_struct* test_env = testenv_alloc(csv_file, output_file, error_file, dir_path);
    
//     log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Level", "Ref", "Function");

//     group_profileos_filerename(test_env);
//     group_profileos_dirrename(test_env);
//     group_profileos_localfilemove(test_env);
//     group_profileos_localdirmove(test_env);
//     group_profileos_filecopy_new(test_env);
//     group_profileos_filecopy_existing(test_env);
//     group_profileos_dircopy(test_env);
    
//     group_profileos_filecreation(test_env);
//     group_profileos_dircreation(test_env);
    
    
//     group_profileos_fileaccess(test_env);
    group_profileos_filemodify(test_env);
    
   
//     free(test_env);
//     free(dir_path);
    
    log_close_csv(csv_file);
}

void group_profileos_filerename(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filerename_interface_new(env);
    struct profile_info_struct* pi2 = profileos_filerename_interface_existing(env);
    struct profile_info_struct* pi3 = profileos_filerename_utilities_new(env);
    struct profile_info_struct* pi4 = profileos_filerename_utilities_existing(env);
    
    char** mask = misc_char_array3("src", "dst", "dir");
    process_profiles4(mask, "File Rename", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_dirrename(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filerename_interface_dir_new(env);
    struct profile_info_struct* pi2 = profileos_filerename_interface_dir_existing(env);
    struct profile_info_struct* pi3 = profileos_filerename_utilities_dir_new(env);
    
    char** mask = misc_char_array3("src", "dst", "dir");
    process_profiles3(mask, "Dir Rename", __func__, env, pi1, pi2, pi3);
}

void group_profileos_localfilemove(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_localfilemove_interface_new(env);
    struct profile_info_struct* pi2 = profileos_localfilemove_interface_existing(env);
    struct profile_info_struct* pi3 = profileos_localfilemove_utilities_new(env);
    struct profile_info_struct* pi4 = profileos_localfilemove_utilities_existing(env);
    
    char** mask = misc_char_array4("src", "srcdir", "dst", "dstdir");
    process_profiles4(mask, "Local File Move", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_localdirmove(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_localfilemove_interface_dir_new(env);
    struct profile_info_struct* pi2 = profileos_localfilemove_interface_dir_existing(env);
    struct profile_info_struct* pi3 = profileos_localfilemove_utilities_dir_new(env);
    
    char** mask = misc_char_array4("src", "srcdir", "dst", "dstdir");
    process_profiles3(mask, "Local Dir Move", __func__, env, pi1, pi2, pi3);
}

void group_profileos_filecopy_new(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_interface_new(env);
    struct profile_info_struct* pi2 = profileos_filecopy_utilities_new(env);
    
    char** mask = misc_char_array4("src", "srcdir", "dst", "dstdir");
    process_profiles2(mask, "File Copy (new)", __func__, env, pi1, pi2);
}

void group_profileos_filecopy_existing(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_interface_existing(env);
    struct profile_info_struct* pi2 = profileos_filecopy_utilities_existing(env);
    
    char** mask = misc_char_array4("src", "srcdir", "dst", "dstdir");
    process_profiles2(mask, "File Copy (existing)", __func__, env, pi1, pi2);
}

void group_profileos_dircopy(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_utilities_dir_new(env);
    
    char** mask = misc_char_array4("src", "srcdir", "dst", "dstdir");
    process_profiles1(mask, "Dir Copy (new)", __func__, env, pi1);
}

void group_profileos_filecreation(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities(env);
    
    char** mask = misc_char_array2("dir", "newfile");
    process_profiles2(mask, "File Creation (new)", __func__, env, pi1, pi2);
}

void group_profileos_dircreation(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface_dir(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities_dir(env);
    
    char** mask = misc_char_array2("dir", "newfile");
    process_profiles2(mask, "Dir Creation (new)", __func__, env, pi1, pi2);
}

void group_profileos_fileaccess(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_fileaccess_interface(env);
    struct profile_info_struct* pi2 = profileos_fileaccess_utilities(env);
    
    char** mask = misc_char_array2("dir", "file");
    process_profiles2(mask, "File Access (existing)", __func__, env, pi1, pi2);
}

void group_profileos_filemodify(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filemodify_interface_wb(env);
    struct profile_info_struct* pi2 = profileos_filemodify_interface_rp(env);
    struct profile_info_struct* pi3 = profileos_filemodify_interface_a(env);
    struct profile_info_struct* pi4 = profileos_filemodify_utilities(env);
    
    char** mask = misc_char_array2("dir", "file");
    process_profiles4(mask, "File Modify (existing)", __func__, env, pi1, pi2, pi3, pi4);
}

void print_profile(struct profile_info_struct* pi, char** mask, testenv_struct* env){
    if (mask != NULL){
        misc_print_profile_masked(env->output_file, env->error_file, pi, mask);
    }
    else {
       misc_print_profile(env->output_file, env->error_file, pi); 
    }
    if (VERBOSE){
        log_info_ts_profile_on_error_message_short(env->output_file, env->error_file, "", 0, pi, "");
    }   
}

void process_profiles(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct** pi_list, int pi_num){
    if (pi_num == 0){
        log_warning(env->output_file, env->error_file, "%s", "Profile list is empty.");
        return;
    }
    
    int all_eq = 1;
    int i;
    for (i = 0; i < pi_num-1; i++){
        if (misc_profile_eq(pi_list[i], pi_list[i+1]) != 0){
            all_eq = 0;
        }
    }
    
    fprintf(env->output_file, "%s (%s):\n", desc, func_name);
    if (all_eq){
        print_profile(pi_list[0], mask, env);
        
        if (VERBOSE){
            for (i = 0; i < pi_num; i++){
                print_profile(pi_list[i], NULL, env);
                fprintf(env->output_file, "\n");
            }
        }
    }
    else {
        fprintf(env->output_file, "Conflictual results\n");
        for (i = 0; i < pi_num; i++){
            print_profile(pi_list[i], NULL, env);
            fprintf(env->output_file, "\n");
        }
    }
    
}

void process_profiles1(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1){
    struct profile_info_struct** pi_list = calloc(1, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    process_profiles(mask, desc, func_name, env, pi_list, 1);    
}

void process_profiles2(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2){
    struct profile_info_struct** pi_list = calloc(2, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    process_profiles(mask, desc, func_name, env, pi_list, 2);    
}

void process_profiles3(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3){
    struct profile_info_struct** pi_list = calloc(3, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    process_profiles(mask, desc, func_name, env, pi_list, 3);    
}

void process_profiles4(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4){
    struct profile_info_struct** pi_list = calloc(4, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    process_profiles(mask, desc, func_name, env, pi_list, 4);    
}

void process_profiles5(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5){
    struct profile_info_struct** pi_list = calloc(5, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    process_profiles(mask, desc, func_name, env, pi_list, 5);    
}

void process_profiles6(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6){
    struct profile_info_struct** pi_list = calloc(6, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    process_profiles(mask, desc, func_name, env, pi_list, 6);    
}

void process_profiles7(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7){
    struct profile_info_struct** pi_list = calloc(7, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    pi_list[6] = pi7;
    process_profiles(mask, desc, func_name, env, pi_list, 7);    
}

void process_profiles8(char** mask, char* desc, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7, struct profile_info_struct* pi8){
    struct profile_info_struct** pi_list = calloc(8, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    pi_list[6] = pi7;
    pi_list[7] = pi8;
    process_profiles(mask, desc, func_name, env, pi_list, 8);    
}
#endif
