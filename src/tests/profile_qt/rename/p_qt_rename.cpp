#include "p_qt_rename.h"

struct profile_info_struct* profile_qt_rename_file_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");

    char** watch_array = misc_char_array3(path_file, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    //sleep(40);

    QFile().rename(path_file, path_new);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_qt_rename_directory_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_orig = misc_concat_ensure_dir_exists(path_dir, "orig/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    misc_concat_ensure_file_exists_filled(path_orig, "dir_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");

    char** watch_array = misc_char_array3(path_orig, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QDir().rename(path_orig, path_new);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}
