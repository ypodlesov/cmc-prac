// (prog1 || prog2) | prog3 >> file1
// [1]       [2]      [3]      [4]
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *cmd1 = argv[1];
    char *cmd2 = argv[2];
    char *cmd3 = argv[3];
    char *file1 = argv[4];

    int fd[2];
    pipe2(fd, O_CLOEXEC);

    if (!fork()) {
        dup2(fd[1], STDOUT_FILENO);
        int pid;
        if (!(pid = fork())) {
            execlp(cmd1, cmd1, NULL);
            _exit(1);
        }
        int wstatus;
        waitpid(pid, &wstatus, 0);
        if (!(WIFEXITED(wstatus) && !WEXITSTATUS(wstatus))) {
             int pid2;
             if (!(pid2 = fork())) {
                 execlp(cmd2, cmd2, NULL);
                 _exit(1);
             }
             waitpid(pid, NULL, 0);
        }
        _exit(0);
    }
    if (!fork()) {
        dup2(fd[0], STDIN_FILENO);
        int fdfile = open(file1, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0600);
        dup2(fdfile, STDOUT_FILENO);
        execlp(cmd3, cmd3, NULL);
        _exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) > 0);
}
