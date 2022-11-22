#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

enum
{   
    MODE = 0700, 
    FILE_SIZE = 1 << 20,
    MAX_LEN = 10,
    MIN_LEN = 5
};

char *
gen_name(int size) 
{
    srand(time(NULL));
    char *res = calloc(size, sizeof(*res));    
    for (int i = 0; i < size; ++i) {
        res[i] = 'a' + rand() % 26;
    }
    return res;
}

int
exist(char *path) 
{
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 0;
    }
    char content[FILE_SIZE] = "#! /bin/python3\n";
    strcat(content, "from os import remove\n");
    strcat(content, "from sys import argv\n");
    strcat(content, "print(");
    for (int i = 1; i < argc; ++i) {
        strcat(content, argv[i]);
        strcat(content, i == argc - 1 ? ")\n" : " * ");
    }
    strcat(content, "remove(argv[0])\n");
    //printf("%s\n", content);
    char path[PATH_MAX] = "src";
    //char *name = gen_name(MIN_LEN + rand() % MAX_LEN);
    //strcat(path, name);
    //free(name);
    //printf("%s\n", path);
    int fd = open(path, O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, MODE);
    FILE *file = fdopen(fd, "w");
    fprintf(file, "%s\n", content);
    fclose(file);
    //close(fd);
    //char cmd[PATH_MAX] = "./";
    //strcat(cmd, path);
    //system(cmd);
    execlp(path, path, NULL);
    exit(1);
}
