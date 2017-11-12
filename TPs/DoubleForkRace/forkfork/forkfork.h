#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

/* type definie func_t */
typedef void (*func_t) (void *);

/* fonction qui executera le travail pour le petit fils de type func_t */
void f(void * arg);

/* fonction double fork */
void forkfork (func_t f, void *arg);

