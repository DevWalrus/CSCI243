/// 
/// @file process.h
/// @brief The headers for the processing the functions given by the user 
/// to amici
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef PROCESS_H
#define PROCESS_H

/// Creates a new person with the given values
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains a string first_name, last_name, and handle
/// @pre the first_name and last_name strings must just be alpha chars
void add (Table *table, int argc, char **argv);

/// Joins 2 handles to become friends
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains 2 string handles
void friend (Table *table, int argc, char **argv);

/// Removes the bond between 2 friends
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains 2 string handles
void unfriend (Table *table, int argc, char **argv);

/// Prints out the provided user's friends
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains 1 string handle
void print (Table *table, int argc, char **argv);

/// Prints out the number of friends the provided user has
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains 1 string handle
void size (Table *table, int argc, char **argv);

/// Prints out the number of users and the number of friendships in the system
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains nothing
void stats (Table *table, int argc, char **argv);

/// Clears the hash table and resets the program for a new set of users
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains nothing
void init (Table *table, int argc, char **argv);

/// Cleanly exits the program
/// @param table pointer to a hash table containing all of the users
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
/// @pre argv contains nothing
void quit (Table *table, int argc, char **argv);

#endif