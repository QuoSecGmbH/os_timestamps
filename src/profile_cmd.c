#ifndef PROFILE_CMD_C
#define PROFILE_CMD_C

#include "profile_cmd.h"

int PROFILE_TREAT_DELAY_AS_COMMAND = 0;

void print_usage(){
    fprintf(stderr, "Usage: ./profile_cmd [options] \"CMD\"\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  --verbose / -v\n");
    fprintf(stderr, "  --quick / -q\n");
    fprintf(stderr, "  --dir / -d PWD_DIR\n");
    fprintf(stderr, "  --watch / -w WATCH\n");
    fprintf(stderr, "  --precommand / -p \"PRECOMMAND\"\n");
    fprintf(stderr, "  --wait-pre-s / -s WAIT_PRE_S\n");
    fprintf(stderr, "  --wait-pre-ns / -n WAIT_PRE_NS\n");
    fprintf(stderr, "  --wait-cmd-s / -t WAIT_CMD_S\n");
    fprintf(stderr, "  --wait-cmd-ns / -m WAIT_CMD_NS\n");
}

int main(int argc, char *argv[]) {
//     char verbose = 0;
    char quick = 0;
    char* pwd_dir = NULL;
    int watch_num = 0;
    char** watch_array;
    char* precommand = NULL;
    time_t wait_pre_s = 0;
    long wait_pre_ns =  ns_after_open;
    
    time_t wait_cmd_s = 0;
    long wait_cmd_ns =  ns_after_open;
    
    int c;
    while (1) {
        static struct option long_options[] =
            {
            {"verbose", no_argument,       0, 'v'},
            {"dir", required_argument,       0, 'd'},
            {"watch", required_argument, 0, 'w'},
            {"precommand", required_argument, 0, 'p'},
            {"wait-pre-s", required_argument, 0, 's'},
            {"wait-pre-ns", required_argument, 0, 'n'},
            {"wait-cmd-s", required_argument, 0, 't'},
            {"wait-cmd-ns", required_argument, 0, 'm'},
            {"quick", no_argument, 0, 'q'},
            {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "vd:w:p:s:n:t:m:q",
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
                pwd_dir = optarg; 
                break;
            }
            case 'w': {
                watch_array = (char**) realloc(watch_array, (watch_num+1)*sizeof(char*));
                watch_array[watch_num] = optarg;
                watch_num++;
                break;
            }
            case 'p': {
                precommand = optarg; 
                break;
            }
            case 's': {
                wait_pre_s = (time_t) atoi(optarg); 
                break;
            }
            case 'n': {
                wait_pre_ns = (long) atol(optarg); 
                break;
            }
            case 't': {
                wait_cmd_s = (time_t) atoi(optarg); 
                break;
            }
            case 'm': {
                wait_cmd_ns = (long) atol(optarg); 
                break;
            }
            case 'q': {
                quick = 1;
                break;
            }
            default:
                fprintf(stderr, "Unknown argument.\n");
                print_usage();
                exit(EXIT_FAILURE);
            }
        }

    if (quick == 1){
        if (precommand == NULL){
            wait_pre_s = 0; 
            wait_pre_ns = 0;
        }
        wait_cmd_s = 0;
        wait_cmd_ns = 0;
    }
    
    char* command = NULL;
    if (optind == argc - 1){
        command = argv[argc-1];
    }
    else {
        fprintf(stderr, "Missing command.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
    
    if (VERBOSE){
        if (precommand != NULL) printf("Precommand: %s\n", precommand);
        if (command != NULL) printf("Command: %s\n", command);
    }
    
    struct profile_info_struct* pi = profile_command(stdout, stderr, pwd_dir, NULL, NULL, watch_num, watch_array, precommand, wait_pre_s, wait_pre_ns, command, wait_cmd_s, wait_cmd_ns);
    misc_print_profile(stdout, stderr, pi);
    
    if (VERBOSE){
        log_info_ts_profile_on_error_message(stdout, stderr, "profile_cmd", 0, pi, "");
    }
}

#endif
