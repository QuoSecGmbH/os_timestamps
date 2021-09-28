#include "p_gio_create.h"

struct profile_info_struct* profile_gio_create_file(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "new_file");
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_new);
    g_file_create(file, G_FILE_CREATE_PRIVATE, NULL, NULL);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_create_symlink_to_file(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_file/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_symlink/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "new_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_file, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink = g_file_new_for_path(path_symlink);
    char *symlink_value = "../file_dir/new_file";
    gboolean isCreate = g_file_make_symbolic_link(symlink, symlink_value, NULL, NULL);

    g_assert_true(isCreate);
    g_object_unref(symlink);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_create_file_into_symlink_dir(testenv_struct* env) {
    char* path_base = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir = misc_concat_ensure_dir_exists(path_base, "dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_link_to_dir = misc_concat(path_base, "symlink");
    char* path_new = misc_concat(path_link_to_dir, "/file");
    misc_nanosleep(ns_after_open);

    int r = symlink("dir/", path_link_to_dir);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array3(path_dir, path_link_to_dir, path_new);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_new);
    g_file_create(file, G_FILE_CREATE_PRIVATE, NULL, NULL);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_create_directory(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "new_dir/");
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_new);
    g_file_make_directory(file, NULL, NULL);
    g_object_unref(file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

struct profile_info_struct* profile_gio_create_symlink_to_dir(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_directory_with_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_directory_with_symlink = misc_concat_ensure_dir_exists(path_dir, "directory_with_link/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_new = misc_concat_ensure_dir_exists(path_directory_with_dir, "new_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_directory_with_symlink, "symlink");
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_new, path_symlink, path_directory_with_dir, path_directory_with_symlink);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *symlink = g_file_new_for_path(path_symlink);
    char *symlink_value = "../directory_with_dir/new_dir/";
    gboolean isCreate = g_file_make_symbolic_link(symlink, symlink_value, NULL, NULL);

    g_assert_true(isCreate);
    g_object_unref(symlink);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}
