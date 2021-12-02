/// 
/// @file hpcalc.c 
/// @brief The main module to run calculator
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "process.h"
#include "stack.h"

#define LINE_MAX 100

typedef struct quick_functions{
    char *str;
    void (*process) ();
} quick_fun;

quick_fun table[] = {
    {"*", multiply}, {"+", add}, {"-", subtract}, {"/", divide}, {"%", mod}, 
    {"^", power}, {".", pop_print}, {".s", size}, {"bye", bye}
};

/// Add the the command line inputs into the stack for the program to process
/// @param table pointer to a hash table containing all of the users
/// @param command string the command provided
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
void process_input(char *command) {
    int num_entries = sizeof(table) / sizeof(quick_fun);
    for(int i = 0; i < num_entries; i++) {  
    // for every quick function in the table
        char *t_command = table[i].str;     
        // pull a command out of the table
        if(!strcmp(t_command, command)) {   
        // if the provided command is equal to the table command
            table[i].process();
            // run the method
            break;
        }
    }
}

/// Remove any extra new line chars
/// @param len int the length of the string
/// @param str string the string to strip
void strip_newline (int len, char *str) {

    if (str[len - 1] == '\n')
        str[len - 1] = '\0';

}

/// Main function to run the calculator
/// When the user quits using "bye" the quitting is done using exit(0)
/// @returns EXIT_FAILURE when the app was quit using ctrl+d
int main(void) {
    st_create();
    printf("hpcalc\n");

    while (1) {
        char input[LINE_MAX];
        char *delim = " ";

        if (NULL != fgets(input, LINE_MAX, stdin)) {
            // printf("%s\n", input);

            int i = 0;
            char *history[LINE_MAX];
            char *command = strtok(input, delim);
            history[i] = command;

            while(NULL != history[i] && history[i][0] != 10) {
                int num = 0;
                bool is_num = true;
                strip_newline(strlen(command), command);

                // printf("READING: %s\n", command);
                
                for (size_t j = 0; j < strlen(command); j++) {
                    if (!(isdigit(command[j]) || '-' == command[j])){
                        is_num = false;
                    }
                }

                if (is_num && strcmp("-", command)) {
                    num = (int) strtol(command, NULL, 10);
                    st_push(num);
                } else {
                    process_input(command);
                }

                command = strtok(NULL, delim);
                history[++i] = command;

            }
        } else {
            st_delete();
            exit(0);
            return EXIT_FAILURE;
        }
    }
    st_delete();
    exit(0);
    return EXIT_FAILURE;
}
