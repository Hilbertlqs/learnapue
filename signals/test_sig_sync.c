#include "apue.h"
#include <fcntl.h>

#define COUNT 10
/*
未出现阻塞。
需要重新调用TELL_WAIT。
int main(int argc, char *argv[])
{
    int fd;
    char buf[MAXLINE];
    pid_t pid;
    int count = 0;

    fd = open("test_sig_sync_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    snprintf(buf, sizeof(buf), "parent: %d\n", count);
    if (write(fd, buf, strlen(buf)) == -1)
        err_sys("write error");
    printf("parent: %d\n", count);

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        for (count = 2; count <= COUNT; count += 2) {
            WAIT_PARENT();
            snprintf(buf, sizeof(buf), "child: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("child: %d\n", count);
            TELL_PARENT(getppid());
        }
    } else {
        for (count = 1; count <= COUNT; count += 2) {
            snprintf(buf, sizeof(buf), "parent: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("parent: %d\n", count);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }

    exit(0);
}
*/
/*
打印
parent: 0
parent: 1
后可能出现阻塞。
int main(int argc, char *argv[])
{
    int fd;
    char buf[MAXLINE];
    pid_t pid;
    int count = 0;

    fd = open("test_sig_sync_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    snprintf(buf, sizeof(buf), "parent: %d\n", count);
    if (write(fd, buf, strlen(buf)) == -1)
        err_sys("write error");
    printf("parent: %d\n", count);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        for (count = 2; count <= COUNT; count += 2) {
            TELL_WAIT();
            WAIT_PARENT();
            snprintf(buf, sizeof(buf), "child: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("child: %d\n", count);
            TELL_PARENT(getppid());
        }
    } else {
        sleep(1);
        for (count = 1; count <= COUNT; count += 2) {
            TELL_WAIT();
            snprintf(buf, sizeof(buf), "parent: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("parent: %d\n", count);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }

    exit(0);
}
*/
/*
加入延时后不出现阻塞。
不加延时出现阻塞，可能是父进程已经执行
TELL_CHILD(pid);
发送信号，但子进程尚未执行
TELL_WAIT();
阻塞信号，信号处理函数提前被调用，导致子进程执行
WAIT_PARENT();
时子进程被阻塞。
但加延时不是解决方法。
int main(int argc, char *argv[])
{
    int fd;
    char buf[MAXLINE];
    pid_t pid;
    int count = 0;

    fd = open("test_sig_sync_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    snprintf(buf, sizeof(buf), "parent: %d\n", count);
    if (write(fd, buf, strlen(buf)) == -1)
        err_sys("write error");
    printf("parent: %d\n", count);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        for (count = 2; count <= COUNT; count += 2) {
            TELL_WAIT();
            WAIT_PARENT();
            snprintf(buf, sizeof(buf), "child: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("child: %d\n", count);
            TELL_PARENT(getppid());
        }
    } else {
        sleep(1);
        for (count = 1; count <= COUNT; count += 2) {
            TELL_WAIT();
            snprintf(buf, sizeof(buf), "parent: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("parent: %d\n", count);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }

    exit(0);
}
*/
/*
使子进程先执行不出现阻塞。
说明子进程执行
TELL_PARENT(getppid());
发送信号时，父进程已经执行
TELL_WAIT();
阻塞了信号，父进程不出现阻塞。
但是为什么之前使父进程先执行时子进程可能出现没有执行TELL_WAIT();的情况。
int main(int argc, char *argv[])
{
    int fd;
    char buf[MAXLINE];
    pid_t pid;
    int count = 1;

    fd = open("test_sig_sync_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    snprintf(buf, sizeof(buf), "parent: 0\n");
    if (write(fd, buf, strlen(buf)) == -1)
        err_sys("write error");
    printf("parent: 0\n");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        for (; count < COUNT; count += 2) {
            TELL_WAIT();
            snprintf(buf, sizeof(buf), "child: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("child: %d\n", count);
            TELL_PARENT(getppid());
            WAIT_PARENT();
        }
    } else {
        for (count += 1; count < COUNT; count += 2) {
            TELL_WAIT();
            WAIT_CHILD();
            snprintf(buf, sizeof(buf), "parent: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("parent: %d\n", count);
            TELL_CHILD(pid);
        }
    }

    exit(0);
}
*/
/*
父进程的信号屏蔽和安排由子进程继承。
在父进程创建子进程之前执行TELL_WAIT();，父进程和子进程都设置了对相关信号的阻塞，这样第一次循环执行时不会出现
“父进程已经执行
TELL_CHILD(pid);
发送信号，但子进程尚未执行
TELL_WAIT();
阻塞信号，信号处理函数提前被调用，导致子进程执行
WAIT_PARENT();
时子进程被阻塞”
的情况，但为什么这样之后的循环也都不会出现子进程被阻塞了。
int main(int argc, char *argv[])
{
    int fd;
    char buf[MAXLINE];
    pid_t pid;
    int count = 0;

    fd = open("test_sig_sync_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    snprintf(buf, sizeof(buf), "parent: %d\n", count);
    if (write(fd, buf, strlen(buf)) == -1)
        err_sys("write error");
    printf("parent: %d\n", count);

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        for (count = 2; count <= COUNT; count += 2) {
            TELL_WAIT();
            WAIT_PARENT();
            snprintf(buf, sizeof(buf), "child: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("child: %d\n", count);
            TELL_PARENT(getppid());
        }
    } else {
        for (count = 1; count <= COUNT; count += 2) {
            TELL_WAIT();
            snprintf(buf, sizeof(buf), "parent: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("parent: %d\n", count);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }

    exit(0);
}
*/
/*
未出现阻塞。
这个版本逻辑上有合理之处，父进程执行TELL_WAIT();后，父进程等待子进程先运行的过程中使用了一次同步，循环中是重新调用TELL_WAIT();，用于计数过程中进行同步，不会出现未进行同步就重新设置对相关信号阻塞的情况。
但还是有问题，父进程等待子进程先运行并不能保证子进程在父进程重新调用TELL_WAIT();之前重新调用TELL_WAIT();，因此，第一次循环执行时父进程和子进程都设置了对相关信号的阻塞都不能保证，此外，在之后的循环中为什么父进程发送信号时子进程已经设置了对相关信号阻塞的问题还存在。
*/
int main(int argc, char *argv[])
{
    int fd;
    char buf[MAXLINE];
    pid_t pid;
    int count = 0;

    fd = open("test_sig_sync_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    snprintf(buf, sizeof(buf), "parent: %d\n", count);
    if (write(fd, buf, strlen(buf)) == -1)
        err_sys("write error");
    printf("parent: %d\n", count);

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        TELL_PARENT(getppid());
        for (count = 2; count <= COUNT; count += 2) {
            TELL_WAIT();
            WAIT_PARENT();
            snprintf(buf, sizeof(buf), "child: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("child: %d\n", count);
            TELL_PARENT(getppid());
        }
    } else {
        WAIT_CHILD();
        for (count = 1; count <= COUNT; count += 2) {
            TELL_WAIT();
            snprintf(buf, sizeof(buf), "parent: %d\n", count);
            if (write(fd, buf, strlen(buf)) == -1)
                err_sys("write error");
            printf("parent: %d\n", count);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }

    exit(0);
}
