
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "racer.h"
#include "pt-cruisers.h"
#include "display.h"

#define BACK_TIRE 1

#define CAR_DEFAULT "~O=-------o>"

static long max_delay = DEFAULT_DELAY;

static void draw_moving_racer(Racer *racer) {
	set_cur_pos(racer->row, FINISH_LINE - racer->dist - 1);
	put(' ');
	for (int i = 0; i < MAX_CAR_LEN; i++) {
		set_cur_pos(racer->row, FINISH_LINE - racer->dist + i);
		put(racer->graphic[i]);
	}
}

static void draw_init_racer(Racer *racer) {
	for (int i = 0; i < MAX_CAR_LEN; i++) {
		set_cur_pos(racer->row, 1 + i);
		put(racer->graphic[i]);
	}
	set_cur_pos(racer->row, FINISH_LINE);
	put('|');
}

static void flat(Racer *racer) {
	racer->graphic[BACK_TIRE] = 'X';
	draw_moving_racer(racer);
}

static void lock() {
	int lockResult = pthread_mutex_lock(&runLock);
    if (lockResult) {
        perror("entering run() function");
        exit(errno);
    }
}

static void unlock() {
	int lockResult = pthread_mutex_unlock(&runLock);
    if (lockResult) {
        perror("exiting run() function");
        exit(errno);
    }
}

void move(Racer *racer) {
	
	lock();
	draw_init_racer(racer);
	unlock();

	while (racer->dist != 0) {

		int sleep_time = rand() % max_delay;
		
		usleep(sleep_time*1000);

		lock();

		if (sleep_time <= 3) {
			flat(racer);
			break;
		}

	    racer->dist--;
	    draw_moving_racer(racer);
    	unlock();
	}
    unlock();
    return;
}

void init_racers( long milliseconds ) {
	max_delay = milliseconds;
	clear();
}

Racer *make_racer( char *name, int position ) {
	Racer *racer = (Racer *) calloc(1, sizeof(Racer));
	racer->graphic = strdup(CAR_DEFAULT);
	FOR((long) strlen(name)) {
		racer->graphic[3 + i] = name[i];
	}
	racer->row = position;
	racer->dist = FINISH_LINE;
	return racer;
}

void destroy_racer( Racer *racer ) {
	free(racer->graphic);
	free(racer);
}

void *run( void *racer ){

	move((Racer *) racer);

	return NULL;
}