#include "apue.h"
#include <sys/wait.h>

void pr_exit_siginfo(siginfo_t *infop)
{
    if (infop->si_code == CLD_EXITED) {
        printf("normal termination, exit status = %d\n", infop->si_status);
    } else if (infop->si_code == CLD_KILLED || infop->si_code == CLD_DUMPED) {
        printf("abnormal termination, signal number = %d%s\n", infop->si_status, infop->si_code == CLD_DUMPED ? " (core file generated)" : " ");
    } else if (infop->si_code == CLD_STOPPED) {
        printf("child stopped, signal number = %d\n", infop->si_status);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    siginfo_t info;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);

    if (waitid(P_PID, pid, &info, WEXITED) != 0)
        err_sys("waitid error");
    pr_exit_siginfo(&info);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();

    if (waitid(P_PID, pid, &info, WEXITED) != 0)
        err_sys("waitid error");
    pr_exit_siginfo(&info);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status /= 0;

    if (waitid(P_PID, pid, &info, WEXITED) != 0)
        err_sys("waitid error");
    pr_exit_siginfo(&info);

    exit(0);
}
