#include "apue.h"

#define BUFSIZE 1000000000

static void sig_alrm(int signo)
{
    printf("caught SIGALRM\n");
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[BUFSIZE] = {0};

    signal(SIGALRM, sig_alrm);

    if ((fp = fopen("test_fwrite_data", "w")) == NULL)
        err_sys("fopen error\n");

    alarm(1);

    if (fwrite(buf, 1, BUFSIZE, fp) != BUFSIZE)
        err_sys("fwrite error\n");

    fclose(fp);

    exit(0);
}
