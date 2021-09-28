#include "p_gio_change.h"

struct profile_info_struct* profile_gio_change_chmod_file(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_file);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE, 0700);

    gboolean check = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE);
    g_assert_true(check);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chown_file(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    uid_t uid = -1;
    gid_t gid = CHOWN_GROUP_GID;

    GFile *file = g_file_new_for_path(path_file);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID, uid);
    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID, gid);

    gboolean checkUID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID);
    gboolean checkGID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID);
    g_assert_true(checkUID);
    g_assert_true(checkGID);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chmod_symlink(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char* path_link = misc_concat(path_link_dir, "symlink");
    int r = symlink("../file_dir/file", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);


    char** watch_array = misc_char_array4(path_file, path_link, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *link = g_file_new_for_path(path_link);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE, 0700);

    gboolean check = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE);
    g_assert_true(check);

    gboolean isSet = g_file_set_attributes_from_info(link, info, G_FILE_QUERY_INFO_NONE, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chown_symlink(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char* path_link = misc_concat(path_link_dir, "symlink");
    int r = symlink("../file_dir/file", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_link, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    uid_t uid = -1;
    gid_t gid = CHOWN_GROUP_GID;

    GFile *file = g_file_new_for_path(path_link);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID, uid);
    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID, gid);

    gboolean checkUID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID);
    gboolean checkGID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID);
    g_assert_true(checkUID);
    g_assert_true(checkGID);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NONE, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chmod_symlink_notFollow(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_link_dir, "symlink");

    int r = symlink("../file_dir/file", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);


    char** watch_array = misc_char_array4(path, path_link, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path_link);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE, 0770);

    gboolean check = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE);
    g_assert_true(check);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chown_symlink_notFollow(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_link_dir, "symlink");
    int r = symlink("../file_dir/file", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_link, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    uid_t uid = -1;
    gid_t gid = CHOWN_GROUP_GID;

    GFile *file = g_file_new_for_path(path_link);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID, uid);
    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID, gid);

    gboolean checkUID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID);
    gboolean checkGID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID);
    g_assert_true(checkUID);
    g_assert_true(checkGID);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chmod_dir(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    GFile *file = g_file_new_for_path(path);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE, 0700);

    gboolean check = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_MODE);
    g_assert_true(check);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
    g_assert_true(isSet);


    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_gio_change_chown_dir(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    uid_t uid = -1;
    gid_t gid = CHOWN_GROUP_GID;

    GFile *file = g_file_new_for_path(path);
    GFileInfo *info = g_file_info_new();

    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID, uid);
    g_file_info_set_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID, gid);

    gboolean checkUID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_UID);
    gboolean checkGID = g_file_info_get_attribute_uint32(info, G_FILE_ATTRIBUTE_UNIX_GID);
    g_assert_true(checkUID);
    g_assert_true(checkGID);

    gboolean isSet = g_file_set_attributes_from_info(file, info, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
    g_assert_true(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}
