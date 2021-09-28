#include "p_qt_access.h"

struct profile_info_struct* profile_qt_access_file_readOnly(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file_to_read = misc_concat_ensure_file_exists_filled(path_dir, "file_to_read", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file_to_read);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file_to_read(path_file_to_read);

    if(!file_to_read.open(QIODevice::ReadOnly)) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening file");
        return nullptr;
    }

    while (!file_to_read.atEnd()) {
        QByteArray line = file_to_read.readLine();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_access_file_readWrite(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file_to_read = misc_concat_ensure_file_exists_filled(path_dir, "file_to_read", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file_to_read);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file_to_read(path_file_to_read);

    if(!file_to_read.open(QIODevice::ReadWrite)) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening file");
        return nullptr;
    }

    while (!file_to_read.atEnd()) {
        QByteArray line = file_to_read.readLine();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_access_symlink_readOnly(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_file/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_symlink/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_symlink_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../directory_with_file/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return nullptr;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_file, path_symlink, path_file_dir, path_symlink_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file_to_read(path_symlink);

    if(!file_to_read.open(QIODevice::ReadOnly)) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening file");
        return nullptr;
    }

    while (!file_to_read.atEnd()) {
        QByteArray line = file_to_read.readLine();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_access_symlink_readWrite(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_file/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink_dir = misc_concat_ensure_dir_exists(path_dir, "directory_with_symlink/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_symlink_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../directory_with_file/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 0;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path_file, path_symlink, path_file_dir, path_symlink_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file_to_read(path_symlink);

    if(!file_to_read.open(QIODevice::ReadWrite)) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening file");
        return nullptr;
    }

    while (!file_to_read.atEnd()) {
        QByteArray line = file_to_read.readLine();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}