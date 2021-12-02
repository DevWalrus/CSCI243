/// 
/// @file stack.c 
/// @brief The module that holds the stack and does all of the processing
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef STACK_H
#define STACK_H

/// Creates a new stack in the heap and sets the usable size to 0
/// @post The stack has enough memory allocated to fit one integer and has a
/// 	size of 0
void st_create();

/// Removes the top item in the stack and returns that. If the stack size is 0
/// the program will terminate.
/// @pre The stack must have at least 1 item
/// @post The stack will no longer have the top item and the size will decrease
/// 	by 1
/// @return int the item previously on top of the stack
int st_pop();

/// Adds a given integer to the stack
/// @param item int object to be pushed onto the stack
/// @post The stack will have the provided item added to it
void st_push(int item);

/// Calculates the size of the stack and returns it
/// @return int the size of the stack
int st_size();

/// Frees the stack
void st_delete();

#endif
