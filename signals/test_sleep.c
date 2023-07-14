#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int i;
    time_t t;
    struct tm *tmp;

    while (1) {
        for (i = 0; i < 5; i++)
            sleep(60);
        time(&t);
        tmp = localtime(&t);
        printf("%d\n", tmp->tm_sec);
    }

    exit(0);
}
