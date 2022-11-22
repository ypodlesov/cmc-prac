#include <stdio.h>

int
main(int argc, char *argc[])
{
    int fds[2];
    pipe(fds);
    time_t t = time(NULL);
    for (int i = 0; i < 3; ++i) {
        if (!fork()) {
            
        } else {
            if (!i) break;    
        }
    }
    while(wait(NULL) > 0) {}

    return 0;
}
