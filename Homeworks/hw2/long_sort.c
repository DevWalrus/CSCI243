// 
// File: long_sort.c
// Description: use the algorithm in sort to sort an input from the
// command line into numerical order
// 
// @author Clinten Hopkins cmh3586
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "sorts.h"

/// A utility method to print out the long integers based on the order they
/// appear in the array of strings
///
/// @param count integer number of elements in the data param
/// @param data  long integer array to be output to the stdout
static void print_longs(int count, long data[] ) {
    for (int i = 0; i < count; ++i) {
        printf("%ld\n", data[i]);
    }
}

/// The function that gets the data from the command line and sends it to the
/// other methods to be sorted and then printed. This method also removes
/// any extra data that doesn't need to be sorted, like the name of the file
/// that called it. It returns an error if any of the input integers are out of
/// bounds.
///
/// @param argc  integer number of command line arguments includes program name
/// @param argv  strings: program-name commandline-argument
/// @returns EXIT_SUCCESS if no error, or EXIT_FAILURE on error
int main( int argc, char * argv[] ) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    long numbers[argc - 1];

    for (int i = 1; i < argc; ++i) {
        
        numbers[i-1] = strtol(argv[i], NULL, 10);

        if (numbers[i-1] == LONG_MIN) {
            fprintf(stderr, "\tvalue[%d] = %s out of range; using %ld\n", i-1, argv[i], LONG_MIN);
        } else if (numbers[i-1] ==  LONG_MAX) {
            fprintf(stderr, "\tvalue[%d] = %s out of range; using %ld\n", i-1, argv[i], LONG_MAX);
        }   

    }

    sort_longs( argc - 1, numbers );

    print_longs( argc - 1,  numbers );

    return EXIT_SUCCESS;
}
