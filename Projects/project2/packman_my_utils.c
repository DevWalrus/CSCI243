///
/// @file packman_my_utils.c
/// @brief Supporting file that does the main work of the Huffman algorithm.
///
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "packman_utils.h"
#include "packman_my_utils.h"
#include "HeapDT.h"

/// The max number of unique symbols being provided
#define MAX_CHAR_COUNT 256
/// The maximum length of a string using 256 unique symbols. Calculated by taking the ceiling(log base 2(256))
#define MAX_STR_LEN 8

// The lookup table that holds the symbol and binary (represented as symbol(index)->binary(string))
static char lut[MAX_CHAR_COUNT][MAX_CHAR_COUNT];

/// find lookup looks at the static lookup table and pulls out a symbol if the 
/// provided string of binary is in the tableif a provided symbol is not in 
/// the table it will return -1
///
/// @param str the binary to look for in string form
/// @return the symbol if the string is in the table, -1 otherwise
///
/// @pre the lookup table has been populated using use_lookup
///
/// @post the internal state of the lookup table has not changed.
static unsigned int find_lookup(const char* str) {
	for (int i = 0; i < MAX_CHAR_COUNT; i++) {
		if (!strcmp(lut[i], str)) {
			return i;
		}
	}
	return -1;
}

/// less-than compares entries as pointers to Tree_node values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
///
/// @return non-zero if *item1->freq < *item2->freq
///
/// @pre values are pointers to Tree_node values.
static int cmp_nodes( const void * item1, const void * item2 ) {
    Tree_node v1 = (Tree_node)item1;
    Tree_node v2 = (Tree_node)item2;
    return v1->freq < v2->freq;
}

/// recursivly lookes through a Tree_node and builds the binary strings
/// created by the number of lefts and rights taken to get to a symbol
///
/// @param root the root node that we will recursivly look through to make the
/// 			binary strings for the lookup table
/// @param initially an empty string that will over time hold the binary string
///        formed by the algorithm
static void make_lookup(Tree_node root, char* binary) {
	if (root->left) {
		char lbinary[MAX_CHAR_COUNT];
		strcpy(lbinary, binary);
		strcat(lbinary, "0");
		make_lookup(root->left, lbinary);
		char rbinary[MAX_CHAR_COUNT];
		strcpy(rbinary, binary);
		strcat(rbinary, "1");
		make_lookup(root->right, rbinary);
	} else {
		if (!strcmp(binary, "")) {
			binary = "0";
		}
        strcpy(lut[root->sym], binary);
	}
}

/// prints out a node in a way that allows me to see the frequency, only used
/// in the heap
///
/// @param node_v pointer to the node we want to print
/// @param out_fp pointer to the output file
static void print_node(const void * node_v, FILE * out_fp) {
	Tree_node node = (Tree_node) node_v;
	fprintf(out_fp, "Sym: 0x%x, Freq:%d\n", node->sym, node ->freq);
}

/// ensures that a file actually read/write some data, if not the method will
/// terminate the program
///
/// @param read_count the number of items read or written to a file
///
/// @post the program will do nothing on a read_count > 1, 
///       but will terminate otherwise
static void ensure_read_write(int read_count) {
	if (read_count == 0) {
    	perror("Failed to output to the file ");
    	exit(EXIT_FAILURE);
    }
}

