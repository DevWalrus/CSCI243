//
// file: test_HeapDT.c 
// 
// test_HeapDT.c is a simple test of a Heap abstract data type implementation.
// 
// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "HeapDT.h"


/// test_int_heap tests an integer heap.
///
/// @param max_flag is true if heap is a maxheap.

void test_int_heap() {

    Heap new_heap = hdt_create(5, NULL, NULL);

    printf("%ld\n", hdt_size(new_heap));

    hdt_destroy(new_heap);

}


/// main function runs tests using integer and char data payloads.
/// The tests use both a minheap and a maxheap.
///
/// @return EXIT_SUCCESS

int main( void ) {

    test_int_heap();     // minheap

    return EXIT_SUCCESS;
}

