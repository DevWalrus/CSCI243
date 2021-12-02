// 
// file: movie.c 
// 
// 
// @author csci243@cs.rit.edu 
// @author cmh3586@cs.rit.edu
// 
// // // // // // // // // // // // // // // // // // // // // // // // 


#include <stdio.h>
#include <string.h>

#include "movie.h"

/// Test if two movies are equal

bool movie_equals(const Movie *m, const Movie *o)
{
    // Two movies are equal if their titles and directors are equal
    if((NULL != m) && (NULL != o))
    {
        if ((0 == strcmp(m->director, o->director)) &&
            (0 == strcmp(m->title, o->title)))
        {
            return true ;
        }
    }
    return false ;
}

/// Initialize Movie structure with given Title and Director.

Movie *movie_new(char *t, char *d)
{
    Movie *m = NULL ;
 
    m = malloc(sizeof(Movie)) ;

    m->director = malloc(strlen(d) + 1) ;
    strcpy(m->director, d) ;

    m->title = malloc(strlen(t) + 1) ;
    strcpy(m->title, t) ;

    m->last_played = NULL;

    return m ;
}

/// destructor

void movie_delete(Movie *m)
{
    free(m->director) ;
    free(m->title) ;
    if(NULL != m->last_played)    mtime_delete(m->last_played) ;
    free(m) ;
}

/// get director

char *movie_get_director(const Movie *m) 
{
    char *tmp = malloc(strlen(m->director)+1) ;
    strcpy(tmp, m->director) ;
    return tmp ;
}

/// get title

char *movie_get_title(const Movie *m)
{
    char *tmp = NULL ;
    tmp = malloc(strlen(m->title)+1) ;
    strcpy(tmp, m->title) ;
    return tmp ;
}

/// get lastplayed

mtime *movie_get_last_played(const Movie *m)
{
    mtime *tmp = mtime_copy(m->last_played) ;
    return tmp ;
}

/// play

void movie_play(Movie *m, mtime *t)
{
    if (NULL != m->last_played)     free(m->last_played) ;
    m->last_played = t ;
}

/// copy

Movie *movie_copy(const Movie *m)
{
    Movie *d = NULL ;
    mtime *tmp = NULL ;

    d = malloc(sizeof(Movie)) ;

    d->director = malloc(strlen(m->director) + 1) ;
    strcpy(d->director, m->director) ;

    d->title = malloc(strlen(m->title) + 1) ;
    strcpy(d->title, m->title) ;

    if (NULL != m->last_played)
    {
        // copy the last played
        tmp = mtime_copy(m->last_played) ;
        d->last_played = tmp ;
    }
    else
    {
        // set last_played to NULL
        d->last_played = NULL ;
    }

    return d ;
}

/// tostring

char *movie_to_string(const Movie *m)
{
    char *sstr = NULL ;
    char *st = NULL ;
    char *sd = NULL ;
    char *tt = NULL ;
    int len = 0 ;

    st = movie_get_title(m) ;
    sd = movie_get_director(m) ;

    // calculate the total string length needed.
    len = strlen("Title: ") + strlen(st) +
                  strlen("  Director: ") + strlen(sd) + 1 ;

    if (NULL != m->last_played)
    {
        tt = mtime_to_string(m->last_played) ;
        len += strlen(" at ") + strlen(tt) ;
    }

    // allocate enough space for the movie
    sstr = malloc( len ) ;

    sprintf(sstr, "Title: %s  Director: %s", st, sd) ;

    if (NULL != m->last_played)
    {
        sstr = strcat(sstr, " at ") ;
        sstr = strcat(sstr, tt) ;
    }

    free(sd) ;
    free(st) ;
    free(tt) ;
    return sstr ;
}
