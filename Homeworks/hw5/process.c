/// 
/// @file process.c 
/// @brief The helper module that does all the calucations and stack 
///     manipulation
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "stack.h"

void multiply() {
    int a = st_pop();
    int b = st_pop();
    st_push(a*b);
}

void add() {
    int a = st_pop();
    int b = st_pop();
    st_push(a+b);
}

void subtract() {
    int a = st_pop();
    int b = st_pop();
    st_push(b-a);
}

void divide() {
    int a = st_pop();
    int b = st_pop();
    if (b == 0) {
        fprintf(stderr, "error: divide by 0: %d / %d\n", a, b);
        st_push(a);
    } else {
        st_push(round(b / ((double) a)) );
    }
}

void mod() {
    int a = st_pop();
    int b = st_pop();
    if (b == 0) {
        fprintf(stderr, "error: divide by 0: %d / %d\n", a, b);
        st_push(a);
    } else {
        st_push(b % a);
    }
}

void power() {
    double a = (double) st_pop();
    double b = (double) st_pop();
    st_push((int) pow(b, a));
}

void pop_print() {
    int a = st_pop();
    printf("%d\n", a);
}

void size() {
    printf("%d\n", st_size());
}

void bye() {
    st_delete();
    printf("ok\n");
    exit(0);
}
