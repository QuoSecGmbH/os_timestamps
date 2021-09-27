#include <stdio.h>
#include <errno.h>
#include <time.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void file_read(char* path, int sz){    
    printf("Using: read\n");
    printf("Offset: (not used with read)\n");
    printf("Size: %d\n", sz);
    
    int f = open(path, O_RDONLY);
    if (f == 0) {
        printf("Error error opening file\n");
        return;
    }
    
    char* buf = (char*) calloc(sz+1, sizeof(char));
    int r = read(f, buf, sz);
    printf("Read %d:\n%s\n", r, buf);
    
    close(f);
}

void file_pread(char* path, int off, int sz){    
    printf("Using: pread\n");
    printf("Offset: %d\n", off);
    printf("Size: %d\n", sz);
    
    int f = open(path, O_RDONLY);
    if (f == 0) {
        printf("Error error opening file\n");
        return;
    }
    
    char* buf = (char*) calloc(sz+1, sizeof(char));
    int r = pread(f, buf, sz, off);
    printf("Read %d:\n%s\n", r, buf);    
    
    close(f);
}

void file_fread(char* path, int sz){    
    printf("Using: fread\n");    
    printf("Offset: (not used with fread)\n");
    printf("Size: %d\n", sz);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("Error error opening file\n");
        return;
    }
    
    char* buf = (char*) calloc(sz+1, sizeof(char));
    int r = fread(buf, 1, sz, fd);
    printf("Read %d:\n%s\n", r, buf);    
    
    fclose(fd);
}

int main (int argc, char **argv){  
    int mode = 0;
    int off = 0;
    int sz = 2;
    if (argc >= 3){
        mode = atoi(argv[2]);
    }
    if (argc >= 4){
        sz = atoi(argv[3]);
    }
    if (argc >= 5){
        off = atoi(argv[4]);
    }
    
    if (mode == 1){
        file_pread(argv[1], off, sz);
    }
    else if (mode == 2){
        file_fread(argv[1], sz);
    }
    else {
        file_read(argv[1], sz);
    }
}
