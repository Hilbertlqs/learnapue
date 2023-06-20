#include "apue.h"
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    int fd;
    int val;
    char buf[MAXLINE];
    pid_t pid;

    dp = opendir("/");
    fd = dirfd(dp);

    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl error");
    if (val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");

    sprintf(buf, "%d", fd);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        execl("/home/lqs/apue3e/learnapue/build/proc/cloexec_child", "cloexec_child", buf, (char *)0);
        exit(127);
    }

    exit(0);
}