void encode(FILE* plain_fp, FILE* out_fp) {
	
	Tree_node all_symbols[MAX_CHAR_COUNT];

	for(int i = 0; i < MAX_CHAR_COUNT; i++) {
		all_symbols[i] = create_tree_node(i, 0);
	}

	rewind(plain_fp);

	while (1) {
		uchar read_sym;
    	int read_count = fread(&read_sym, sizeof(uchar), 1, plain_fp);

    	if (ferror(plain_fp)) {
	    	perror("The file was unable to be read ");
	    }
	    if (read_count == 0) {
	    	break;
	    }
	    all_symbols[read_sym]->freq++;
    }

    size_t unique = 0;

    for(int i = 0; i < MAX_CHAR_COUNT; i++) {
		if (all_symbols[i]->freq != 0) {
			unique++;
		}
	}

	Heap symbol_heap = hdt_create(unique, cmp_nodes, print_node);

	for(int i = 0; i < MAX_CHAR_COUNT; i++) {
		Tree_node node = all_symbols[i];
		if (node->freq != 0) {
			hdt_insert_item(symbol_heap, (void *) node);
		} else {
			free_tree_node(all_symbols[i]);
		}
	}

	while(hdt_size(symbol_heap) > 1) {
		Tree_node lowest = hdt_remove_top(symbol_heap);
		Tree_node second_lowest = hdt_remove_top(symbol_heap);
		Tree_node combo = create_tree_node(NUL, lowest->freq + second_lowest->freq);
		combo->left=lowest;
		combo->right=second_lowest;
		hdt_insert_item(symbol_heap, (void *) combo);
	}

	Tree_node sorted = hdt_remove_top(symbol_heap);
	hdt_destroy(symbol_heap);
	make_lookup(sorted, "");

	unsigned int bit_a = 0;
	unsigned int index = 0;
	unsigned int *bit_a_a = (unsigned int *) calloc(sizeof(unsigned int), index + 1);
	assert(bit_a_a != NULL);
    int old_bin_out = 0;

	rewind(plain_fp);

	unsigned int bin_out_len = 0;

	while (1) {
		uchar read_sym;
    	int read_count = fread(&read_sym, sizeof(uchar), 1, plain_fp);

    	if (ferror(plain_fp)) {
	    	perror("The file was unable to be read ");
	    }
	    if (read_count == 0) {
	    	break;
	    }

	    char *bin_str = lut[read_sym];
	    int bin_len = strlen(bin_str);
	    bin_out_len += bin_len;
	    unsigned int cap = (32 * (index + 1));

	    if (bin_out_len < cap) {
		    bit_a |= (strtol(bin_str, NULL, 2) << (32 - bin_out_len % 32));
	    	bit_a_a[index] = bit_a;
	    } else {
	    	int overflow = bin_out_len - cap;
	    	int remaining = cap - old_bin_out;
	    	int i = 1;
	    	for(; i <= remaining; i++) {
	    		bit_a |= ((bin_str[i-1] - 48) << (32 - bin_out_len % 32));
	    	}
	    	bit_a_a[index] = bit_a;
	   	 	index++;
	    	bit_a_a = (unsigned int *) realloc(bit_a_a, sizeof(unsigned int) * (index + 1));
	    	assert(bit_a_a != NULL);
	    	memset(&bit_a_a[index], 0, sizeof(unsigned int));
	    	bit_a = 0;

	    	for(; i <= overflow+remaining; i++) {
	    		bit_a |= ((bin_str[i-1] - 48) << (32 - bin_out_len % 32));
	    	}
	    	bit_a_a[index] = bit_a;
	    }
	    old_bin_out = bin_out_len;
    }

    int read_count =  write_tree(out_fp, sorted);
	if (read_count == -1) {
    	perror("Failed to output to the file ");
    	exit(EXIT_FAILURE);
    }

    read_count = fwrite(&bin_out_len, 1, sizeof(unsigned int), out_fp); 
    ensure_read_write(read_count);

 	for (unsigned int i = 0; i <= index; i++) {
	    read_count = fwrite(&bit_a_a[i], 1, sizeof(unsigned int), out_fp); 
		ensure_read_write(read_count);
		fflush(out_fp);
	}	
	free(bit_a_a);
	free_tree_node(sorted);
}

void decode(FILE *bin_fp, FILE *out_fp) {

	rewind(bin_fp);

	Tree_node root = read_tree(bin_fp);

	// print_tree(root);

	unsigned int num_bits;

	int read_count = fread(&num_bits, sizeof(unsigned int), 1, bin_fp); 
    ensure_read_write(read_count);

    unsigned int index = ceil(num_bits/32.0);

    unsigned int *bit_a_a = (unsigned int *) calloc(sizeof(unsigned int), index);
    assert(bit_a_a != NULL);

    for (unsigned int i = 0; i < index; i++) {
	    read_count = fread(&bit_a_a[i], sizeof(unsigned int), 1, bin_fp);
		ensure_read_write(read_count);
	}	

	make_lookup(root, "");

	char temp[MAX_CHAR_COUNT];
	strcpy(temp, "");
	for (unsigned int i = 1; i <= num_bits; i++) {
		int bit_a_a_index = (i - 1)/32.0;
		int bit_shift = (i - 1) % 32;
		unsigned int reading = bit_a_a[bit_a_a_index] << bit_shift;
		if ((reading & 0x80000000) == 0x80000000) {
			strcat(temp, "1");
		} else {
			strcat(temp, "0");
		}

		int sym_i = find_lookup(temp);

		if (sym_i != -1) {
			fprintf(out_fp, "%c", sym_i);
			strcpy(temp, "");
		}

	}
	free(bit_a_a);
	free_tree_node(root);
}