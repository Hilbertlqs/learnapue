#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */
#include <signal.h>		/* for SIG_ERR */
#include <sys/resource.h>
#include <errno.h>

#define BUFFSIZE 100

typedef	void	Sigfunc(int);	/* for signal handlers */
Sigfunc	*signal_intr(int, Sigfunc *);		/* {Prog signal_intr_function} */

static void sig_xfsz(int signo)
{
    printf("caught SIGXFSZ\n");
}

int main(int argc, char *argv[])
{
    int n;
    int c;
    char buf[BUFFSIZE];
    struct rlimit limit;
    unsigned long long lim_cur, lim_max;

    getrlimit(RLIMIT_FSIZE, &limit);
    lim_cur = limit.rlim_cur;
    lim_max = limit.rlim_max;
    printf("RLIMIT_FSIZE: %lld, %lld\n", lim_cur, lim_max);

    limit.rlim_cur = 1024;
    limit.rlim_max = 1024;
    setrlimit(RLIMIT_FSIZE, &limit);
    getrlimit(RLIMIT_FSIZE, &limit);
    lim_cur = limit.rlim_cur;
    lim_max = limit.rlim_max;
    printf("RLIMIT_FSIZE: %lld, %lld\n", lim_cur, lim_max);

    signal_intr(SIGXFSZ, sig_xfsz);

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if ((c = write(STDOUT_FILENO, buf, n)) != n) {
            printf("write: %d, %s\n", c, strerror(errno));
        } else {
            printf("\n");
            printf("write: %d\n", c);
        }
    }

    if (n < 0)
        printf("read: %d, %s\n", n, strerror(errno));

    exit(0);
}
