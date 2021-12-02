
#ifndef PT_CRUISERS_H_
#define PT_CRUISERS_H_

#include <pthread.h>
#include <errno.h>

#define ALL_NUM_STR "0123456789"

#define FOR(x) for (long i = 0; i < x; i++)

#define handle_pthread_error(rc, msg) \
	do { errno = rc; perror(msg); exit(EXIT_FAILURE); } while (0)

long racers_count;

pthread_mutex_t runLock;

char *strdup();

#endif