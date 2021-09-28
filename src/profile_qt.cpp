#ifndef PROFILE_QT_C
#define PROFILE_QT_C

#include "profile_qt.h"

int PROFILE_TREAT_DELAY_AS_COMMAND = 0;
int OPTION_VOLUME_FILE_MOVE = 0;
int OPTION_QUICK = 0;
gid_t CHOWN_GROUP_GID = -1;
char* mounted = NULL;

void print_usage(){
    fprintf(stderr, "Usage: ./profile_gio [options] \"CMD\"\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  --verbose / -v\n");
    fprintf(stderr, "  --mounted / -m MNT\n");
}

int main(int argc, char *argv[]) {
    int c;
    while (1) {
        static struct option long_options[] =
                {
                        {"verbose", no_argument,       0, 'v'},
                        {"nodelay", no_argument,       0, 'd'},
                        {"mounted", required_argument, 0, 'm'},
                        {"guid-chown", required_argument, 0, 'g'},
                        {"quick", required_argument, 0, 'q'},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "vdm:g:q",
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
            case 'q': {
                OPTION_QUICK = 1;
                break;
            }
            case 'm': {
                OPTION_VOLUME_FILE_MOVE = 1;
                mounted = optarg;
                break;
            }
            case 'g': {
                CHOWN_GROUP_GID = (gid_t) atoi(optarg);
                break;
            }
            default:
                fprintf(stderr, "Unknown argument.\n");
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    return run_profile_qt();
}

int run_profile_qt(){
    FILE* csv_file_brief = log_open_csv("qt_profile_results.csv");
    FILE* csv_file_flags = log_open_csv("qt_profile_flags.csv");
    FILE* output_file = stdout;
    FILE* error_file = stderr;

    int i;
    char* dir_base_path = "tmp_qt_profile";
    char* dir_path = NULL;
    char* dir_path_volume = NULL;
    for (i = 0; i <= 99; i++){
        char* buf = (char*) calloc(sizeof(char), strlen(dir_base_path)+6);
        sprintf(buf, "%s_%02d/", dir_base_path, i);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        if (stat(buf, attr) == -1) {
            mkdir(buf, 0700);
            dir_path = buf;
            if (OPTION_VOLUME_FILE_MOVE){
                struct stat* attr_volume = (struct stat*) calloc(sizeof(struct stat), 1);
                dir_path_volume = misc_concat(mounted, buf);
                if (stat(dir_path_volume, attr) == -1) {
                    mkdir(dir_path_volume, 0700);
                }
                else {
                    log_error(output_file, error_file, "Dir %s already exists, please remove similar dir before relaunching", dir_path_volume);
                    return 1;
                }
            }
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
    if (OPTION_VOLUME_FILE_MOVE){
        log_info(output_file, error_file, "Volume path is: %s", dir_path_volume);
    }

    if (CHOWN_GROUP_GID == -1){
        log_warning(output_file, error_file, "Group gid is -1, tests using chown (filechange) may be non-reliable. Set git with -g option.");
    }

    current_time_setup_local_timemarker(output_file, error_file);
    current_time_setup_local_timemarkerdir(output_file, error_file);
    testenv_struct* test_env = testenv_alloc_csv(csv_file_brief, output_file, error_file, dir_path, dir_path_volume, csv_file_flags);

    log_csv_add_line(csv_file_brief, 2, "Reference", "MACB");
    log_csv_add_line(csv_file_flags, 4, "Description", "File", "M/A/C/B", "Flag");

    group_profile_qt_rename_file(test_env);
    group_profile_qt_rename_directory(test_env);


    group_profile_qt_move_file(test_env);
    group_profile_qt_move_directory(test_env);

//     Provoke segfault:
//     group_profile_qt_volume_fileMove(test_env);
//     group_profile_qt_volume_directoryMove(test_env);
    

    group_profile_qt_copy_file_new(test_env);

    group_profile_qt_create_file(test_env);
    group_profile_qt_create_file_symlink(test_env);
    group_profile_qt_create_file_intoSymlinkDir(test_env);
    group_profile_qt_create_directory(test_env);
    group_profile_qt_create_directory_symlink(test_env);

    group_profile_qt_access_file(test_env);
    group_profile_qt_access_symlink(test_env);

    group_profile_qt_modify_file(test_env);
    group_profile_qt_modify_symlink(test_env);


//      Need superuser rights --> sudo ./profile_gio -g 1002
     group_profile_qt_change_file(test_env);
     group_profile_qt_change_dir(test_env);
     group_profile_qt_change_symlink_follow(test_env);
     
//      group_profile_qt_change_symlink_notFollow(test_env); // Does not exist (?)



    group_profile_qt_delete_last_File(test_env);
    group_profile_qt_delete_notLast_file(test_env);
    group_profile_qt_delete_symlink_file(test_env);
    group_profile_qt_delete_directory(test_env);
    group_profile_qt_delete_symlink_directory(test_env);

    log_close_csv(csv_file_brief);
    log_close_csv(csv_file_flags);

    return 1;
}

void group_profile_qt_rename_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_rename_file_new(env);

    char** mask = misc_char_array3("src", "dst", "dir/");
    process_profiles1(mask, "File Rename", "PROFILE.QT.RENAME.FILE.NEW", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_rename_directory(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_rename_directory_new(env);

    char** mask = misc_char_array3("src/", "dst/", "dir/");
    process_profiles1(mask, "Directory Rename", "PROFILE.QT.RENAME.DIRECTORY.NEW", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_move_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_move_file_new(env);

    char** mask = misc_char_array4("src_file", "src_dir/", "dst_file", "dst_dir/");
    process_profiles1(mask, "Local File Move", "PROFILE.QT.MOVE.FILE", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_move_directory_existing(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_move_file_existing(env);

    char** mask = misc_char_array4("src/", "src_dir/", "dst/", "dst_dir/");
    process_profiles1(mask, "Local File Move (Existing)", "PROFILE.QT.MOVE.FILE.EXISTING", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_move_directory(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_move_directory_new(env);

    char** mask = misc_char_array4("src/", "src_dir/", "dst/", "dst_dir/");
    process_profiles1(mask, "Local Directory Move", "PROFILE.QT.MOVE.DIRECTORY", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_copy_file_new(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_copy_file_new(env);

    char** mask = misc_char_array4("src_file", "src_dir/", "dst_file", "dst_dir/");
    process_profiles1(mask, "File Copy New", "PROFILE.QT.COPY.FILE.NEW", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_create_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_create_file(env);

    char** mask = misc_char_array2("dir/", "new_file");
    process_profiles1(mask, "File Creation", "PROFILE.QT.CREATE.FILE", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_create_file_symlink(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_create_symlink_to_file(env);

    char** mask = misc_char_array4("new_file", "symlink", "directory_with_file/", "directory_with_symlink/");
    process_profiles1(mask, "Symlink (to file) Creation", "PROFILE.QT.CREATE.SYMLINK_TO_FILE",
                      const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_create_file_intoSymlinkDir(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_create_file_into_symlink_dir(env);

    char** mask = misc_char_array3("dir/", "symlink_dir", "file");
    process_profiles1(mask, "File Creation into Symlink Dir", "PROFILE.QT.CREATE.FILE.INTO_SYMLINK_DIR",
                      const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_create_directory(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_create_directory(env);

    char** mask = misc_char_array2("parent_dir/", "new_dir");
    process_profiles1(mask, "Directory Creation", "PROFILE.QT.CREATE.DIR", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_create_directory_symlink(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_create_symlink_to_dir(env);

    char** mask = misc_char_array4("new_dir/", "symlink", "directory_with_dir/", "directory_with_link/");
    process_profiles1(mask, "Symlink (to dir) Creation", "PROFILE.QT.CREATE.SYMLINK_TO_DIR",
                      const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_access_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_access_file_readOnly(env);
    struct profile_info_struct* pi2 = profile_qt_access_file_readWrite(env);

    char** mask = misc_char_array2("dir/", "file");
    process_profiles2(mask, "File Access", "PROFILE.QT.READ.FILE", const_cast<char *>(__func__), env, pi1, pi2);
}

void group_profile_qt_access_symlink(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_access_symlink_readOnly(env);
    struct profile_info_struct* pi2 = profile_qt_access_symlink_readWrite(env);

    char** mask = misc_char_array4("file", "symlink", "file_dir/", "link_dir/");
    process_profiles2(mask, "Symlink (to file) Access (default follow)", "PROFILE.QT.READ.SYMLINK",
                      const_cast<char *>(__func__), env, pi1, pi2);
}

void group_profile_qt_modify_file(testenv_struct* env) {
    struct profile_info_struct* pi2 = profile_qt_modify_file_append(env);
    struct profile_info_struct* pi3 = profile_qt_modify_file_readWrite(env);
    struct profile_info_struct* pi1 = profile_gio_modify_file_writeOnly(env);

    char** mask = misc_char_array2("dir/", "file");
    process_profiles3(mask, "File Modify", "PROFILE.QT.WRITE.FILE", const_cast<char *>(__func__), env, pi1, pi2, pi3);
}

void group_profile_qt_modify_symlink(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_modify_symlink_writeOnly(env);
    struct profile_info_struct* pi2 = profile_qt_modify_symlink_append(env);
    struct profile_info_struct* pi3 = profile_qt_modify_symlink_readWrite(env);

    char** mask = misc_char_array4("file", "symlink", "file_dir/", "link_dir/");
    process_profiles3(mask, "Symlink (to file) Modify (default follow)", "PROFILE.QT.WRITE.SYMLINK",
                      const_cast<char *>(__func__), env, pi1, pi2, pi3);
}

void group_profile_qt_change_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_change_chmod_file(env);

    char** mask = misc_char_array2("dir/", "file");
    process_profiles1(mask, "File Change", "PROFILE.QT.CHANGE.FILE", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_change_symlink_follow(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_change_chmod_symlink(env);

    char** mask = misc_char_array4("file", "symlink", "file_dir/", "link_dir/");
    process_profiles1(mask, "Symlink (to file) Change (default follow)", "PROFILE.QT.CHANGE.SYMLINK.FOLLOW",
                      const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_change_dir(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_change_chmod_dir(env);

    char** mask = misc_char_array2("parent_dir/", "dir/");
    process_profiles1(mask, "Dir Change", "PROFILE.QT.CHANGE.DIR", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_delete_last_File(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_delete_lastFile_empty(env);
    struct profile_info_struct* pi2 = profile_qt_delete_lastFile_notEmpty(env);

    char** mask = misc_char_array2("dir/", "file");
    process_profiles2(mask, "File Delete (last hard link)", "PROFILE.QT.DELETE.FILE.LAST",
                      const_cast<char *>(__func__), env, pi1, pi2);

}

void group_profile_qt_delete_notLast_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_delete_notLastFile_empty(env);
    struct profile_info_struct* pi2 = profile_qt_delete_notLastFile_notEmpty(env);

    char** mask = misc_char_array2("dir/", "file");
    process_profiles2(mask, "File Delete (not last hard link)", "PROFILE.QT.DELETE.FILE.NOT_LAST",
                      const_cast<char *>(__func__), env, pi1, pi2);

}

void group_profile_qt_delete_symlink_file(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_delete_symlink(env);

    char** mask = misc_char_array4("file", "symlink", "file_dir/", "link_dir/");
    process_profiles1(mask, "Symlink (to file) Delete", "PROFILE.QT.DELETE.SYMLINK.TO_FILE",
                      const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_delete_directory(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_delete_directory(env);

    char** mask = misc_char_array2("parent_dir/", "dir/");
    process_profiles1(mask, "Directory Delete (last hard link)", "PROFILE.QT.DELETE.DIR", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_delete_symlink_directory(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_delete_directory_symlink(env);

    char** mask = misc_char_array4("dir/", "symlink", "directory_with_dir/", "directory_with_symlink/");
    process_profiles1(mask, "Symlink (to dir) Delete", "PROFILE.QT.DELETE.SYMLINK.TO_DIR",
                      const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_directory_traversal(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_traversal_directory(env);

    char** mask = misc_char_array1("dir/");
    process_profiles1(mask, "Dir Traversal", "PROFILE.QT.TRAVERSAL.DIRECTORY", const_cast<char *>(__func__), env, pi1);
}

void group_profile_qt_directory_traversal_symlink(testenv_struct* env) {
    struct profile_info_struct* pi1 = profile_qt_traversal_directory_symlink(env);

    char** mask = misc_char_array2("dir/", "symlink");
    process_profiles1(mask, "Symlink (to dir) Traversal", "PROFILE.QT.TRAVERSAL.SYMLINK.TO_DIR", const_cast<char *>(__func__), env, pi1);
}

void print_profile(struct profile_info_struct* pi, char** mask, testenv_struct* env, char* desc, char* func_name){
    misc_print_profile_masked(env->output_file, env->error_file, pi, mask, desc, func_name, env->csv_file, env->csv_file_flags);
    if (VERBOSE){
        log_info_ts_profile_on_error_message_short(env->output_file, env->error_file, "", 0, pi, "");
    }
}

void process_profiles(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct** pi_list, int pi_num){
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

    fprintf(env->output_file, "%s (%s):\n", desc, ref);
    if (all_eq){
        print_profile(pi_list[0], mask, env, ref, func_name);

        if (VERBOSE){
            for (i = 0; i < pi_num; i++){
                print_profile(pi_list[i], NULL, env, ref, func_name);
                fprintf(env->output_file, "\n");
            }
        }
    }
    else {
        fprintf(env->output_file, "Conflictual results\n");
        for (i = 0; i < pi_num; i++){
            print_profile(pi_list[i], NULL, env, ref, func_name);
            fprintf(env->output_file, "\n");
        }
    }

}

void process_profiles1(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(1,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 1);
}

void process_profiles2(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(2,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 2);
}

void process_profiles3(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(3,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 3);
}

void process_profiles4(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(4,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 4);
}

void process_profiles5(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(5,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 5);
}

void process_profiles6(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(6,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 6);
}

void process_profiles7(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(7,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    pi_list[6] = pi7;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 7);
}

void process_profiles8(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7, struct profile_info_struct* pi8){
    struct profile_info_struct** pi_list = static_cast<profile_info_struct **>(calloc(8,
                                                                                      sizeof(struct profile_info_struct *)));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    pi_list[6] = pi7;
    pi_list[7] = pi8;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 8);
}

#endif
