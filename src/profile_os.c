#ifndef PROFILE_OS_C
#define PROFILE_OS_C

#include "profile_os.h"

int PROFILE_TREAT_DELAY_AS_COMMAND = 0;
int OPTION_VOLUME_FILE_MOVE = 0;
int OPTION_QUICK = 0;
gid_t CHOWN_GROUP_GID = -1;
char* mounted = NULL;

void print_usage(){
    fprintf(stderr, "Usage: ./profile_os [options]\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -q, --quick            Skip some operations (on symlink, on hardlink...)\n");
    fprintf(stderr, "  -v, --verbose         \n");
    fprintf(stderr, "  -g, --guid-chown GID   GID to be used in chown tests (you should be able to do a chown :GID file) \n");
//     fprintf(stderr, "  --timewait / -t TIMEWAIT\n");
    fprintf(stderr, "  -m, --mounted MNT/     Path of the mounted filesystem for tests on Volume Copy\n");
    fprintf(stderr, "  -d, --nodelay          Treat delays as command updates\n");
}

int main(int argc, char *argv[]) {
//     char verbose = 0;
    char quick = 0;
    char* pwd_dir = NULL;
    int watch_num = 0;
    char** watch_array;
    char* precommand = NULL;
    time_t wait_pre_s = 0;
    
    time_t wait_cmd_s = 0;
    
    int c;
    while (1) {
        static struct option long_options[] =
            {
            {"verbose", no_argument,       0, 'v'},
            {"nodelay", no_argument,       0, 'd'},
//             {"timewait", required_argument, 0, 't'},
            {"mounted", required_argument, 0, 'm'},
            {"guid-chown", required_argument, 0, 'g'},
            {"quick", required_argument, 0, 'q'},
            {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "vdm:g:q",
                        long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
            {
            case 'v': {
                VERBOSE = 1; 
                break;
            }            
            case 'd': {
                PROFILE_TREAT_DELAY_AS_COMMAND = 1; 
                break;
            }
            case 'q': {
                OPTION_QUICK = 1; 
                break;
            }
            case 'm': {
                OPTION_VOLUME_FILE_MOVE = 1;
                mounted = optarg;
                break;
        }
            case 'g': {
                CHOWN_GROUP_GID = (gid_t) atoi(optarg);
                break;
        }
            default:
                fprintf(stderr, "Unknown argument.\n");
                print_usage();
                exit(EXIT_FAILURE);
            }
        }
        
    run_profileos();
}

int run_profileos(){
    FILE* csv_file_brief = log_open_csv("os_profile_results.csv");
    FILE* csv_file_flags = log_open_csv("os_profile_flags.csv");
    FILE* output_file = stdout;
    FILE* error_file = stderr;
  
    int i;
    char* dir_base_path = "tmp_os_profile";
    char* dir_path = NULL;
    char* dir_path_volume = NULL;
    for (i = 0; i <= 99; i++){
        char* buf = (char*) calloc(sizeof(char), strlen(dir_base_path)+6);
        sprintf(buf, "%s_%02d/", dir_base_path, i);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        if (stat(buf, attr) == -1) {
            mkdir(buf, 0700);
            dir_path = buf;
            if (OPTION_VOLUME_FILE_MOVE){
                struct stat* attr_volume = (struct stat*) calloc(sizeof(struct stat), 1);
                dir_path_volume = misc_concat(mounted, buf);
                if (stat(dir_path_volume, attr) == -1) {
                    mkdir(dir_path_volume, 0700);
                }
                else {
                    log_error(output_file, error_file, "Dir %s already exists, please remove similar dir before relaunching", dir_path_volume);
                    return 1;
                }
            }
            free(attr);
            break;
        }
        free(buf);
        free(attr);
    }
    
    if (dir_path == NULL){
        log_error(output_file, error_file, "%s", "Impossible to find suitable directory for tests, exiting.");
        return 1;
    }
    log_info(output_file, error_file, "Directory for tests is: %s", dir_path);
    if (OPTION_VOLUME_FILE_MOVE){
        log_info(output_file, error_file, "Volume path is: %s", dir_path_volume);
    }
    
    if (CHOWN_GROUP_GID == -1){
        log_warning(output_file, error_file, "Group GID to use for chown tests is unset (default: -1), tests using chown (PROFILE.OS.*.CHANGE.*) will probably fail. Set GID with -g option.");
    }
    
#ifndef __linux__
#ifndef __freebsd__
    current_time_setup_local_timemarker(output_file, error_file);
    current_time_setup_local_timemarkerdir(output_file, error_file);
#endif
#endif
    
    testenv_struct* test_env = testenv_alloc_csv(csv_file_brief, output_file, error_file, dir_path, dir_path_volume, csv_file_flags);
    
    log_csv_add_line(csv_file_brief, 2, "Reference", "MACB");
    log_csv_add_line(csv_file_flags, 4, "Description", "File", "M/A/C/B", "Flag");

    group_profileos_filerename(test_env);
    group_profileos_dirrename(test_env);
    group_profileos_localfilemove(test_env);
    group_profileos_localdirmove(test_env);
    if (OPTION_VOLUME_FILE_MOVE){
        group_profileos_volumefilemove(test_env);
        group_profileos_volumedirmove(test_env);
    }
    group_profileos_filecopy_new(test_env);
    group_profileos_filecopy_existing(test_env);
    if (OPTION_VOLUME_FILE_MOVE){
        group_profileos_volumefilecopy_new(test_env);
        group_profileos_volumefilecopy_existing(test_env);
    }
    
    group_profileos_dircopy_notempty(test_env);    
    if (OPTION_VOLUME_FILE_MOVE){
        group_profileos_volumedircopy_notempty(test_env);
    }
    if (!OPTION_QUICK){
        group_profileos_dircopy_empty(test_env);
        if (OPTION_VOLUME_FILE_MOVE){
        group_profileos_volumedircopy_empty(test_env);
        }
    }

    
    group_profileos_filecreation(test_env);
    if (!OPTION_QUICK){
        group_profileos_filecreation_newhardlink(test_env);
        group_profileos_filesymlink_creation(test_env);
        group_profileos_filecreation_intosymlinkdir(test_env);
    }
    group_profileos_dircreation(test_env);
    if (!OPTION_QUICK){
        group_profileos_dirsymlink_creation(test_env);
    }
    
    
    group_profileos_fileaccess(test_env);
    if (!OPTION_QUICK){
        group_profileos_fileaccess_symlink(test_env);
        group_profileos_symlink_readlink(test_env);
    }
    
    group_profileos_filemodify(test_env);
    if (!OPTION_QUICK){
        group_profileos_filemodify_symlink(test_env);
    }
    
    group_profileos_filechange(test_env);
    if (!OPTION_QUICK){
        group_profileos_symlinkchange(test_env);
        group_profileos_symlinkchange_nofollow(test_env);
    }
    group_profileos_dirchange(test_env);
    
    group_profileos_filedelete_last(test_env);
    group_profileos_filedelete_notlast(test_env);
    if (!OPTION_QUICK){
        group_profileos_filedelete_symlink(test_env);
    }
    group_profileos_dirdelete(test_env);
    if (!OPTION_QUICK){
        group_profileos_dirdelete_symlink(test_env);
    }
    
    group_profileos_dirlisting_notempty(test_env);
    if (!OPTION_QUICK){
        group_profileos_dirlisting_empty(test_env);
        group_profileos_dirlisting_symlink(test_env);
    }
    
    group_profileos_dirtraversal(test_env);
    if (!OPTION_QUICK){
        group_profileos_dirtraversal_symlink(test_env);
    }
   
    group_profileos_execute(test_env);
    if (!OPTION_QUICK){
        group_profileos_execute_symlink(test_env);
        group_profileos_execute_intosymlinkdir(test_env);
    }
   
//     free(test_env);
//     free(dir_path);
    
    log_close_csv(csv_file_brief);
    log_close_csv(csv_file_flags);
}

void group_profileos_filerename(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filerename_interface_new(env);
    struct profile_info_struct* pi2 = profileos_filerename_interface_existing(env);
    struct profile_info_struct* pi3 = profileos_filerename_utilities_new(env);
    struct profile_info_struct* pi4 = profileos_filerename_utilities_existing(env);
    
    char** mask = misc_char_array3("src", "dst", "dir/");
    process_profiles4(mask, "File Rename", "PROFILE.OS.FILE.RENAME", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_dirrename(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filerename_interface_dir_new(env);
    struct profile_info_struct* pi2 = profileos_filerename_interface_dir_existing(env);
    struct profile_info_struct* pi3 = profileos_filerename_utilities_dir_new(env);
    
    char** mask = misc_char_array3("src/", "dst/", "dir/");
    process_profiles3(mask, "Dir Rename", "PROFILE.OS.DIR.RENAME", __func__, env, pi1, pi2, pi3);
}

void group_profileos_localfilemove(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_localfilemove_interface_new(env);
    struct profile_info_struct* pi2 = profileos_localfilemove_interface_existing(env);
    struct profile_info_struct* pi3 = profileos_localfilemove_utilities_new(env);
    struct profile_info_struct* pi4 = profileos_localfilemove_utilities_existing(env);
    
    char** mask = misc_char_array4("src", "srcdir/", "dst", "dstdir/");
    process_profiles4(mask, "Local File Move", "PROFILE.OS.FILE.MV_LOCAL", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_localdirmove(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_localfilemove_interface_dir_new(env);
    struct profile_info_struct* pi2 = profileos_localfilemove_interface_dir_existing(env);
    struct profile_info_struct* pi3 = profileos_localfilemove_utilities_dir_new(env);
    
    char** mask = misc_char_array4("src/", "srcdir/", "dst/", "dstdir/");
    process_profiles3(mask, "Local Dir Move", "PROFILE.OS.DIR.MV_LOCAL", __func__, env, pi1, pi2, pi3);
}

void group_profileos_volumefilemove(testenv_struct* env){
    char** mask = misc_char_array4("src", "srcdir/", "dst", "dstdir/");
    
    // Linux, OpenBSD, FreeBSD: Interface "rename" does not work across file systemes (errno 18 - EXDEV 18 Invalid cross-device link), see: man 2 rename
    struct profile_info_struct* pi1 = profileos_volumefilemove_utilities_new(env);
    struct profile_info_struct* pi2 = profileos_volumefilemove_utilities_existing(env);
    process_profiles2(mask, "Volume File Move", "PROFILE.OS.FILE.MV_VOLUME", __func__, env, pi1, pi2);
}

void group_profileos_volumedirmove(testenv_struct* env){
    char** mask = misc_char_array4("src/", "srcdir/", "dst/", "dstdir/");
    
    // Linux, OpenBSD, FreeBSD: Interface "rename" does not work across file systemes (errno 18 - EXDEV 18 Invalid cross-device link), see: man 2 rename
    struct profile_info_struct* pi1 = profileos_volumefilemove_utilities_dir_new(env);
    process_profiles1(mask, "Volume Dir Move", "PROFILE.OS.DIR.MV_VOLUME", __func__, env, pi1);
}

void group_profileos_filecopy_new(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_interface_new(env);
    struct profile_info_struct* pi2 = profileos_filecopy_utilities_new(env);
    
    char** mask = misc_char_array4("src", "srcdir/", "dst", "dstdir/");
    process_profiles2(mask, "Local File Copy (new)", "PROFILE.OS.FILE.COPY_LOCAL.NEW", __func__, env, pi1, pi2);
}

void group_profileos_volumefilecopy_new(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_volumefilecopy_interface_new(env);
    struct profile_info_struct* pi2 = profileos_volumefilecopy_utilities_new(env);
    
    char** mask = misc_char_array4("src", "srcdir/", "dst", "dstdir/");
    process_profiles2(mask, "Volume File Copy (new)", "PROFILE.OS.FILE.COPY_VOLUME.NEW", __func__, env, pi1, pi2);
}

void group_profileos_filecopy_existing(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_interface_existing(env);
    struct profile_info_struct* pi2 = profileos_filecopy_utilities_existing(env);
    
    char** mask = misc_char_array4("src", "srcdir/", "dst", "dstdir/");
    process_profiles2(mask, "Local File Copy (existing)", "PROFILE.OS.FILE.COPY_LOCAL.EXISTING", __func__, env, pi1, pi2);
}

void group_profileos_volumefilecopy_existing(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_volumefilecopy_interface_existing(env);
    struct profile_info_struct* pi2 = profileos_volumefilecopy_utilities_existing(env);
    
    char** mask = misc_char_array4("src", "srcdir/", "dst", "dstdir/");
    process_profiles2(mask, "Volume File Copy (existing)", "PROFILE.OS.FILE.COPY_VOLUME.EXISTING", __func__, env, pi1, pi2);
}

void group_profileos_dircopy_notempty(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_utilities_dir_new_notempty(env);
    
    char** mask = misc_char_array4("src/", "srcdir/", "dst/", "dstdir/");
    process_profiles1(mask, "Local Dir Copy (new, notempty)", "PROFILE.OS.DIR.COPY_LOCAL.NEW.NOTEMPTY", __func__, env, pi1);
}

void group_profileos_volumedircopy_notempty(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_volumefilecopy_utilities_dir_new_notempty(env);
    
    char** mask = misc_char_array4("src/", "srcdir/", "dst/", "dstdir/");
    process_profiles1(mask, "Volume Dir Copy (new, notempty)", "PROFILE.OS.DIR.COPY_VOLUME.NEW.NOTEMPTY", __func__, env, pi1);
}

void group_profileos_dircopy_empty(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecopy_utilities_dir_new_empty(env);
    
    char** mask = misc_char_array4("src/", "srcdir/", "dst/", "dstdir/");
    process_profiles1(mask, "Local Dir Copy (new, empty)", "PROFILE.OS.DIR.COPY_LOCAL.NEW.EMPTY", __func__, env, pi1);
}

void group_profileos_volumedircopy_empty(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_volumefilecopy_utilities_dir_new_empty(env);
    
    char** mask = misc_char_array4("src/", "srcdir/", "dst/", "dstdir/");
    process_profiles1(mask, "Volume Dir Copy (new, empty)", "PROFILE.OS.DIR.COPY_VOLUME.NEW.EMPTY", __func__, env, pi1);
}

void group_profileos_filecreation(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities(env);
    
    char** mask = misc_char_array2("dir/", "newfile");
    process_profiles2(mask, "File Creation", "PROFILE.OS.FILE.NEW", __func__, env, pi1, pi2);
}

void group_profileos_filecreation_newhardlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface_newhardlink(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities_newhardlink(env);
    
    char** mask = misc_char_array4("file", "hardlink", "filedir/", "linkdir/");
    process_profiles2(mask, "Hardlink (to file) Creation", "PROFILE.OS.HARDLINK.FILE.NEW", __func__, env, pi1, pi2);
}

void group_profileos_filesymlink_creation(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities_symlink(env);
    
    char** mask = misc_char_array4("file", "symlink", "filedir/", "linkdir/");
    process_profiles2(mask, "Symlink (to file) Creation", "PROFILE.OS.SYMLINK.FILE.NEW", __func__, env, pi1, pi2);
}

void group_profileos_filecreation_intosymlinkdir(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface_intosymlinkdir(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities_intosymlinkdir(env);
    
    char** mask = misc_char_array3("dir/", "symlinkdir", "file");
    process_profiles2(mask, "File Creation into Symlink Dir", "PROFILE.OS.FILE.NEW.INTOSYMLINKDIR", __func__, env, pi1, pi2);
}

void group_profileos_dircreation(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface_dir(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities_dir(env);
    
    char** mask = misc_char_array2("parentdir/", "newdir/");
    process_profiles2(mask, "Dir Creation", "PROFILE.OS.DIR.NEW", __func__, env, pi1, pi2);
}

void group_profileos_dirsymlink_creation(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filecreation_interface_symlink_dir(env);
    struct profile_info_struct* pi2 = profileos_filecreation_utilities_symlink_dir(env);
    
    char** mask = misc_char_array4("dir/", "symlink", "dirdir/", "linkdir/");
    process_profiles2(mask, "Symlink (to dir) Creation", "PROFILE.OS.SYMLINK.DIR.NEW", __func__, env, pi1, pi2);
}


void group_profileos_fileaccess(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_fileaccess_interface(env);
    struct profile_info_struct* pi2 = profileos_fileaccess_utilities(env);
    
    char** mask = misc_char_array2("dir/", "file");
    process_profiles2(mask, "File Access", "PROFILE.OS.FILE.READ", __func__, env, pi1, pi2);
}

void group_profileos_symlink_readlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_symlink_readlink_interface(env);
    struct profile_info_struct* pi2 = profileos_symlink_readlink_utilities(env);
    struct profile_info_struct* pi3 = profileos_symlink_readlink_interface_dir(env);
    struct profile_info_struct* pi4 = profileos_symlink_readlink_utilities_dir(env);
    
    char** mask = misc_char_array4("target", "symlink", "targetdir/", "linkdir/");
    process_profiles4(mask, "Symlink (to file/dir) readlink", "PROFILE.OS.SYMLINK.READLINK", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_fileaccess_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_fileaccess_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_fileaccess_utilities_symlink(env);
    
    char** mask = misc_char_array4("file", "symlink", "filedir/", "linkdir/");
    process_profiles2(mask, "Symlink (to file) Access (defaut follow)", "PROFILE.OS.SYMLINK.FILE.READ", __func__, env, pi1, pi2);
}

void group_profileos_filemodify(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filemodify_interface_wb(env);
    struct profile_info_struct* pi2 = profileos_filemodify_interface_rp(env);
    struct profile_info_struct* pi3 = profileos_filemodify_interface_a(env);
    struct profile_info_struct* pi4 = profileos_filemodify_utilities_r1(env);
    struct profile_info_struct* pi5 = profileos_filemodify_utilities_r2(env);
    
    char** mask = misc_char_array2("dir/", "file");
    process_profiles5(mask, "File Modify", "PROFILE.OS.FILE.WRITE", __func__, env, pi1, pi2, pi3, pi4, pi5);
}

void group_profileos_filemodify_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filemodify_interface_wb_symlink(env);
    struct profile_info_struct* pi2 = profileos_filemodify_interface_rp_symlink(env);
    struct profile_info_struct* pi3 = profileos_filemodify_interface_a_symlink(env);
    struct profile_info_struct* pi4 = profileos_filemodify_utilities_r1_symlink(env);
    struct profile_info_struct* pi5 = profileos_filemodify_utilities_r2_symlink(env);
    
    char** mask = misc_char_array4("file", "symlink", "filedir/", "linkdir/");
    process_profiles5(mask, "Symlink (to file) Modify (defaut follow)", "PROFILE.OS.SYMLINK.FILE.WRITE", __func__, env, pi1, pi2, pi3, pi4, pi5);
}

void group_profileos_filechange(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filechange_interface_chmod(env);
    struct profile_info_struct* pi2 = profileos_filechange_interface_chown(env);
    struct profile_info_struct* pi3 = profileos_filechange_utilities_chmod(env);
    struct profile_info_struct* pi4 = profileos_filechange_utilities_chown(env);
    
    char** mask = misc_char_array2("dir/", "file");
    process_profiles4(mask, "File Change", "PROFILE.OS.FILE.CHANGE", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_symlinkchange(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filechange_interface_chmod_symlink(env);
    struct profile_info_struct* pi2 = profileos_filechange_interface_chown_symlink(env);
    struct profile_info_struct* pi3 = profileos_filechange_utilities_chmod_symlink(env);
    struct profile_info_struct* pi4 = profileos_filechange_utilities_chown_symlink(env);
    
    char** mask = misc_char_array4("file", "symlink", "filedir/", "linkdir/");
    process_profiles4(mask, "Symlink (to file) Change (defaut follow)", "PROFILE.OS.SYMLINK.FILE.CHANGE", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_symlinkchange_nofollow(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filechange_utilities_chown_symlink_nofollow(env);
    struct profile_info_struct* pi2 = profileos_filechange_interface_chown_symlink_nofollow(env);
    
    char** mask = misc_char_array4("file", "symlink", "filedir/", "linkdir/");
#ifdef __linux__
    process_profiles2(mask, "Symlink (to file) Change (no follow)", "PROFILE.OS.SYMLINK.FILE.CHANGE.NOFOLLOW", __func__, env, pi1, pi2);
#else
    struct profile_info_struct* pi3 = profileos_filechange_interface_chmod_symlink_nofollow(env);
    struct profile_info_struct* pi4 = profileos_filechange_utilities_chmod_symlink_nofollow(env);
    
    process_profiles4(mask, "Symlink (to file) Change (no follow)", "PROFILE.OS.SYMLINK.FILE.CHANGE.NOFOLLOW", __func__, env, pi1, pi2, pi3, pi4);
#endif
}

void group_profileos_dirchange(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filechange_interface_chmod_dir(env);
    struct profile_info_struct* pi2 = profileos_filechange_interface_chown_dir(env);
    struct profile_info_struct* pi3 = profileos_filechange_utilities_chmod_dir(env);
    struct profile_info_struct* pi4 = profileos_filechange_utilities_chown_dir(env);
    
    char** mask = misc_char_array2("parentdir/", "dir/");
    process_profiles4(mask, "Dir Change", "PROFILE.OS.DIR.CHANGE", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_filedelete_last(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filedelete_last_interface_empty(env);
    struct profile_info_struct* pi2 = profileos_filedelete_last_interface_notempty(env);
    struct profile_info_struct* pi3 = profileos_filedelete_last_utilities_empty(env);
    struct profile_info_struct* pi4 = profileos_filedelete_last_utilities_notempty(env);
    
    char** mask = misc_char_array2("dir/", "file");
    process_profiles4(mask, "File Delete (last hard link)", "PROFILE.OS.FILE.RM.last", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_filedelete_notlast(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filedelete_notlast_interface_empty(env);
    struct profile_info_struct* pi2 = profileos_filedelete_notlast_interface_notempty(env);
    struct profile_info_struct* pi3 = profileos_filedelete_notlast_utilities_empty(env);
    struct profile_info_struct* pi4 = profileos_filedelete_notlast_utilities_notempty(env);
    
    char** mask = misc_char_array2("dir/", "file");
    process_profiles4(mask, "File Delete (not last hard link)", "PROFILE.OS.FILE.RM.notlast", __func__, env, pi1, pi2, pi3, pi4);
}

void group_profileos_filedelete_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_filedelete_last_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_filedelete_last_utilities_symlink(env);
    
    char** mask = misc_char_array4("file", "symlink", "filedir/", "linkdir/");
    process_profiles2(mask, "Symlink (to file) Delete", "PROFILE.OS.SYMLINK.FILE.RM.last", __func__, env, pi1, pi2);
}

void group_profileos_dirdelete(testenv_struct* env){
    // Hard link to a directory:
    // POSIX: "If path1 names a directory, link( ) shall fail unless the process has appropriate privileges and the implementation supports using link( ) on directories."
    // Linux: You can't do a hard link to a dir: https://askubuntu.com/questions/210741/why-are-hard-links-not-allowed-for-directories
    // OpenBSD: man 2 link - "As mandated by POSIX.1 name1 may not be a directory"
    // FreeBSD: man 2 link - "The name1 argument may not be a directory"
    struct profile_info_struct* pi1 = profileos_dirdelete_interface(env);
    struct profile_info_struct* pi2 = profileos_dirdelete_utilities_rm(env);
    struct profile_info_struct* pi3 = profileos_dirdelete_utilities_rmdir(env);
    
    char** mask = misc_char_array2("parentdir/", "dir/");
    process_profiles3(mask, "Dir Delete (last hard link)", "PROFILE.OS.DIR.RM.last", __func__, env, pi1, pi2, pi3);
}

void group_profileos_dirdelete_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_dirdelete_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_dirdelete_utilities_symlink(env);
    
    char** mask = misc_char_array4("dir/", "symlink", "dirdir/", "linkdir/");
    process_profiles2(mask, "Symlink (to dir) Delete", "PROFILE.OS.SYMLINK.DIR.RM.last", __func__, env, pi1, pi2);
}

void group_profileos_dirlisting_notempty(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_dirlisting_interface_notempty(env);
    struct profile_info_struct* pi2 = profileos_dirlisting_utilities_notempty(env);
    
    char** mask = misc_char_array2("dir/", "file");
    process_profiles2(mask, "Dir Listing (not empty)", "PROFILE.OS.DIR.LISTING.notempty", __func__, env, pi1, pi2);
}

void group_profileos_dirlisting_empty(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_dirlisting_interface_empty(env);
    struct profile_info_struct* pi2 = profileos_dirlisting_utilities_empty(env);
    
    char** mask = misc_char_array1("dir/");
    process_profiles2(mask, "Dir Listing (empty)", "PROFILE.OS.DIR.LISTING.empty", __func__, env, pi1, pi2);
}

void group_profileos_dirlisting_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_dirlisting_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_dirlisting_utilities_symlink(env);
    
    char** mask = misc_char_array3("dir/", "symlink", "file");
    process_profiles2(mask, "Symlink (to dir) Listing", "PROFILE.OS.SYMLINK.DIR.LISTING.notempty", __func__, env, pi1, pi2);
}

void group_profileos_dirtraversal(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_dirtraversal_interface(env);
    struct profile_info_struct* pi2 = profileos_dirtraversal_utilities(env);
    struct profile_info_struct* pi3 = profileos_dirtraversal_utilities_profileos(env);
    
    char** mask = misc_char_array1("dir/");
    process_profiles3(mask, "Dir Traversal", "PROFILE.OS.DIR.TRAVERSAL", __func__, env, pi1, pi2, pi3);
}

void group_profileos_dirtraversal_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_dirtraversal_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_dirtraversal_utilities_symlink(env);
    struct profile_info_struct* pi3 = profileos_dirtraversal_utilities_profileos_symlink(env);
    
    char** mask = misc_char_array2("dir/", "symlink");
    process_profiles3(mask, "Symlink (to dir) Traversal", "PROFILE.OS.SYMLINK.DIR.TRAVERSAL", __func__, env, pi1, pi2, pi3);
}

void group_profileos_execute(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_execute_system_interface(env);
    struct profile_info_struct* pi2 = profileos_execute_system_utilities(env);
    struct profile_info_struct* pi3 = profileos_execute_local_interface(env);
    struct profile_info_struct* pi4 = profileos_execute_local_utilities(env);
    
    char** mask = misc_char_array3("bin", "dir/", "pwd/");
    process_profiles4(mask, "Binary Execution", "PROFILE.OS.EXEC", __func__, env, pi1, pi2, pi3, pi4);
}


void group_profileos_execute_symlink(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_execute_local_interface_symlink(env);
    struct profile_info_struct* pi2 = profileos_execute_local_utilities_symlink(env);
    
    char** mask = misc_char_array5("bin", "bin_symlink", "bindir/", "linkdir/", "pwd/");
    process_profiles2(mask, "Symlink (to binary) Execution", "PROFILE.OS.SYMLINK.EXEC", __func__, env, pi1, pi2);
}


void group_profileos_execute_intosymlinkdir(testenv_struct* env){
    struct profile_info_struct* pi1 = profileos_execute_local_interface_intosymlinkdir(env);
    struct profile_info_struct* pi2 = profileos_execute_local_utilities_intosymlinkdir(env);
    
    char** mask = misc_char_array4("bin", "dir/", "dir_symlink", "pwd/");
    process_profiles2(mask, "Binary Execution into Symlink Dir", "PROFILE.OS.EXEC.INTOSYMLINKDIR", __func__, env, pi1, pi2);
}

void print_profile(struct profile_info_struct* pi, char** mask, testenv_struct* env, char* desc, char* func_name){
    misc_print_profile_masked(env->output_file, env->error_file, pi, mask, desc, func_name, env->csv_file, env->csv_file_flags);
    if (VERBOSE){
        log_info_ts_profile_on_error_message_short(env->output_file, env->error_file, "", 0, pi, "");
    }   
}

void process_profiles(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct** pi_list, int pi_num){
    if (pi_num == 0){
        log_warning(env->output_file, env->error_file, "%s", "Profile list is empty.");
        return;
    }
    
    int all_eq = 1;
    int i;
    for (i = 0; i < pi_num-1; i++){
        if (misc_profile_eq(pi_list[i], pi_list[i+1]) != 0){
            all_eq = 0;
        }
    }
    
    fprintf(env->output_file, "%s (%s):\n", desc, ref);
    if (all_eq){
        print_profile(pi_list[0], mask, env, ref, func_name);
        
        if (VERBOSE){
            for (i = 0; i < pi_num; i++){
                print_profile(pi_list[i], NULL, env, ref, func_name);
                fprintf(env->output_file, "\n");
            }
        }
    }
    else {
        fprintf(env->output_file, "Conflictual results\n");
        for (i = 0; i < pi_num; i++){
            print_profile(pi_list[i], NULL, env, ref, func_name);
            fprintf(env->output_file, "\n");
        }
    }
    
}

void process_profiles1(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1){
    struct profile_info_struct** pi_list = calloc(1, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 1);    
}

void process_profiles2(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2){
    struct profile_info_struct** pi_list = calloc(2, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 2);    
}

void process_profiles3(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3){
    struct profile_info_struct** pi_list = calloc(3, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 3);    
}

void process_profiles4(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4){
    struct profile_info_struct** pi_list = calloc(4, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 4);    
}

void process_profiles5(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5){
    struct profile_info_struct** pi_list = calloc(5, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 5);    
}

void process_profiles6(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6){
    struct profile_info_struct** pi_list = calloc(6, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 6);    
}

void process_profiles7(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7){
    struct profile_info_struct** pi_list = calloc(7, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    pi_list[6] = pi7;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 7);    
}

void process_profiles8(char** mask, char* desc, char* ref, char* func_name, testenv_struct* env, struct profile_info_struct* pi1, struct profile_info_struct* pi2, struct profile_info_struct* pi3, struct profile_info_struct* pi4, struct profile_info_struct* pi5, struct profile_info_struct* pi6, struct profile_info_struct* pi7, struct profile_info_struct* pi8){
    struct profile_info_struct** pi_list = calloc(8, sizeof(struct profile_info_struct*));
    pi_list[0] = pi1;
    pi_list[1] = pi2;
    pi_list[2] = pi3;
    pi_list[3] = pi4;
    pi_list[4] = pi5;
    pi_list[5] = pi6;
    pi_list[6] = pi7;
    pi_list[7] = pi8;
    process_profiles(mask, desc, ref, func_name, env, pi_list, 8);    
}
#endif
