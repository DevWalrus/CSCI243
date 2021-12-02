/// 
/// @file amici.c   
/// @brief The main module to run the social media app Amici
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "table.h"
#include "person.h"
#include "process.h"

#define LINE_MAX 1024

typedef struct quick_functions{
    char *str;
    void (*process) (Table *, int, char **);
} quick_f_t;

quick_f_t table[] = {
    {"add", add}, {"friend", friend}, {"unfriend", unfriend}, {"print", print}, 
    {"size", size}, {"stats", stats}
};

/// Process the command line command into the program
/// @param table pointer to a hash table containing all of the users
/// @param command string the command provided
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
void process_command(Table *people, char *command, int argc, char *argv[argc]) {
    int num_entries = sizeof(table) / sizeof(quick_f_t);

    for(int i = 0; i < num_entries; i++) {
        char *t_command = table[i].str;
        if(!strcmp(t_command, command)) {
            table[i].process(people, argc, argv);
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

/// Removes a blank "" argument from the list
/// @param argc int value representing the number of arguments provided after 
/// the command was called
/// @param argv pointer to an array of strings holding the provided arguments
int remove_blank_arg(int argc, char **argv) {
    int result = 0;
    for (int i = 0; i < argc; i++) {
        bool found = false;
        if (!found) {
            if (!strcmp(argv[i], "")) {
                found = true;
                result = -1;
                if (i == argc-1) {
                    argv[i] = NULL;
                } else {
                    argv[i] = argv[i + 1];
                }
            }
        } else {
            if (i == argc-1) {
                argv[i] = NULL;
            } else {
                argv[i] = argv[i + 1];
            }
        }
    }
    return result;
}

// main
int main(void) {

    size_t (*str_hash_ptr)(const void *) = str_hash;
    bool (*str_equals_ptr)(const void *, const void *) = str_equals;
    void (*person_print_ptr)(const void *, const void*) = person_print;
    // void (*person_delete_ptr)(void *, void *) = person_delete;

    Table people_item = ht_create(str_hash_ptr, str_equals_ptr, 
                                  person_print_ptr, NULL);
    Table *people = &people_item;

    while (1) {

        printf("amici> ");
        char input[LINE_MAX];
        char *delim = " ";

        if (NULL != fgets(input, LINE_MAX, stdin)) {

            char *args[LINE_MAX];
            int i = 0;
            char *command = strtok(input, delim);
            strip_newline(strlen(command), command);

            if (!strcmp(command, "quit")) {
                quit(people, 0, NULL);
                return EXIT_SUCCESS;
            }

            if (!strcmp(command, "init")) {
                init(people, 0, NULL);
                people_item = ht_create(str_hash_ptr, str_equals_ptr, 
                                        person_print_ptr, NULL);
                people = &people_item;

                continue;
            }

            args[i] = strtok(NULL, delim);

            while(NULL != args[i]) {
                strip_newline(strlen(args[i]), args[i]);
                args[++i] = strtok(NULL, delim);
            }
            if (args[i] != NULL) {
                strip_newline(strlen(args[i]), args[i]);
            }
            i += remove_blank_arg(i, args);
            process_command(people, command, i, args);

        } else {

            printf("Something went wrong, please try again later.\n");
            quit(people, 0, NULL);
            return EXIT_FAILURE;

        }
    }

    printf("Something went wrong, please try again later.\n");
    quit(people, 0, NULL);
    return EXIT_FAILURE;
}

