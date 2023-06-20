#include "apue.h"
#include <errno.h>

int globvar = 6;

int main(int argc, char *argv[])
{
    int var;
    pid_t pid;
    int i;
    char buf[MAXLINE];
    int stdout_fd = -1;

    var = 88;
    printf("before fork\n");
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        globvar++;
        var++;
        /* _exit(0); -> exit(0); do not close standard I/O stream, printf has output */
        fclose(stdout);
        exit(0);
    }

    i = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    sprintf(buf, "%d\n", i);
    if (write(STDOUT_FILENO, buf, strlen(buf)) == -1) {
        /* not verified */
        /* ------------ */
        if (errno ==  EBADF) {
            char output_buf[] = "STDOUT_FILENO closed, dup STDOUT_FILENO\n";
            stdout_fd = dup(STDOUT_FILENO);
            write(stdout_fd, buf, strlen(buf));
            write(stdout_fd, output_buf, strlen(output_buf));
        /* ------------ */
        } else {
            exit(127);
        }
    } else {
        char output_buf[] = "STDOUT_FILENO not closed\n";
        write(STDOUT_FILENO, output_buf, strlen(output_buf));
    }
    exit(0);
}
