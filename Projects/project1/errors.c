/// 
/// @file errors.c   
/// @brief The module to output an error if a function recives a bad input
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>

void make_error(char *command, char *args) {
    fprintf(stderr, "error: %s command usage: %s %s\n", command, 
            command, args);
}

void add_error () {
    make_error("add", "first_name last_name handle");
}

void friend_error () {
    make_error("friend", "handle1 handle2");
}

void unfriend_error () {
    make_error("unfriend", "handle1 handle2");
}

void print_error () {
    make_error("print", "handle");
}

void size_error () {
    make_error("size", "handle");
}

void stats_error () {
    make_error("stats", "handle");
}

void init_error () {
    make_error("init", "");
}

void quit_error () {
    make_error("quit", "");
}