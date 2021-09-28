#include "p_gio_access.h"

struct profile_info_struct* profile_gio_access_file(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file_to_read = misc_concat_ensure_file_exists_filled(path_dir, "file_to_read", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file_to_read);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file_to_read = g_file_new_for_path(path_file_to_read);
    GFileInputStream *read_stream = g_file_read(file_to_read, NULL, NULL);

    gssize read;
    char temp[1000];

    while(TRUE) {
        read = g_input_stream_read(G_INPUT_STREAM(read_stream), temp, G_N_ELEMENTS(temp) - 1, NULL, NULL);
        if(read <= 0) {
            break;
        }
    }

    g_object_unref(file_to_read);
    g_object_unref(read_stream);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_access_symlink(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_file/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_symlink/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_symlink_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../directory_with_file/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_file, path_symlink, path_file_dir, path_symlink_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink_to_read = g_file_new_for_path(path_symlink);
    GFileInputStream *read_stream = g_file_read(symlink_to_read, NULL, NULL);

    gssize read;
    char temp[1000];

    while(TRUE) {
        read = g_input_stream_read(G_INPUT_STREAM(read_stream), temp, G_N_ELEMENTS(temp) - 1, NULL, NULL);
        if(read <= 0) {
            break;
        }
    }

    g_object_unref(read_stream);
    g_object_unref(symlink_to_read);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}
