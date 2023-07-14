#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "apue.h"

void sig2str(int signo, char *str)
{
    switch (signo) {
    case SIGHUP:
        strcpy(str, "HUP");
        break;
    case SIGINT:
        strcpy(str, "INT");
        break;
    case SIGQUIT:
        strcpy(str, "QUIT");
        break;
    case SIGILL:
        strcpy(str, "ILL");
        break;
    case SIGTRAP:
        strcpy(str, "TRAP");
        break;
    case SIGABRT:
        strcpy(str, "ABRT");
        break;
    case SIGBUS:
        strcpy(str, "BUS");
        break;
    case SIGFPE:
        strcpy(str, "FPE");
        break;
    case SIGKILL:
        strcpy(str, "KILL");
        break;
    case SIGUSR1:
        strcpy(str, "USR1");
        break;
    case SIGSEGV:
        strcpy(str, "SEGV");
        break;
    case SIGUSR2:
        strcpy(str, "USR2");
        break;
    case SIGPIPE:
        strcpy(str, "PIPE");
        break;
    case SIGALRM:
        strcpy(str, "ALRM");
        break;
    case SIGTERM:
        strcpy(str, "TERM");
        break;
    case SIGSTKFLT:
        strcpy(str, "STKFLT");
        break;
    case SIGCHLD:
        strcpy(str, "CHLD");
        break;
    case SIGCONT:
        strcpy(str, "CONT");
        break;
    case SIGSTOP:
        strcpy(str, "STOP");
        break;
    case SIGTSTP:
        strcpy(str, "TSTP");
        break;
    case SIGTTIN:
        strcpy(str, "TTIN");
        break;
    case SIGTTOU:
        strcpy(str, "TTOU");
        break;
    case SIGURG:
        strcpy(str, "URG");
        break;
    case SIGXCPU:
        strcpy(str, "XCPU");
        break;
    case SIGXFSZ:
        strcpy(str, "XFSZ");
        break;
    case SIGVTALRM:
        strcpy(str, "VTALRM");
        break;
    case SIGPROF:
        strcpy(str, "PROF");
        break;
    case SIGWINCH:
        strcpy(str, "WINCH");
        break;
    case SIGPOLL:
        strcpy(str, "POLL");
        break;
    case SIGPWR:
        strcpy(str, "PWR");
        break;
    case SIGSYS:
        strcpy(str, "SYS");
        break;
    default:
        strcpy(str, "UNKNOWN");
        break;
    }
}

int main(int argc, char *argv[])
{
    int signo;
    char str[MAXLINE];

    while (1) {
        scanf("%d", &signo);
        sig2str(signo, str);
        printf("%s\n", str);
    }

    exit(0);
}
