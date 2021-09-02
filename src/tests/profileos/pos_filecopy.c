#ifndef POS_FILECOPY_C
#define POS_FILECOPY_C

#include "pos_filecopy.h"

struct profile_info_struct* profileos_filecopy_interface_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* srcFile = fopen(path, "rb");
    FILE* dstFile = fopen(path_new,   "wb");

    char ch = fgetc(srcFile);
    while (ch != EOF) {
        fputc(ch, dstFile);
        ch = fgetc(srcFile);
    }
    
    fclose(srcFile);
    fclose(dstFile);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_volumefilecopy_interface_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir_volume, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* srcFile = fopen(path, "rb");
    FILE* dstFile = fopen(path_new,   "wb");

    char ch = fgetc(srcFile);
    while (ch != EOF) {
        fputc(ch, dstFile);
        ch = fgetc(srcFile);
    }
    
    fclose(srcFile);
    fclose(dstFile);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecopy_interface_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dstdir, "dst", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* srcFile = fopen(path, "rb");
    FILE* dstFile = fopen(path_new,   "wb");

    char ch = fgetc(srcFile);
    while (ch != EOF) {
        fputc(ch, dstFile);
        ch = fgetc(srcFile);
    }
    
    fclose(srcFile);
    fclose(dstFile);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_volumefilecopy_interface_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir_volume, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dstdir, "dst", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* srcFile = fopen(path, "rb");
    FILE* dstFile = fopen(path_new,   "wb");

    char ch = fgetc(srcFile);
    while (ch != EOF) {
        fputc(ch, dstFile);
        ch = fgetc(srcFile);
    }
    
    fclose(srcFile);
    fclose(dstFile);

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filecopy_utilities_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char* command = "cp srcdir/src dstdir/dst";
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_volumefilecopy_utilities_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir_volume, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char* command = misc_concat(misc_concat(misc_concat("cp ", path), " "), path_new);
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, NULL, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecopy_utilities_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dstdir, "dst", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "cp srcdir/src dstdir/dst";
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_volumefilecopy_utilities_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir_volume, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_srcdir, "src", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dstdir, "dst", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = misc_concat(misc_concat(misc_concat("cp ", path), " "), path_new);
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, NULL, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecopy_utilities_dir_new_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_srcdir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path, "dirfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char* command = "cp -r srcdir/src dstdir/dst";
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_volumefilecopy_utilities_dir_new_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir_volume, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_srcdir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path, "dirfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char* command = misc_concat(misc_concat(misc_concat("cp -r ", path), " "), path_new);
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, NULL, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecopy_utilities_dir_new_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_srcdir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char* command = "cp -r srcdir/src dstdir/dst";
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_volumefilecopy_utilities_dir_new_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_volume = misc_concat_ensure_dir_exists(env->dir_path_volume, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_dstdir = misc_concat_ensure_dir_exists(path_dir_volume, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_srcdir, "src/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dstdir, "dst");
    
    char* command = misc_concat(misc_concat(misc_concat("cp -r ", path), " "), path_new);
    
    char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, NULL, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

// struct profile_info_struct* profileos_filecopy_utilities_dir_existing(testenv_struct* env){
//     char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
//     char* path_srcdir = misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, env->output_file, env->error_file, __func__);
//     char* path_dstdir = misc_concat_ensure_dir_exists(path_dir, "dstdir/", 0, 0, env->output_file, env->error_file, __func__);
//     char* path = misc_concat_ensure_dir_exists(path_srcdir, "src", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
//     char* path_new = misc_concat_ensure_dir_exists(path_dstdir, "dst", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
//     
//     char* command = "cp -r srcdir/src dstdir/dst";
//     
//     char** watch_array = misc_char_array4(path, path_srcdir, path_new, path_dstdir);
//     int watch_num = 4;
//     
//     struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
//     
//     return pi;
// }

#endif
