/// 
/// @file process.h 
/// @brief The helper module that does all the calucations and stack 
///     manipulation
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef PROCESS_H
#define PROCESS_H

/// Does multiplication on the top 2 items in the stack and adds the 
/// product to the stack (removing the 2 items)
/// @pre The stack must have at least 2 items
/// @post The stack will have the product pushed onto it
void multiply();

/// Does addition on the top 2 items in the stack and adds the 
/// sum to the stack (removing the 2 items)
/// @pre The stack must have at least 2 items
/// @post The stack will have the sum pushed onto it
void add();

/// Does subtraction on the top 2 items in the stack and adds the 
/// result to the stack (removing the 2 items)
/// @pre The stack must have at least 2 items
/// @post The stack will have the result pushed onto it
void subtract();

/// Does division on the top 2 items in the stack and adds the 
/// result to the stack (removing the 2 items)
/// @pre The stack must have at least 2 items
/// @post The stack will have the result pushed onto it
void divide();

/// Does modulus on the top 2 items in the stack and adds the 
/// result to the stack (removing the 2 items)
/// @pre The stack must have at least 2 items
/// @post The stack will have the result pushed onto it
void mod();

/// Does power multiplication on the top 2 items in the stack and adds the
/// result to the stack (removing the 2 items)
/// @pre The stack must have at least 2 items
/// @post The stack will have the result pushed onto it
void power();

/// Removes the top item on the stack and prints it to stdout
/// @pre The stack must have at least 1 item
/// @post The stack will have the origional stack without the item popped
void pop_print();

/// Prints the size of the stack
void size();

/// Frees the stack and exits cleanly
void bye();

#endif
