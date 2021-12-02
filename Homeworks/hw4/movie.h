// File:         movie.h
// Author        CS@RIT.EDU
// Description:  Module that represents a movie
//

#ifndef MOVIE_H_DEFINED
#define MOVIE_H_DEFINED

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "mtime.h"
 
/// This structure represents a Movie played by a streaming service.

typedef struct movie_s {
     char  *director ;        ///< string name of the director
     char  *title ;           ///< string name of the title
     mtime *last_played ;     ///< pointer to time object of last play
} Movie ;

/// @param t pointer to a string name of a movie title
/// @param d pointer to a string name of a director
/// @return pointer to a new Movie instance

Movie *movie_new(char *t, char *d) ;

/// delete the movie instance and free its associated memory
/// @param m pointer to a Movie instance

void movie_delete(Movie *m) ;

/// @param m pointer to a movie instance
/// @param o pointer to a second movie instance
/// @return non-zero if director and title are the same

bool movie_equals(const Movie *m, const Movie *o) ;

/// @param src pointer to a movie instance

Movie *movie_copy(const Movie *src) ;

/// @param m pointer to a movie instance
/// @return a copy of the director string

char *movie_get_director(const Movie *m) ;

/// @param m pointer to a movie instance
/// @return a copy of the title string

char *movie_get_title(const Movie *m) ;

/// record the last time movie played
/// @param m pointer to a movie instance
/// @param t pointer to a time object for this play time (NULL to unplay)

void movie_play(Movie *m, mtime *t) ;

/// get the last time the movie was played
/// @param m pointer to a movie instance
/// @return a pointer to the last play time

mtime *movie_get_last_played(const Movie *m) ;

/// @param m pointer to a movie instance
/// @return a string representation of the movie

char *movie_to_string(const Movie *m) ;

#endif

