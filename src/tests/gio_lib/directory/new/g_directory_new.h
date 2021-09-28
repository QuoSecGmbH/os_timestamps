#ifndef EMPTY_G_DIRECTORY_NEW_H
#define EMPTY_G_DIRECTORY_NEW_H

#include "log.h"
#include "current_time.h"
#include <glib.h>
#include <gio/gio.h>


int check_gio_g_file_make_directory(FILE * csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_gio_g_file_make_directory_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif //EMPTY_G_DIRECTORY_NEW_H
