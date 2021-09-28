#include "p_gio_rename.h"

struct profile_info_struct* profile_gio_rename_file_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");

    char** watch_array = misc_char_array3(path_file, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    log_info(env->output_file, env->error_file, "%s - ***INFO : Start Looking Here", __func__, errno);

    GFile *file = g_file_new_for_path(path_file);
    g_file_set_display_name(file, "renamed", NULL, NULL);

    log_info(env->output_file, env->error_file, "%s - ***INFO : Stop Looking Here", __func__);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_rename_directory_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_orig = misc_concat_ensure_dir_exists(path_dir, "orig/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    misc_concat_ensure_file_exists_filled(path_orig, "dir_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");

    char** watch_array = misc_char_array3(path_orig, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_orig);
    g_file_set_display_name(file, "renamed", NULL, NULL);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}
