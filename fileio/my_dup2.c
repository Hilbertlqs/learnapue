#include "apue.h"
#include <limits.h>
#include <sys/resource.h>
#include <errno.h>
#include <fcntl.h>

#define OPEN_MAX_GUESS 256

long open_max(void)
{
    long openmax;
    struct rlimit rl;

    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX) {
        if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
            err_sys("can't get file limit");
        if (rl.rlim_max == RLIM_INFINITY)
            openmax = OPEN_MAX_GUESS;
        else
            openmax = rl.rlim_max;
    }
    return(openmax);
}

/* 对于dup2，可以用fd2参数指定新描述符的值。 */
int my_dup2(int fd, int fd2)
{
    int dup_fd;
    int begin_fd;
    int temp_fd;
    long openmax;
    int i;

    openmax = open_max();
    printf("openmax is %ld\n", openmax);

    if (fd < 0 || fd2 < 0 || fd > (openmax - 1) || fd2 > (openmax - 1)) {
        perror("fd error");
        return -1;
    }

    /* 如若fd等于fd2，则dup2返回fd2，而不关闭它。否则，fd2的FD_CLOEXEC文件描述符标志就被清除，这样fd2在进程调用exec时是打开状态。 */
    if(fd == fd2) {
        return fd2;
    }

    /* 如果fd2已经打开，则先将其关闭。 */
    close(fd2);

    /* 由dup返回的新文件描述符一定是当前可用文件描述符中的最小数值。 */
    temp_fd = dup(fd);
    if (temp_fd == -1) {
        perror("dup error");
        return -1;
    }
    dup_fd = temp_fd;
    printf("create fd %d\n", dup_fd);
    begin_fd = dup_fd;
    while (dup_fd < (openmax - 1)) {
        if (dup_fd == fd2) {
            printf("get fd2\n");
            break;
        }
        temp_fd = dup(fd);
        if (temp_fd == -1) {
            perror("dup error");
            for (i = begin_fd; i <= dup_fd; ++i) {
                close(i);
                printf("close fd %d\n", i);
            }
            return -1;
        }
        dup_fd = temp_fd;
        printf("create fd %d\n", dup_fd);
    }

    if (dup_fd == (openmax - 1)) {
        printf("cannot get fd2 within openmax fds\n");
        for (i = begin_fd; i <= dup_fd; ++i) {
            close(i);
            printf("close fd %d\n", i);
        }
        return -1;
    }

    for (i = begin_fd; i < dup_fd; ++i) {
        close(i);
        printf("close fd %d\n", i);
    }

    return dup_fd;
}

int main(int argc, char *argv[])
{
    int fd;
    int fd2;
    char *buf = "my_dup2 test\n";

    if (argc != 2)
        err_quit("usage: my_dup2 <descriptor#>");

    if ((fd = open("my_dup2_text", O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
        err_sys("open error");

    fd2 = my_dup2(fd, atoi(argv[1]));
    if (fd2 == -1)
        err_sys("my_dup2 error");
    printf("fd2 is %d\n", fd2);

    if (write(fd2, buf, strlen(buf)) != strlen(buf))
        err_sys("write error");

    close(fd2);
    printf("close fd %d\n", fd2);

    exit(0);
}
