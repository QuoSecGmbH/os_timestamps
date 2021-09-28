#include "p_qt_copy.h"

/*
 * copy a file to a new file that does not yet exist
 */
struct profile_info_struct* profile_qt_copy_file_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path,
                                                   misc_concat(const_cast<char *>(__func__), "/"),
                                                   0, 0, env->output_file, env->error_file,
                                                   __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/",
                                                       0, 0, env->output_file, env->error_file,
                                                       __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/",
                                                       0, 0, env->output_file, env->error_file,
                                                       __func__);

    char* path_file_to_copy = misc_concat_ensure_file_exists_filled(path_src_dir,
                                                                    "src_file", 10, s_0s,
                                                                    ns_after_open, env->output_file, env->error_file,
                                                                    __func__);
    char* path_dst_file = misc_concat(path_dst_dir, "dst_file");

    char** watch_array = misc_char_array4(path_file_to_copy, path_src_dir, path_dst_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile().copy(path_file_to_copy, path_dst_file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);

    return pi;
}

/*
 * copy a file to an existing one
 * If a file with the name newName already exists, copy() returns false (i.e., QFile will not overwrite it).
 */