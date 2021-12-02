// 
// file: movietest.c 
// 
// 
// @author csci243@cs.rit.edu 
// @author Clinten Hopkins cmh3586@cs.rit.edu
// 
// // // // // // // // // // // // // // // // // // // // // // // // 


#include <stdio.h>
#include <stdlib.h>

#include "movie.h"
#include "mtime.h"

/// main function
///
/// @return errorCode  error Code; EXIT_SUCCESS if no error

int main( void )
{
    mtime *atime = NULL ;

    Movie *movie1 = NULL ;
    Movie *movie2 = NULL ;
    Movie *movie3 = NULL ;

    printf( "Creating a time...\n" ) ;
    atime = mtime_new( 6, 30, "pm" ) ;

    printf( "Starting movie tests...\n" ) ;

    movie1 = movie_new( "Star Wars: Episode IV A New Hope", "George Lucas" ) ;
    printf( "First movie initialized...\n" ) ;

    char *director = movie_get_director( movie1 ) ;
    char *title = movie_get_title( movie1 ) ;
    printf( "The current movie1 movie is: %s by %s.\n", title, director) ;
    free( director ) ;
    free( title ) ;

    char * mstr = movie_to_string( movie1 ) ;
    printf( "Otherwise... %s\n", mstr ) ;
    free(mstr);

    movie_play( movie1, atime ) ;
    mstr = movie_to_string( movie1 ) ;
    printf( "After playing the movie... %s\n", mstr ) ;
    free(mstr);

    mtime *glp = movie_get_last_played( movie1 ) ;
    char *sglp = mtime_to_string(glp) ;
    director = movie_get_director( movie1 ) ;
    title = movie_get_title( movie1 ) ;
    printf( "The same movie referencing members is: %s by %s. Last played at: %s\n", 
             title, director, sglp ) ;
    free( director ) ;
    free( title ) ;
    mtime_delete( glp ) ;
    free( sglp ) ;

    movie_delete( movie1 ) ;

    director = malloc( sizeof( "Steven Spielberg" ) + 1 ) ;
    title = malloc( sizeof( "Jurassic Park" ) + 1 ) ;
    strcpy( director, "Steven Spielberg" ) ;
    strcpy( title, "Jurassic Park" ) ;
    movie2 = movie_new( title, director ) ;
    free( director ) ;
    free( title ) ;
    mstr = movie_to_string( movie2 ) ;
    printf( "The movie2 movie is: %s\n", mstr ) ;
    free(mstr);
    
    movie1 = movie_copy( movie2 ) ;
    mstr = movie_to_string( movie1 ) ;
    printf( "The copy of movie2 movie is: %s \n", mstr ) ;
    free(mstr);
    movie_delete( movie2 ) ;
    mstr = movie_to_string( movie1 ) ;
    printf( "After deleting the original, the copy of movie2 "
            "movie is ... %s\n", mstr ) ;
    free(mstr);

    char *pstr ;
    movie3 = movie_copy( movie1 ) ;
    if ( movie_equals( movie1, movie3 ) )
    {
        mstr = movie_to_string( movie1 ) ;
        pstr = movie_to_string( movie3 ) ;
        printf( "The movie3 movie %s\n"
                "    is the same as movie1 movie %s\n", pstr, mstr ) ;
        free( pstr ) ;
        free(mstr);
    }
    else {
        printf( "ERROR: movieCopy() failure!\n" ) ;
    }

    movie_delete( movie3 ) ;
    movie_delete( movie1 ) ;

    movie3 = movie_new( "A Bug's Life", "John Lasseter" ) ;
    mstr = movie_to_string( movie3 ) ;
    printf( "The current movie3 movie is: %s\n", mstr ) ;
    free(mstr);

    movie_play( movie3, mtime_new(4, 42, "am") ) ;

    mstr = movie_to_string( movie3 ) ;
    printf( "The current movie3 movie is: %s\n", mstr ) ;
    free( mstr ) ;

    //movie_delete( movie1 ) ;
    movie_delete( movie3 ) ;

    return EXIT_SUCCESS ;
}
