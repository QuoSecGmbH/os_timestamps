#ifndef POSIX_TIMESTAMPS_P_QT_CREATE_H
#define POSIX_TIMESTAMPS_P_QT_CREATE_H

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QDir>

extern "C" {
    #include "log.h"
    #include "current_time.h"
    #include "file_ts.h"
    #include "misc.h"
    #include "profile.h"
};

struct profile_info_struct* profile_qt_create_file(testenv_struct* env);
struct profile_info_struct* profile_qt_create_symlink_to_file(testenv_struct* env);
struct profile_info_struct* profile_qt_create_file_into_symlink_dir(testenv_struct* env);
struct profile_info_struct* profile_qt_create_directory(testenv_struct* env);
struct profile_info_struct* profile_qt_create_symlink_to_dir(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_QT_CREATE_H
