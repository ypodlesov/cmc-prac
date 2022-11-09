#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) 
{
    char *path = strdup(argv[1]);
    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1) {
        fprintf(stderr, "error! open\n");
        exit(1);
    }
    struct stat stb;
    fstat(fd, &stb);
    printf("%lld\n", stb.st_size);
    int tmp = 10;
    write(fd, &tmp, sizeof(tmp));
    printf("%lld\n", stb.st_size);

    printf("%d\n", 1 << 16);


    return 0;
}
