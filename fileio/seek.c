#include "apue.h"

int main(int argc, char *argv[])
{
    if (lseek(STDIN_FILENO, 0, SEEK_SET) == -1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");
    exit(0);
}
