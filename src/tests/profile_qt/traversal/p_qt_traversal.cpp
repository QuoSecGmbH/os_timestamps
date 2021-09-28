#include "p_qt_traversal.h"

struct profile_info_struct* profile_qt_traversal_directory(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array1(path);
    int watch_num = 1;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    bool isTraversal = QDir().cd(path);
    Q_ASSERT(isTraversal);
    misc_nanosleep(ns_after_open);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profile_qt_traversal_directory_symlink(testenv_struct* env) {
    char* path_base = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir = misc_concat_ensure_dir_exists(path_base, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_base, "symlink");

    int r = symlink("dir/", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 0;
    }
    misc_nanosleep(ns_after_open);

    char** watch_array = misc_char_array2(path_dir, path_link);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    bool isTraversal = QDir().cd(path_link);
    Q_ASSERT(isTraversal);
    misc_nanosleep(ns_after_open);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}
