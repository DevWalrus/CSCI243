/// 
/// @file amici.h   
/// @brief The main methods in the social media app Amici
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef AMICI_H_DEFINED
#define AMICI_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "table.h"
#include "person.h"
#include "process.h"

/// Main function to run the social media app
///
/// @returns EXIT_SUCCESS when the app was quit using "quit" or 
///          EXIT_FAILURE when the app was quit because of a unfixable error
int main(void);

#endif

