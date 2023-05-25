#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2)
        err_quit("usage: %s <file>");

    unlink(argv[1]);
    if ((fd = creat(argv[1], FILE_MODE)) < 0)
        err_sys("creat error");

    exit(0);
}
