// 
// File: text_sort.c
// Description: This uses the exchange sort algorithm to sort an array strings
// given to the file on the command line
// 
// @author Clinten Hopkins cmh3586
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>

#include "sorts.h"

/// A utility method to print out the strings based on the order they appear
/// in the array of strings
///
/// @param count integer number of elements in the data param
/// @param data  string array to be output to the stdout
static void print_strings(int count, char * data[] ) {
    for (int i = 0; i < count; ++i) {
        printf("%s\n", data[i]);
    }
}

/// The function that gets the data from the command line and sends it to the
/// other methods to be sorted and then printed. This method also removes
/// any extra data that doesn't need to be sorted, like the name of the file
/// that called it.
///
/// @param argc  integer number of command line arguments includes program name
/// @param argv  strings: program-name commandline-argument
/// @returns EXIT_SUCCESS if no error, or EXIT_FAILURE on error
int main( int argc, char * argv[] ) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    char * strings[argc - 1];

    for (int i = 1; i < argc; ++i) {
        strings[i-1] = argv[i];
    }

    sort_strings( argc - 1, strings);

    print_strings( argc - 1,  strings );

    return EXIT_SUCCESS;
}

