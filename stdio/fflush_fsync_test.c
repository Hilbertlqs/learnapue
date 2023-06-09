#include "apue.h"

int main(int argc, char *argv[])
{
    FILE *fp;

    if ((fp = fopen("fflush_fsync", "w")) == NULL)
        err_sys("fopen error");

    fprintf(fp, "fflush fsync");
    fflush(fp);
    fsync(fileno(fp));

    _Exit(0);
}
