
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "racer.h"
#include "display.h"
#include "pt-cruisers.h"

pthread_mutex_t runLock = PTHREAD_MUTEX_INITIALIZER;

char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);
    if (dst == NULL) {
    	fprintf(stderr, "Failed to duplicate string\n");
    	exit(EXIT_FAILURE);
    }
    strcpy(dst, src);
    return dst;
}

int main(int argc, char const *argv[])
{
	srand((unsigned) time(NULL));

	int pos = 1;

	if (argc < 3) {
		fprintf(stderr, "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
		return EXIT_FAILURE;
	}

	if (strspn(argv[pos], ALL_NUM_STR) == strlen(argv[pos])) {
		//process the time thing
		init_racers(strtol(argv[pos++], NULL, 10));
	} else {
		init_racers(DEFAULT_DELAY);
	}

	racers_count = argc-pos;
	pthread_t *threads = (pthread_t *) calloc(racers_count, sizeof(pthread_t));

	if (racers_count < 2) {
		fprintf(stderr, "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
		return EXIT_FAILURE;
	}

	Racer **racers = (Racer **) calloc(racers_count, sizeof(Racer *));

	FOR(racers_count) {
		if(strlen(argv[pos + i]) > MAX_NAME_LEN) {
			fprintf(stderr, "Error: racer names must not exceed length 6.\n");
			return EXIT_FAILURE;
		}
		racers[i] = make_racer(argv[pos + i], i + 1);
	}

    int rc = pthread_mutex_init( &runLock, NULL );

	FOR(racers_count) {
		rc = pthread_create(&threads[i], NULL, &run, (void *) racers[i]);
		if (rc) {
			char* thread_str = "";
			sprintf(thread_str, "%ld", i);
			char* error = "pthread_create ";
			strcat(error, thread_str);
			strcat(error, " failed");
			handle_pthread_error(rc, error);
		}
	}

	void *retval;

	FOR(racers_count) {
		pthread_join(threads[i], &retval);
	}

	FOR(racers_count) {
		destroy_racer(racers[i]);
	}

	free(threads);
	free(racers);

	set_cur_pos(racers_count + 1, 0);

	return EXIT_SUCCESS;
}