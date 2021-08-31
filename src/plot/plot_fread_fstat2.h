#ifndef PLOT_FREAD_FSTAT2_H
#define PLOT_FREAD_FSTAT2_H

#include "current_time.h"
#include "file_ts.h"
#include "log.h"
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "misc.h"
#include <getopt.h>

struct timespec* delta(struct timespec* ts_wait);
int main (int argc, char **argv);

#endif
