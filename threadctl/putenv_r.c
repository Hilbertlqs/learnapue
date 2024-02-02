#include <string.h>
#include <errno.h>
#include <pthread.h>

extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void)
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

/* 
 * man 3 putenv
 * NOTES
 *        The putenv() function is not required to be reentrant, and the one in glibc 2.0 is not, but the glibc 2.1 version is.
 * 
 *        Since  version  2.1.2,  the glibc implementation conforms to SUSv2: the pointer string given to putenv() is used.  In particular, this string becomes part of the environment; changing it
 *        later will change the environment.  (Thus, it is an error to call putenv() with an automatic variable as the argument, then return from the calling function while string is still part of
 *        the environment.)  However, glibc versions 2.0 to 2.1.1 differ: a copy of the string is used.  On the one hand this causes a memory leak, and on the other hand it violates SUSv2.
 * 
 *        The 4.4BSD version, like glibc 2.0, uses a copy.
 * 
 *        SUSv2 removes the const from the prototype, and so does glibc 2.1.3.
 * 
 *        The GNU C library implementation provides a nonstandard extension.  If string does not include an equal sign:
 * 
 *            putenv("NAME");
 * 
 *        then the named variable is removed from the caller's environment.
 */
int putenv_r(char *string)
{
    int i, len;
    
    char *key = NULL;
    key = strchr(string, '=');
    if (key == NULL) {
        /* man errno
         * is EINVAL appropriate? */
        return EINVAL;
    }
    len = key - string;

    pthread_once(&init_done, thread_init);

    pthread_mutex_lock(&env_mutex);
    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(string, environ[i], len) == 0) {
            environ[i] = string;
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    environ[i] = string;
    pthread_mutex_unlock(&env_mutex);

    return 0;
}
