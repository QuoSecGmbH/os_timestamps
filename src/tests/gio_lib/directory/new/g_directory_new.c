#include "g_directory_new.h"

int check_gio_g_file_make_directory(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path) {
    char* parent_dir = misc_concat_ensure_dir_exists(dir_path, "gio.directory.new.g_make_directory", 0,
            0, output_file, error_file, __func__);

    GFile *root;
    GFile *child;
    char *target_path;

    root = g_file_new_for_path(parent_dir);
    child = g_file_get_child(root, "g_dir");

    g_assert_true (child != NULL);

    struct timespec* ts_before = current_time_ns_fslike_osspecific();

    g_file_make_directory (child, NULL, NULL);
    target_path = g_file_get_path (child);

    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(target_path);

    int result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file,
            __func__, ts_before, ts_after, file_stat);

    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);

    g_object_unref(root);
    g_object_unref(child);

    free(parent_dir);
    free(ts_before);
    free(ts_after);
    free(file_stat);

    return result;
}

int check_gio_g_file_make_directory_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path) {
    char* parent_dir = misc_concat_ensure_dir_exists(dir_path, "gio.directory.new.g_make_directory", 0,
                                                     0, output_file, error_file, __func__);

    GFile *root;
    GFile *child;
    char *target_path;

    root = g_file_new_for_path(parent_dir);
    child = g_file_get_child (root, "g_dir");

    g_assert_true (child != NULL);

    g_file_make_directory (child, NULL, NULL);
    target_path = g_file_get_path (child);

    struct stat_macb* file_stat = get_path_timestamps(target_path);

    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 ||
            misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0) {
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }

    g_object_unref(root);
    g_object_unref(child);

    free(parent_dir);
    free(file_stat);

    return result;
}


