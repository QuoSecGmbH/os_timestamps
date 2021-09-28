#include "p_gio_delete.h"

/*
 * Deletes a empty file in a directory
 */
struct profile_info_struct* profile_gio_delete_lastFile_empty(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file_to_delete = misc_concat_ensure_file_exists(path_dir, "empty_file_to_delete", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file_to_delete);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file_to_delete = g_file_new_for_path(path_file_to_delete);
    gboolean isDelete = g_file_delete(file_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(file_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * Deletes a file that is not empty
 */
struct profile_info_struct* profile_gio_delete_lastFile_notEmpty(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file_to_delete = misc_concat_ensure_file_exists_filled(path_dir, "not_empty_file_to_delete", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);


    char** watch_array = misc_char_array2(path_dir, path_file_to_delete);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file_to_delete = g_file_new_for_path(path_file_to_delete);
    gboolean isDelete = g_file_delete(file_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(file_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * Delete symbolic link
 */
struct profile_info_struct* profile_gio_delete_symlink(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_file/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_symlink/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_symlink_dir, "symlink");

    int r = symlink("../directory_with_file/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_file, path_symlink, path_file_dir, path_symlink_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink_to_delete = g_file_new_for_path(path_symlink);
    gboolean isDelete = g_file_delete(symlink_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(symlink_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_delete_notLastFile_empty(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, (char*) "link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink_to_delete = g_file_new_for_path(path_link);
    gboolean isDelete = g_file_delete(symlink_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(symlink_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_delete_notLastFile_notEmpty(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, (char*) "link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink_to_delete = g_file_new_for_path(path_link);
    gboolean isDelete = g_file_delete(symlink_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(symlink_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}


/*
 * Delete a empty directory
 */
struct profile_info_struct* profile_gio_delete_directory(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_directory_to_delete = misc_concat_ensure_dir_exists(path_dir, "directory_to_delete/", 0, 0, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_directory_to_delete);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *directory_to_delete = g_file_new_for_path(path_directory_to_delete);
    gboolean isDelete = g_file_delete(directory_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(directory_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * removes a symbolic link pointing to a directory
 */
struct profile_info_struct* profile_gio_delete_directory_symlink(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_directory_with_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_directory_with_link_to_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_symlink_to_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_dir = misc_concat_ensure_dir_exists(path_directory_with_dir, "dir/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_directory_with_link_to_dir, "symlink");

    int r = symlink("../directory_with_dir/dir/", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_to_dir, path_symlink, path_directory_with_dir, path_directory_with_link_to_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink_to_delete = g_file_new_for_path(path_symlink);
    gboolean isDelete = g_file_delete(symlink_to_delete, NULL, NULL);

    g_assert_true(isDelete);
    g_object_unref(symlink_to_delete);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}
