#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>

void work(int serial, volatile int *p)
{
    while (1) {
        while (!p[serial]) {}
        int t = p[serial]; p[serial] = 0;
        printf("%d %d\n", serial, t); fflush(stdout);
        p[1 - serial] = t + 1;
    }
}

int main()
{
    int *p = mmap(NULL, sizeof(*p) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    for (int i = 0; i < 2; ++i) {   
        int pid = fork();
        if (pid == 0) {
            work(i, p);
            _exit(0);
        }
    }

    p[0] = 1;
    
    while(wait(NULL) > 0) {
    }
}
