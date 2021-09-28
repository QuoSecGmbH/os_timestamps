#include "p_qt_change.h"

struct profile_info_struct* profile_qt_change_chmod_file(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path_file);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    bool isSet = QFile(path_file).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
    Q_ASSERT(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_change_chmod_symlink(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_dir = misc_concat_ensure_dir_exists(path_dir, "file_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link_dir = misc_concat_ensure_dir_exists(path_dir, "link_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file = misc_concat_ensure_file_exists_filled(path_file_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char* path_link = misc_concat(path_link_dir, "symlink");
    int r = symlink("../file_dir/file", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return nullptr;
    }
    misc_nanosleep(ns_after_open);


    char** watch_array = misc_char_array4(path_file, path_link, path_file_dir, path_link_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    bool isSet = QFile(path_link).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
    Q_ASSERT(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

struct profile_info_struct* profile_qt_change_chmod_dir(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    bool isSet = QFile(path).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
    Q_ASSERT(isSet);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}


/*
 * https://stackoverflow.com/questions/41733820/set-file-ownergroup-in-linux-using-qt-c#:~:text=1%20Answer&text=Setting%20file%20permissions%20can%20be,chown()%20function%20from%20unistd.
 *
 * Setting file permissions can be done by QFile::setPermissions method instead of using native chmod function,
 * but Qt has not equivalent of chown. You should use chown() function from unistd.h Look here.
 */

