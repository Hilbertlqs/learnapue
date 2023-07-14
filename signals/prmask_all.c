#include "apue.h"
#include <errno.h>

void
pr_mask(const char *str)
{
    sigset_t    sigset;
    int         errno_save;

    errno_save = errno;     /* we can be called by signal handlers */
    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGABRT))
            printf(" SIGABRT");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");
        if (sigismember(&sigset, SIGBUS))
            printf(" SIGBUS");
        if (sigismember(&sigset, SIGCANCEL))
            printf(" SIGCANCEL");
        if (sigismember(&sigset, SIGCHLD))
            printf(" SIGCHLD");
        if (sigismember(&sigset, SIGCONT))
            printf(" SIGCONT");
        if (sigismember(&sigset, SIGEMT))
            printf(" SIGEMT");
        if (sigismember(&sigset, SIGFPE))
            printf(" SIGFPE");
        if (sigismember(&sigset, SIGFREEZE))
            printf(" SIGFREEZE");
        if (sigismember(&sigset, SIGHUP))
            printf(" SIGHUP");
        if (sigismember(&sigset, SIGILL))
            printf(" SIGILL");
        if (sigismember(&sigset, SIGINFO))
            printf(" SIGINFO");
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGIO))
            printf(" SIGIO");
        if (sigismember(&sigset, SIGIOT))
            printf(" SIGIOT");
        if (sigismember(&sigset, SIGJVM1))
            printf(" SIGJVM1");
        if (sigismember(&sigset, SIGJVM2))
            printf(" SIGJVM2");
        if (sigismember(&sigset, SIGKILL))
            printf(" SIGKILL");
        if (sigismember(&sigset, SIGLOST))
            printf(" SIGLOST");
        if (sigismember(&sigset, SIGLWP))
            printf(" SIGLWP");
        if (sigismember(&sigset, SIGPIPE))
            printf(" SIGPIPE");
        if (sigismember(&sigset, SIGPOLL))
            printf(" SIGPOLL");
        if (sigismember(&sigset, SIGPROF))
            printf(" SIGPROF");
        if (sigismember(&sigset, SIGPWR))
            printf(" SIGPWR");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGSEGV))
            printf(" SIGSEGV");
        if (sigismember(&sigset, SIGSTKFLT))
            printf(" SIGSTKFLT");
        if (sigismember(&sigset, SIGSTOP))
            printf(" SIGSTOP");
        if (sigismember(&sigset, SIGSYS))
            printf(" SIGSYS");
        if (sigismember(&sigset, SIGTERM))
            printf(" SIGTERM");
        if (sigismember(&sigset, SIGTHAW))
            printf(" SIGTHAW");
        if (sigismember(&sigset, SIGTHR))
            printf(" SIGTHR");
        if (sigismember(&sigset, SIGTRAP))
            printf(" SIGTRAP");
        if (sigismember(&sigset, SIGTSTP))
            printf(" SIGTSTP");
        if (sigismember(&sigset, SIGTTIN))
            printf(" SIGTTIN");
        if (sigismember(&sigset, SIGTTOU))
            printf(" SIGTTOU");
        if (sigismember(&sigset, SIGURG))
            printf(" SIGURG");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGUSR2))
            printf(" SIGUSR2");
        if (sigismember(&sigset, SIGVTALRM))
            printf(" SIGVTALRM");
        if (sigismember(&sigset, SIGWAITING))
            printf(" SIGWAITING");
        if (sigismember(&sigset, SIGWINCH))
            printf(" SIGWINCH");
        if (sigismember(&sigset, SIGXCPU))
            printf(" SIGXCPU");
        if (sigismember(&sigset, SIGXFSZ))
            printf(" SIGXFSZ");
        if (sigismember(&sigset, SIGXRES))
            printf(" SIGXRES");

        printf("\n");
    }

    errno = errno_save;     /* restore errno */
}
