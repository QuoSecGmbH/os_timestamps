#include "p_gio_volume_fileMove.h"

struct profile_info_struct* profile_gio_volume_fileMove_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir_volume, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_file = misc_concat_ensure_file_exists_filled(path_src_dir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new_file = misc_concat(path_dst_dir, "dst");

    char** watch_array = misc_char_array4(path_src_file, path_src_dir, path_new_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    printf("p1 %s\n", path_src_file);
    printf("p2 %s\n", path_new_file);

    GFile *src_file = g_file_new_for_path(path_src_file);
    GFile *dst_file = g_file_new_for_path(path_new_file);
    g_file_move(src_file, dst_file, G_FILE_COPY_NONE, NULL, NULL, NULL, NULL);

    g_object_unref(src_file);
    g_object_unref(dst_file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_volume_fileMove_existing(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir_volume, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_file = misc_concat_ensure_file_exists_filled(path_src_dir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new_file = misc_concat_ensure_file_exists_filled(path_dst_dir, "dst", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array4(path_src_file, path_src_dir, path_new_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *src_file = g_file_new_for_path(path_src_file);
    GFile *dst_file = g_file_new_for_path(path_new_file);
    g_file_move(src_file, dst_file, G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, NULL);

    g_object_unref(src_file);
    g_object_unref(dst_file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_volume_directoryMove_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir_volume, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_src_directory = misc_concat_ensure_dir_exists(path_src_dir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_to_src_directory, "dir_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char* path_to_dst_directory = misc_concat(path_dst_dir, "dst");

    char** watch_array = misc_char_array4(path_to_src_directory, path_src_dir, path_to_dst_directory, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *src_directory = g_file_new_for_path(path_to_src_directory);
    GFile *dst_directory = g_file_new_for_path(path_to_dst_directory);
    g_file_move(src_directory, dst_directory, G_FILE_COPY_NONE, NULL, NULL, NULL, NULL);

    g_object_unref(src_directory);
    g_object_unref(dst_directory);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_volume_directoryMove_existing(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir_volume, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_src_directory = misc_concat_ensure_dir_exists(path_src_dir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_to_src_directory, "dir_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_to_dst_directory = misc_concat_ensure_dir_exists(path_dst_dir, "dst/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array4(path_to_src_directory, path_src_dir, path_to_dst_directory, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *src_directory = g_file_new_for_path(path_to_src_directory);
    GFile *dst_directory = g_file_new_for_path(path_to_dst_directory);
    g_file_move(src_directory, dst_directory, G_FILE_COPY_OVERWRITE, NULL, NULL, NULL, NULL);

    g_object_unref(src_directory);
    g_object_unref(dst_directory);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}
