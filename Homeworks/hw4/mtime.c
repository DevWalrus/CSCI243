// 
// file: mtime.c
// 
// Implementation of the mtime functions.
// 
// @author csci243@cs.rit.edu 
// 
// // // // // // // // // // // // // // // // // // // // // // // // 


#include <stdlib.h>
#include <stdio.h>
#include "mtime.h"

/// allocate space for a mtime structure and populate

mtime *mtime_new(int hour, int min, char *tod)
{
    char *mtod ;
    mtod = malloc(3 * sizeof(char)) ;   // tod is always two characters
    mtime *t = malloc(sizeof(mtime)) ;

    /* verify hour, minute and tod values */
    hour = hour % 12 ;
    if (0 == hour)
    {
        hour = 12 ;
    }
    min = min % 60 ;

    // verify that the tod is "am" or "pm"
    if ((0 != strcmp(tod, "am")) && (0 != strcmp(tod, "pm")))
    {
        strcpy(mtod, "xm") ;
    }
    else
    {
        strcpy(mtod, tod) ;
    }

    /* initialize structure */
    t->hour = hour ;
    t->min = min ;
    t->timeofday = malloc((strlen(mtod) + 1) * sizeof(char)) ;
    strcpy(t->timeofday, mtod) ;

    // clean up before leaving
    free(mtod) ;

    return t ;
}

/// time destructor
void mtime_delete(mtime *t)
{
    free(t->timeofday) ;   // has to be done explicitly
    free(t) ;
}

/// copy a time structure
mtime *mtime_copy(const mtime *src)
{
    mtime *dest = NULL ;

    dest = malloc(sizeof(mtime)) ;

    dest->hour = src->hour ;
    dest->min = src->min ;
    dest->timeofday = malloc((strlen(src->timeofday) + 1) * sizeof(char)) ;
    strcpy(dest->timeofday, src->timeofday) ;

    return dest ;
}

/// mtime_get_hour

int mtime_get_hour(const mtime *t)
{
  return t->hour;
}

/// mtime_get_minute

int mtime_get_minute(const mtime *t)
{
  return t->min;
}

// mtime_get_TOD

char *mtime_get_TOD(const mtime *t)
{
    return t->timeofday ;
}

/// convert the contents of an mtime structure

char *mtime_to_string(const mtime *t)
{
    char *tstr = NULL ;

    //allocate enough space for the time as a string
    tstr = malloc((2 + 1 + 2 + 2 + 1) * sizeof(char)) ;

    // put the string together
    sprintf(tstr, "%2d:%02d%s", mtime_get_hour(t), mtime_get_minute(t),
            t->timeofday) ;

    return tstr ;
}
