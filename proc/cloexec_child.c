#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    int val;

    sscanf(argv[1], "%d", &fd);
    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("fcntl error");
    if (val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");

    exit(0);
}
