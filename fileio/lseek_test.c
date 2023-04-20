#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf_read[12];
    char buf_write[] = "lseek test\n";

    if ((fd = open("lseek_test", O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
        err_sys("open error");

    if (write(fd, buf_write, strlen(buf_write)) != strlen(buf_write))
        err_sys("write error");

    lseek(fd, 6, SEEK_SET);
    if (read(fd, buf_read, sizeof(buf_read)) == -1)
        err_sys("read error");
    printf("read: %s\n", buf_read);
    lseek(fd, 6, SEEK_SET);
    if (write(fd, buf_write, strlen(buf_write)) != strlen(buf_write))
        err_sys("write error");

    close(fd);

    exit(0);
}
