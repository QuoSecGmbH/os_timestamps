#ifndef POS_FILECREATION_C
#define POS_FILECREATION_C

#include "pos_filecreation.h"

struct profile_info_struct* profileos_filecreation_interface(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newfile");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path_new, "wb");
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_interface_newhardlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_filedir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_hardlink = misc_concat(path_linkdir, "hardlink");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path_new, path_hardlink, path_filedir, path_linkdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    int r = link(path_new, path_hardlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s, errno: %d", __func__, "error creating link", errno);
        return 1;
    }
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_interface_dir(testenv_struct* env){   
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newdir/");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    mkdir(path_new, 0700);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_interface_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_filedir, "newfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path_new, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    int r = symlink("../filedir/newfile", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s, errno: %d", __func__, "error creating link", errno);
        return 1;
    }
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_interface_intosymlinkdir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_dir = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_link = misc_concat(path_dir, "symlink");
    char* path_new = misc_concat(path_dir_link, "/file");
    misc_nanosleep(ns_after_open);
        
    int r = symlink("dir/", path_dir_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array3(path_dir_dir, path_dir_link, path_new);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path_new, "wb");
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_interface_symlink_dir(testenv_struct* env){   
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dirdir = misc_concat_ensure_dir_exists(path_dir, "dirdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_dir_exists(path_dirdir, "newdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path_new, path_symlink, path_dirdir, path_linkdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    int r = symlink("../dirdir/newdir/", path_symlink);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newfile");
    misc_nanosleep(ns_after_open);
    
    char* command = "touch newfile";
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities_newhardlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_filedir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_hardlink = misc_concat(path_linkdir, "hardlink");
    misc_nanosleep(ns_after_open);
    
    char* command = "ln filedir/file linkdir/hardlink";
    
    char** watch_array = misc_char_array4(path_new, path_hardlink, path_filedir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities_dir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newdir/");
    misc_nanosleep(ns_after_open);
    
    char* command = "mkdir newdir";
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_filedir = misc_concat_ensure_dir_exists(path_dir, "filedir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_filedir, "newfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    char* command = "ln -s ../filedir/newfile linkdir/symlink";
    
    char** watch_array = misc_char_array4(path_new, path_symlink, path_filedir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities_intosymlinkdir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_dir = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_link = misc_concat(path_dir, "symlink");
    char* path_new = misc_concat(path_dir_link, "/file");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("dir/", path_dir_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "touch symlink/file";
    
    char** watch_array = misc_char_array3(path_dir_dir, path_dir_link, path_new);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities_symlink_dir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dirdir = misc_concat_ensure_dir_exists(path_dir, "dirdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_dir, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_dir_exists(path_dirdir, "newdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_symlink = misc_concat(path_linkdir, "symlink");
    misc_nanosleep(ns_after_open);
    
    char* command = "ln -s ../dirdir/newdir/ linkdir/symlink";
    
    char** watch_array = misc_char_array4(path_new, path_symlink, path_dirdir, path_linkdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

#endif
