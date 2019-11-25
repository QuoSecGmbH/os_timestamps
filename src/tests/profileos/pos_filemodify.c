#ifndef POS_FILEMODIFY_C
#define POS_FILEMODIFY_C

#include "pos_filemodify.h"

struct profile_info_struct* profileos_filemodify_interface_wb(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path, "wb");
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_interface_rp(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path, "r+");
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_interface_a(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path, "a");
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_utilities(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "echo a >> file";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_interface_wb_symlink(testenv_struct* env){
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
    
    FILE* fd = fopen(path_symlink, "wb");
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_interface_rp_symlink(testenv_struct* env){
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
    
    FILE* fd = fopen(path_symlink, "r+");
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_interface_a_symlink(testenv_struct* env){
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
    
    FILE* fd = fopen(path_symlink, "a");
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, fd);
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filemodify_utilities_symlink(testenv_struct* env){
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
    
    char* command = "echo a >> linkdir/symlink";
    
    char** watch_array = misc_char_array4(path, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

#endif
