///
/// @file packman_my_utils.h
/// @brief Supporting file that does the main work of the Huffman algorithm.
///
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef PACKMAN_MY_UTILS_H_
#define PACKMAN_MY_UTILS_H_

/// takes in 2 file pointers, the latter could be stdout, and compresses the
/// data from the first pointer into the second using the Huffman algorithm
///
/// @param plain_fp the pointer to the file we are reading from
/// @param out_fp the pointer to the file we are writing to
///
/// @pre both file pointers must be open and able to be read
///
/// @post the plain_fp will not change but the out_fp will have the compressed
///       data inside it
void encode(FILE* plain_fp, FILE* out_fp);

/// takes in 2 file pointers, the latter could be stdout, and decompresses the
/// data from the first pointer into the second using the Huffman algorithm
///
/// @param bin_fp the pointer to the file we are reading from
/// @param out_fp the pointer to the file we are writing to
///
/// @pre both file pointers must be open and able to be read
///
/// @post the bin_fp will not change but the out_fp will have the decompressed
///       data inside it
void decode(FILE *bin_fp, FILE *out_fp);

#endif