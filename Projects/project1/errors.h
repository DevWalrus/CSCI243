/// 
/// @file errors.c   
/// @brief The module to output an error if a function recives a bad input
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

/// Create a message to be displayed to the stderr using a default format
/// @param command string representation of the command that was called
/// @param args string holding the correct format of the arguments
void make_error (char *command, char *args);

/// Send the error message to stderr if the add function recived a bad input
void add_error ();

/// Send the error message to stderr if the friend function recived a bad input
void friend_error ();

/// Send the error message to stderr if the unfriend function recived a bad input
void unfriend_error ();

/// Send the error message to stderr if the print function recived a bad input
void print_error ();

/// Send the error message to stderr if the size function recived a bad input
void size_error ();

/// Send the error message to stderr if the stats function recived a bad input
void stats_error ();

/// Send the error message to stderr if the init function recived a bad input
void init_error ();

/// Send the error message to stderr if the quit function recived a bad input
void quit_error ();

#endif