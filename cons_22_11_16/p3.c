// код с консультации: но там писал его я в том числе 

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int 
main(int argc, char *argv[])
{
    int fds[2] = { 0, 1 };
    for (int i = 1; i < argc; ++i) {
        int tmpfds[2] = { 0, 1 };
        if (i != argc - 1) {
            pipe2(tmpfds, O_CLOEXEC);
        }
        int pid = fork();
        if (pid < 0) {
             
        } else if (pid > 0) {
            dup2(fds[0], STDIN_FILENO);
            dup2(tmpfds[1], STDOUT_FILENO);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }
        if (tmpfds[1] != 1) {
            close(tmpfds[1]);
        }
        if (fds[0] != 0) {
            close(fds[0]);
        }
        fds[0] = tmpfds[0];
    }
    while (wait(NULL) > 0) {}

    return 0;
}
