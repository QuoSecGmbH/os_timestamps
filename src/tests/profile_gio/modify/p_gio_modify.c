#include "p_gio_modify.h"


/*
 * g_file_replace ()
 * Returns an output stream for overwriting the file
 * If the file doesn't exist, it will be created
 */
struct profile_info_struct* profile_gio_modify_file_replace(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
  
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    

    GFile *file = g_file_new_for_path(path);
//     TRUE: gboolean make_backup, but it does not seem to make a difference
//     GFileOutputStream *write_stream = g_file_replace(file, NULL, TRUE, G_FILE_CREATE_PRIVATE, NULL, NULL);
    GFileOutputStream *write_stream = g_file_replace(file, NULL, NULL, G_FILE_CREATE_PRIVATE, NULL, NULL);
    char buf[50] = "g_file_replace file test";

    g_output_stream_write(G_OUTPUT_STREAM(write_stream), buf, strlen(buf), NULL, NULL);
    g_output_stream_close(G_OUTPUT_STREAM(write_stream), NULL, NULL);

    g_object_unref(write_stream);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_modify_symlink_replace(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../file_dir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_symlink);
//     TRUE: gboolean make_backup, but it does not seem to make a difference
//     GFileOutputStream *write_stream = g_file_replace(file, NULL, TRUE, G_FILE_CREATE_PRIVATE, NULL, NULL);
    GFileOutputStream *write_stream = g_file_replace(file, NULL, NULL, G_FILE_CREATE_PRIVATE, NULL, NULL);
    char buf[50] = "g_file_replace symlink test";

    g_output_stream_write(G_OUTPUT_STREAM(write_stream), buf, strlen(buf), NULL, NULL);
    g_output_stream_close(G_OUTPUT_STREAM(write_stream), NULL, NULL);

    g_object_unref(write_stream);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * g_file_append_to ()
 * Gets an output stream for appending data to the file.
 * If the file doesn't already exist it is created.
 */
struct profile_info_struct* profile_gio_modify_file_append(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    

    GFile *file = g_file_new_for_path(path);
    GFileOutputStream *write_stream = g_file_append_to(file, G_FILE_CREATE_PRIVATE, NULL, NULL);
    char buf[50] = "g_file_append file test";

    g_output_stream_write(G_OUTPUT_STREAM(write_stream), buf, strlen(buf), NULL, NULL);
    g_output_stream_close(G_OUTPUT_STREAM(write_stream), NULL, NULL);

    g_object_unref(write_stream);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_modify_symlink_append(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../file_dir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_symlink);
    GFileOutputStream *write_stream = g_file_append_to(file, G_FILE_CREATE_PRIVATE, NULL, NULL);
    char buf[50] = "g_file_append symlink test";

    g_output_stream_write(G_OUTPUT_STREAM(write_stream), buf, strlen(buf), NULL, NULL);
    g_output_stream_close(G_OUTPUT_STREAM(write_stream), NULL, NULL);

    g_object_unref(write_stream);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * g_file_open_readwrite ()
 * Opens an existing file for reading and writing.
 * The result is a GFileIOStream that can be used to read and write the contents of the file.
 * GFileIOStream --> GIOStream
 */
struct profile_info_struct* profile_gio_modify_file_open(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_file);
    GFileIOStream *read_write_stream = g_file_open_readwrite(file, NULL, NULL);
    char buf[50] = "g_file_open_readwrite file test";

    GOutputStream *write_stream = g_io_stream_get_output_stream(G_IO_STREAM(read_write_stream));
    g_output_stream_write(write_stream, buf, strlen(buf), NULL, NULL);
    g_output_stream_close(write_stream, NULL, NULL);

    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_modify_symlink_open(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../file_dir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_symlink);
    GFileIOStream *read_write_stream = g_file_open_readwrite(file, NULL, NULL);
    char buf[50] = "g_file_open_readwrite symlink test";

    GOutputStream *write_stream = g_io_stream_get_output_stream(G_IO_STREAM(read_write_stream));
    g_output_stream_write(write_stream, buf, strlen(buf), NULL, NULL);
    g_output_stream_close(write_stream, NULL, NULL);

    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}
