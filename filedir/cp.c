#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[])
{
    int fd1, fd2;
    struct stat stat;
    int has_hole = 0;
    int n;
    char buf[BUFFSIZE];
    char tmp_buf[BUFFSIZE];
    int i, j;

    if (argc != 3)
        err_quit("usage: %s <source_file> <target_file>", argv[0]);

    if ((fd1 = open(argv[1], O_RDONLY)) == -1)
        err_sys("%s open error", argv[1]);
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        err_sys("%s open error", argv[2]);

    if (fstat(fd1, &stat) == -1)
        err_sys("fstat error");
    if (S_ISREG(stat.st_mode) && stat.st_size > 512 * stat.st_blocks) {/* 512 or 1024 or other value? generally, stat.st_blksize = 4096 */
        printf("%s has hole\n", argv[1]);
        has_hole = 1;
    }

    if (has_hole) {
        while ((n = read(fd1, buf, BUFFSIZE)) != -1) {
            if (n == 0) {
                printf("end of file\n");
                break;
            } else {
                for (i = 0, j = 0; i < n; i++) {
                    if (buf[i] != 0)
                        tmp_buf[j++] = buf[i];
                }
                if (write(fd2, tmp_buf, j) != j)
                    err_sys("write error");
            }
        }
        if (n == -1)
            err_sys("read error");
    } else {
        while ((n = read(fd1, buf, BUFFSIZE)) != -1) {
            if (n == 0) {
                printf("end of file\n");
                break;
            } else {
                if (write(fd2, tmp_buf, n) != n)
                    err_sys("write error");
            }
        }
        if (n == -1)
            err_sys("read error");
    }

    close(fd1);
    close(fd2);

    exit(0);
}
