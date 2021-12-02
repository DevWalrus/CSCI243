// 
// File: sorts.c
// Description: The algorithm that takes both integer and string arrays
// and sorts them into numberical and alphabetical order respectivly
// 
// @author Clinten Hopkins cmh3586
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sorts.h"

// A basic function to sort strings based on the exchange sort algorithm
void sort_strings( int count, char * data[] ) {
    int i, j; 
    char * temp;
    for ( i = 0; i < count - 1; ++i ) {
        for ( j = i + 1; j < count; ++j ) {
            if ( strcmp(data[i], data[j]) > 0 ) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}


// A basic function to sort long integers based on the exchange sort algorithm
void sort_longs( int count, long data[] ) {
    int i, j, temp;
    for ( i = 0; i < count - 1; ++i ) {
        for ( j = i + 1; j < count; ++j ) {
            if ( data[i] > data[j] ) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}
