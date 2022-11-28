// code from consultation
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

#define SUCCESS(A) (WIFEXITED(A) && !(WEXITSTATUS(A)))

void
terminate_all(int *pids) 
{
    for (int i = 0; pids[i] != -1; ++i) {
        kill(pids[i], SIGKILL);
        pids[i] = -1;
    }
}

int 
main(int argc, char *argv[])
{
    int pids[argc];
    for (int i = 0; i < argc; ++i) pids[i] = -1;
    int fds[2] = { 0, 1 };
    for (int i = 1; i < argc; ++i) {
        int tmpfds[2] = { 0, 1 };
        if (i != argc - 1) {
            if (pipe2(tmpfds, O_CLOEXEC)) {
                exit(1);
            }
        }
        pids[i-1] = fork();
        if (pids[i-1] < 0) {
            _exit(1);
        } else if (!pids[i-1]) {
            dup2(fds[0], STDIN_FILENO);
            dup2(tmpfds[1], STDOUT_FILENO);
            execlp(argv[i], argv[i], NULL);
            _exit(0);
        }
        if (tmpfds[1] != 1) {
            if (close(tmpfds[1])) {
                _exit(1);
            }
        }
        if (fds[0] != 0) {
            if (close(fds[0])) {
                _exit(1);
            }
        }
        fds[0] = tmpfds[0];
    }
    if (close(fds[0])) {
        terminate_all(pids);
        exit(1);
    }
    if (close(fds[1])) {
        terminate_all(pids);
        exit(1);
    }
    int status;
    while (wait(&status) > 0) {
        if (!SUCCESS(status)) {
            terminate_all(pids);
            exit(1);
        }
    }
    return 0;
}
