// 
// file: mtime.h
// 
// Header file for movie time functions
// 
// @author csci243@cs.rit.edu 
// 
// // // // // // // // // // // // // // // // // // // // // // // // 


#ifndef TIME_H_DEFINED
#define TIME_H_DEFINED

#include <string.h>

// define a type for the time structure

typedef struct mtime_
{
    int   hour;          ///< integer hour
    int   min;           ///< integer minute
    char *timeofday;     ///< string representation
} mtime ;

// construct a time structure
// @param hour integer for this hour
// @param min integer for this minute
// @param tod string for this time of day (e.g. "am" or "pm")
// @return dynamically allocated time structure

mtime *mtime_new(int hour, int min, char *tod) ;

// delete a time structure
// @param t time pointer to process

void mtime_delete(mtime *t) ;

// copy a time structure (create space if needed)
// @param src time pointer to process
// @return dynamically allocated copy of time structure

mtime *mtime_copy(const mtime *src);

// @param t time pointer
// @return this time's hour

int mtime_get_hour(const mtime *t);

// @param t time pointer to process
// @return this time's minutes

int mtime_get_minute(const mtime *t);

// @param t time pointer to process
// @return this time's am/pm string

char *mtime_get_TOD(const mtime *t);

// @param t time pointer to process
// @return a string representation of the time

char *mtime_to_string(const mtime *t) ;

#endif
