#ifndef POS_FILEACCESS_C
#define POS_FILEACCESS_C

#include "pos_fileaccess.h"

struct profile_info_struct* profileos_fileaccess_interface(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path, "rb");
    char* buf = (char*) calloc(3, sizeof(char));
    int n_read = fread(buf, 1, 2, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_fileaccess_interface_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_filedir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../filedir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path_symlink, "rb");
    char* buf = (char*) calloc(3, sizeof(char));
    int n_read = fread(buf, 1, 2, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}


struct profile_info_struct* profileos_fileaccess_utilities(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "cat file > /dev/null";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_fileaccess_utilities_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_filedir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../filedir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "cat linkdir/symlink > /dev/null";
    
    char** watch_array = misc_char_array4(path, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_symlink_readlink_interface(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_filedir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../filedir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    enum { BUFFERSIZE = 1024 };
    char buf_link[BUFFERSIZE];
    ssize_t len = readlink(path_symlink, buf_link, sizeof(buf_link)-1);

    if (len == -1) {
        log_warning(env->output_file, env->error_file, "%s - %s: %d", __func__, "error reading symlink", errno);
    }
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_symlink_readlink_utilities(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_filedir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../filedir/file", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "readlink linkdir/symlink > /dev/null";
    
    char** watch_array = misc_char_array4(path, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_symlink_readlink_interface_dir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dirdir = misc_concat_ensure_dir_exists(path_dir, "dirdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dirdir, "dir/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../dirdir/dir/", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path, path_symlink, path_dirdir, path_linkdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    enum { BUFFERSIZE = 1024 };
    char buf_link[BUFFERSIZE];
    ssize_t len = readlink(path_symlink, buf_link, sizeof(buf_link)-1);

    if (len == -1) {
        log_warning(env->output_file, env->error_file, "%s - %s: %d", __func__, "error reading symlink", errno);
    }
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_symlink_readlink_utilities_dir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dirdir = misc_concat_ensure_dir_exists(path_dir, "dirdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dirdir, "dir/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../dirdir/dir/", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "readlink linkdir/symlink > /dev/null";
    
    char** watch_array = misc_char_array4(path, path_symlink, path_dirdir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

#endif
