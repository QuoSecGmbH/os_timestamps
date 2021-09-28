#include "p_qt_modify.h"

/*
 * QIODevice::WriteOnly
 * Returns an output stream for overwriting the file
 * this mode implies Truncate unless combined with ReadOnly, Append or NewOnly.
 */
struct profile_info_struct* profile_gio_modify_file_writeOnly(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "File open in mode ReadWrite" << endl;
        file.close();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_modify_symlink_writeOnly(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../file_dir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 0;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file(path_symlink);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "File open in mode WriteOnly" << endl;
        file.close();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}


/*
 * QIODevice::Append
 * The device is opened in append mode so that all data is written to the end of the file.
 */
struct profile_info_struct* profile_qt_modify_file_append(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file(path);
    if(file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "File open in mode Append" << endl;
        file.close();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_modify_symlink_append(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../file_dir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 0;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file(path_symlink);
    if(file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "File open in mode Append" << endl;
        file.close();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}


/*
 * QIODevice::ReadWrite
 * The device is open for reading and writing.
 */
struct profile_info_struct* profile_qt_modify_file_readWrite(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file(path_file);
    if(file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "File open in mode ReadWrite" << endl;
        file.close();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_modify_symlink_readWrite(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_link_dir, "symlink");
    misc_nanosleep(ns_after_open);

    int r = symlink("../file_dir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 0;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array4(path, path_symlink, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile file(path_symlink);
    if(file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "File open in mode ReadWrite" << endl;
        file.close();
    }

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}
