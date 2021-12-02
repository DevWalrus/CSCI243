// file: warning.c
// description: faulty, incomplete code that needs repair.
// @author RIT CS Dept.
// @author Clinten Hopkins cmh3586
//
// ========================= INSTRUCTIONS =========================
//
// Add an author line above to contain your full name and login ID.
// Put your author line as the last author line.
// <br/>
// What you CAN change/remove:
//     - preprocessor statements
//     - statements in function bodies.
// What you CANNOT change:
//     - the compute function docstrings and declarations.
//

#include <stdio.h>
#include <stdlib.h>          // strtol returns an int from a C string

/// compute returns the year of a US presidential election in a weird way.
/// A presidential election occurs every 4 years, e.g. 2000, 2004, 2008, ...
///
/// First, compute calculates the year representing the millennium
/// using the century parameter value. For the purpose of this program,
/// the year representing the 'start' millennial year is the '0th' year.
/// For example, consider 1200 as the 'start' of the 13th century (1200-1299).
///
/// Second, compute adds the offset value to the millennial year.
///
/// Third, compute calculates whether offset is evenly divisible by 4.
/// Calculate the remainder of offset divided by 4 to decide what to do next.
///
/// If the remainder is 0, then subtract 4 from the millennial year value.
///
/// Otherwise, subtract the remainder from the millennial year.
///
/// Finally the function returns the value of that election year.
///
/// Examples:
///     compute( 20, 0) returns 1900 + 0 - 4 = 1896
///     compute( 20, 1) returns 1900 + 1 - 1 = 1900
///     compute( 20, 2) returns 1900 + 2 - 2 = 1900
///     compute( 20, 3) returns 1900 + 3 - 3 = 1900
///     compute( 20, 4) returns 1900 + 4 - 4 = 1900
///
///     compute( 20, 8) returns 1900 + 8 - 4 = 1904
///     compute( 20, 9) returns 1900 + 9 - 1 = 1908
///
/// @param century positive integer number of the current century AD
/// @param offset positive integer number of years after 'start' of a century
/// @return a presidential election year
/// @pre (century >= 18)
/// @pre if (century == 18) then (offset >= 89)
/// @pre if (century > 18) then (0 <= offset <= 99)

int compute( int century, int offset ) {

    int millennium = (century * 100) - 100;
    if (offset % 4  == 0) {
        return millennium + offset - 4; 
    } else {
        return millennium + offset - (offset % 4);
    }
}

/// output a usage message to stderr, standard error.
/// Use when the program has an incomplete command line.
/// @param message NUL-terminated C string to print

void usage( char message[] ) {
    fprintf( stderr, "%s", message );
}

/// The program prints the year of the previous presidential election
/// computed based on input of the century (AD) and the year offset from
/// the start of the century. The main inputs are command line arguments.
///
/// The main function converts the command line's century number and
/// year offset values to integers using the strtol library function that
/// converts a C string to an integer value. Then
/// it calls compute() passing century number and year offset as arguments.
///
/// A simple way to use the strtol function is like this:
///     Given a C string variable, str, that contains numeric digits,
///     this statement returns the integer numeric value in base 10:
/// 
///     int value = strtol( str, NULL, 10 );
///
/// The century-number is argv[1], and the year-offset is argv[2].
///
/// @see compute function that implements the algorithm.
///
/// @param argc integer value 3 for the number of command line tokens
/// @param argv array of C string references, the command line arguments,
///        and the type of argv is written as char * argv[]
///
/// @return 0 to tell the OS that the process ran successfully, OR
///         return 1 to tell the OS that the result was out of range.

int main( int argc, char * argv[] ) {

    if ( argc != 3 ) {
        usage( "usage: warning century year_offset\n" );
        return 1;
    }

    int century = strtol(argv[1], NULL, 10);
    int year_offset = strtol(argv[2], NULL, 10);

    int election_year = compute( century, year_offset );

    printf( "%d\n", election_year );

    // 1788 is the date of the first USA election.
    if ( election_year < 1788 ) return 1;
    return 0;
}

