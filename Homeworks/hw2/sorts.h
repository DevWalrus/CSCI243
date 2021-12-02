//
// File: sort.h
// Description: The methods that sort the data based on type
//
// @author Clinten Hopkins cmh3586
//
// // // // // // // // // // // // // // // // // //  // // // // // // // // // // // // // // // // // //

#ifndef SORTS_H
#define SORTS_H


/// Sort an array of strings into alphabetical order with the "lowest" letter (or first letter of the alphabet) 
/// being displayed first and the "highest" being displayed last
///
/// @param count integer number of items to be sorted
/// @param data  string array to be sorted

void sort_strings( int count, char * data[] );


/// Sort an array of long integers into numerical order with the lowest number being displayed first and
/// the highest being displayed last
///
/// @param count integer number of items to be sorted
/// @param data  long integer array to be sorted

void sort_longs( int count, long data[] );

#endif
