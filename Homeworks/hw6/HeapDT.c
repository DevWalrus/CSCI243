/// 
/// @file HeapDT.c   
/// @brief The implementation of the Abstract Data Type (ADT) Heap. This
/// This is designed to restict the end user's ability to see any implementation
/// deatils regarding the type. It takes any data type that can be converted
/// void * types.
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "HeapDT.h"

static struct heap_s {
    size_t capacity;
    size_t size;
    int (*cmp_fun_ptr)(const void *, const void *);
    void (*print_item_ptr)(const void *, FILE *);
    const void **data;
} heap_s;

/// @returns The index of the parent node of index i in the array
static size_t parent(int i) {
    return (i-1)/2;
}

/// @returns The index of the left child node of index i in the array
static size_t left_child(int i) {
    return 2*i + 1;
}

/// @returns The index of the right child node of index i in the array
static size_t right_child(int i) {
    return 2*i + 2;
}

/// Calculates the index of the value that should go first based on the 
/// comparison function provided by the user on heap generation. The
/// nodes being compared are: 
///     - index
///     - left child of index (if in the heap)
///     - right child of indes (if in the heap)
/// 
/// @param heap the heap we will be looking at to do the compaison
/// @param index the parent node we will be using to initiate the comparison
/// @returns The index of the parent node of index i in the array
static int first_of_three(struct heap_s *heap, int index) {

    const void **data = heap->data;
    size_t left_i = left_child(index);
    size_t right_i = right_child(index);
    const void *this_v = data[index];
    if (right_i < heap->size) {
        const void *left_v = data[left_i];
        const void *right_v = data[right_i];
        if (heap->cmp_fun_ptr(left_v, this_v) || heap->cmp_fun_ptr(right_v, this_v)) {
            if (heap->cmp_fun_ptr(left_v, right_v)) {
                return left_i;
            } else {
                return right_i;
            }
        } else {
            return index;
        }
    } else if (left_i < heap->size) {
        const void *left_v = data[left_i];
        if (heap->cmp_fun_ptr(left_v, this_v)) {
            return left_i;
        } else {
            return index;
        }
    } else {
      return index;
    }
}

/// (Ideally) Starts at the bottom of the heap and compares the given node to
/// it's parent, swapping if the comparison function provided says we should
/// which then will create the desired heap structure (usually min or max heap)
/// 
/// @param heap the heap we will be looking at to do the comparison
/// @param startIndex the child node we will be using to initiate the comparison
static void shift_up (struct heap_s *heap, int start_index) {

    int i = start_index;
    const void **data = heap->data;
    while (i > 0 && !heap->cmp_fun_ptr(data[parent(i)], data[i])) {
        const void *temp = data[parent(i)];
        data[parent(i)] = data[i];
        data[i] = temp;
        i = parent(i);
    }

}

/// (Ideally) Starts at the top of the heap and compares the given node to
/// it's children (using the helper function first_of_three), swapping if the 
/// comparison function provided says we should which then will create the 
/// desired heap structure (usually min or max heap)
/// 
/// @param heap the heap we will be looking at to do the comparison
/// @param startIndex the parent node we will be using to initiate the comparison
static void shift_down(struct heap_s *heap, int start_index) {

    size_t i = start_index;
    const void **data = heap->data;
    size_t swap_i = first_of_three(heap, i);
    while (swap_i != i) {
        const void *temp = data[swap_i];
        data[swap_i] = data[i];
        data[i] = temp;
        i = swap_i;
        swap_i = first_of_three(heap, i);
    }
    
}

// Creates a new heap
Heap hdt_create(size_t capacity,
               int (*cmp_fun)( const void * lhs, const void * rhs ),
               void (*print_item)( const void * item, FILE * outfp ) ) {
    struct heap_s *new;

    new = malloc(sizeof(heap_s));
    assert(new != NULL);

    new->capacity = capacity;
    new->size = 0;
    new->data = malloc(sizeof(void *) * new->capacity);
    if (new->data == NULL) {
        free(new);
        assert(new->data != NULL);
    }
    new->cmp_fun_ptr = cmp_fun;
    new->print_item_ptr = print_item;
    return (Heap) new;
}

// Destroys a heap
void hdt_destroy(Heap a_heap) {
    struct heap_s *heap = (struct heap_s *) a_heap;
    free(heap->data);
    free(heap);
}

// Grabs the current size of the used positions in the heap
size_t hdt_size(Heap a_heap) {
    struct heap_s *heap = (struct heap_s *) a_heap;
    return heap->size;
}

// Grabs the top item and returns it to the user
const void * hdt_top(const Heap a_heap) {
    struct heap_s *heap = (struct heap_s *) a_heap;
    const void *result = heap->data[0];
    return result;
}

// Removes the top item in the heap, shifting everything else up if needed
void * hdt_remove_top(Heap a_heap) {
    struct heap_s *heap = (struct heap_s *) a_heap;
    const void **data = heap->data;
    const void *result = data[0];
    data[0] = data[--heap->size];
    shift_down(heap, 0);
    return (void *) result;

}

// Adds a new item to the top of the heap, shifting everything else down if needed
void hdt_insert_item(Heap a_heap, const void * item) {

    struct heap_s *heap = (struct heap_s *) a_heap;
    size_t size = ++(heap->size);

    if (size > heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, sizeof(void *) * heap->capacity);
        if (heap->data == NULL) {
            free(heap);
            assert(heap->data != NULL);
        }
    }

    (heap->data)[heap->size - 1] = item;
    shift_up(heap, heap->size - 1);
}

// Prints the heap to a given output file
void hdt_print(Heap a_heap, FILE * outfp) {
    struct heap_s *heap = (struct heap_s *) a_heap;
    const void **data = heap->data;
    for (size_t i = 0; i < heap->size; i++) {
        heap->print_item_ptr(data[i], outfp);
    }
}
