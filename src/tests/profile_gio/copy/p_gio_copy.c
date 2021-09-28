#include "p_gio_copy.h"

/*
 * copy a file to a new file that does not yet exist
 */
struct profile_info_struct* profile_gio_copy_file_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_to_copy = misc_concat_ensure_file_exists_filled(path_src_dir, "src_file", 10000, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_dst_file = misc_concat(path_dst_dir, "dst_file");
    
    misc_nanosleep(ns_DELAY); // Delay

    char** watch_array = misc_char_array4(path_file_to_copy, path_src_dir, path_dst_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *src_file = g_file_new_for_path(path_file_to_copy);
    GFile *dst_file = g_file_new_for_path(path_dst_file);
    gboolean isCopy = g_file_copy(src_file, dst_file, G_FILE_COPY_NONE, NULL, NULL, NULL, NULL);

    g_assert_true(isCopy);
    g_object_unref(src_file);
    g_object_unref(dst_file);
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

/*
 * copy a file to an existing one
 */
struct profile_info_struct* profile_gio_copy_file_existing(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_src_file = misc_concat_ensure_file_exists_filled(path_src_dir, "src_file", 10000, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_to_dst_file = misc_concat_ensure_file_exists_filled(path_dst_dir, "dst_file", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    misc_nanosleep(ns_DELAY); // Delay

    char** watch_array = misc_char_array4(path_to_src_file, path_src_dir, path_to_dst_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *src_file = g_file_new_for_path(path_to_src_file);
    GFile *dst_file = g_file_new_for_path(path_to_dst_file);
    gboolean isCopy = g_file_copy(src_file, dst_file, G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, NULL);

    g_assert_true(isCopy);
    g_object_unref(src_file);
    g_object_unref(dst_file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * directory copy == recursive file copy with for loop
 */

