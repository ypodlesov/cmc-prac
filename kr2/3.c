#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) 
{
    setvbuf(stdin, NULL, _IONBF, 0);
    int num;
    while (scanf("%d", &num) == 1) {
        printf("%d %d\n", getpid(), num);
        fflush(stdout);
        int cur_depth = 0;
        while (1) {
            if (!fork()) {
                if (++cur_depth == num) {
                    if (scanf("%d", &num) == 1) {
                        printf("%d %d\n", getpid(), num);
                        fflush(stdout);
                    }
                    _exit(0);
                }
            } else {
                wait(NULL);
                if (cur_depth > 0) {
                    _exit(0);
                } else {
                    break;
                }
            }
        }
    }
    while (wait(NULL) > 0) {}
    

    return 0;
}
