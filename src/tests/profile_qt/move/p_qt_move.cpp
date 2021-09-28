#include "p_qt_move.h"

/*
 * move a file to a new file that does not yet exist
 */
struct profile_info_struct* profile_qt_move_file_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_file_to_move = misc_concat_ensure_file_exists_filled(path_src_dir, "src_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_dst_file = misc_concat(path_dst_dir, "dst_file");

    char** watch_array = misc_char_array4(path_file_to_move, path_src_dir, path_dst_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile().rename(path_file_to_move, path_dst_file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * move a file to an existing one ?
 * bool QFile::rename(const QString &newName)
 *
 * Renames the file currently specified by fileName() to newName. Returns true if successful; otherwise returns false.
 * If a file with the name newName already exists, rename() returns false (i.e., QFile will not overwrite it).
 * The file is closed before it is renamed.
 * If the rename operation fails, Qt will attempt to copy this file's contents to newName, and then remove this file, keeping only newName.
 * If that copy operation fails or this file can't be removed, the destination file newName is removed to restore the old state.
 *
 */
struct profile_info_struct* profile_qt_move_file_existing(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_src_file = misc_concat_ensure_file_exists_filled(path_src_dir, "src_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_to_dst_file = misc_concat_ensure_file_exists_filled(path_dst_dir, "dst_file", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array4(path_to_src_file, path_src_dir, path_to_dst_file, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QFile().rename(path_to_src_file, path_to_dst_file);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);
    return pi;
}

/*
 * move a directory to a new directory that does not yet exist
 */
struct profile_info_struct* profile_qt_move_directory_new(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_src_directory = misc_concat_ensure_dir_exists(path_src_dir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_to_src_directory, "src_dir_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char* path_to_dst_directory = misc_concat(path_dst_dir, "dst");

    char** watch_array = misc_char_array4(path_to_src_directory, path_src_dir, path_to_dst_directory, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QDir().rename(path_to_src_directory, path_to_dst_directory);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}

/*
 * move a directory to an existing one ? // work in UI (Nautilus) with copy + delete
 * bool QDir::rename(const QString &oldName, const QString &newName)
 *
 * Renames a file or directory from oldName to newName, and returns true if successful; otherwise returns false.
 * On most file systems, rename() fails only if oldName does not exist, or if a file with the new name already exists.
 * However, there are also other reasons why rename() can fail.
 * If oldName is a file (not a directory) that can't be renamed right away, Qt will try to copy oldName to newName and remove oldName.
 */
struct profile_info_struct* profile_qt_move_directory_existing(testenv_struct* env) {
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(const_cast<char *>(__func__), "/"), 0, 0, env->output_file, env->error_file, __func__);

    char* path_src_dir = misc_concat_ensure_dir_exists(path_dir, "src_dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dst_dir = misc_concat_ensure_dir_exists(path_dir, "dst_dir/", 0, 0, env->output_file, env->error_file, __func__);

    char* path_to_src_directory = misc_concat_ensure_dir_exists(path_src_dir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_to_src_directory, "src_dir_file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char* path_to_dst_directory = misc_concat_ensure_dir_exists(path_dst_dir, "dst/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);

    char** watch_array = misc_char_array4(path_to_src_directory, path_src_dir, path_to_dst_directory, path_dst_dir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);

    QDir().rename(path_to_src_directory, path_to_dst_directory);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, ns_DELAY);

    return pi;
}
