#include "apue.h"

void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);
void my_setbuf(FILE *, char *);

int main(int argc, char *argv[])
{
    FILE *fp;

    fputs("enter any character\n", stdout);
    if (getchar() == EOF)
        err_sys("getchar error");
    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL)
        err_sys("fopen error");
    if (getc(fp) == EOF)
        err_sys("getc error");
    pr_stdio("/etc/passwd", fp);
    exit(0);
}

void pr_stdio(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);
    if (is_unbuffered(fp))
        printf("unbuffered");
    else if (is_linebuffered(fp))
        printf("line buffered");
    else
        printf("fully buffered");
    printf(", buffer size = %d\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)

int is_unbuffered(FILE *fp)
{
    return(fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp)
{
    return(fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp)
{
    return(fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined(__SNBF)

int is_unbuffered(FILE *fp)
{
    return(fp->_flags & __SNBF);
}

int is_linebuffered(FILE *fp)
{
    return(fp->_flags & __SLBF);
}

int buffer_size(FILE *fp)
{
    reutnr(fp->_bf._size);
}

#elif defined(_IONBF)
/*
#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif
*/
int is_unbuffered(FILE *fp)
{
    return(fp->_flags & _IONBF);
}

int is_linebuffered(FILE *fp)
{
    return(fp->_flags & _IOLBF);
}

int buffer_size(FILE *fp)
{
#ifdef _LP64
    return(fp->_IO_buf_end - fp->_IO_buf_base);
#else
    return(BUFSIZ);
#endif
}

#else

#error unknown stdio implementation!

#endif
/*
void my_setbuf(FILE *fp, char *buf)
{
    setvbuf(fp, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}
*/
void my_setbuf(FILE *fp, char *buf)
{
    if (buf != NULL) {
        if (fp == stdin || fp == stdout)
            setvbuf(fp, buf, _IOLBF, BUFSIZ);
        else if (fp == stderr)
            setvbuf(fp, buf, _IONBF, BUFSIZ);
        else
            setvbuf(fp, buf, _IOFBF, BUFSIZ);
    } else {
        setvbuf(fp, buf, _IONBF, BUFSIZ);
    }
}
