#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

int 
is_prime(int n) 
{
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int last;

void 
handler(int sig) 
{
    if (sig == SIGINT) {
        static int cnt = 0;
        if (cnt == 4) _exit(0);
        printf("%d\n", last);
        ++cnt;
    } else if (sig == SIGTERM) {
        _exit(0);
    }
}

int
main(void)
{
    struct sigaction act = {};
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    printf("%d\n", getpid());
    int low, high;
    scanf("%d%d", &low, &high);
    for (int i = low; i < high; ++i) {
        if (is_prime(i)) last = i;
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
