/// 
/// @file stack.c 
/// @brief The module that holds the stack and does all of the processing
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static int *stack;
static int size;

int st_size();
bool st_empty();
void st_create();
int st_pop();
void st_push(int item);
void st_delete();

int st_size() {
    return size-1;
}

/// Evaluates if the size of the stack is 0 ie. it is empty
/// @return bool true if the stack is 0 and false if not
bool st_empty() {
    return st_size() == 0;
}

void st_create() {
    //define the stack
    size = 1;
    stack = malloc(sizeof(int) * size);
}

int st_pop() {
    if (st_empty()) {
        st_delete();
        assert(!st_empty());
    }
    size--;
    int result = stack[size];
    int *new_stack = realloc(stack, sizeof(int)*size);
    assert(new_stack != NULL);
    stack = new_stack;
    return result;
}

void st_push(int item) {
    size++;
    int *new_stack = realloc(stack, sizeof(int)*size);
    assert(new_stack != NULL);
    stack = new_stack;
    stack[size-1] = item;
}

void st_delete() {
    free(stack);
}
