///
/// @file packman.c
/// @brief Reads in a file and either encodes or decodes it based on the
/// 	   pressence of a magic number in the file (0x80F0).
///
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packman_utils.h"
#include "packman_my_utils.h"

#define ENSURE_OPENED(file) ensure_opened(file, __FILE__, __LINE__, __func__, "f-nosuchfile");

char *strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p != NULL) {
        memcpy(p, s, size);
    }
    return p;
}

void ensure_opened(FILE *file_ptr, char* code_file, int line, const char* fname, char* msg) {
	char *str_fname = strdup(fname);
	if (!file_ptr) {
    	report_error(code_file, line, str_fname, msg );
    	free(str_fname);
    	exit(EXIT_FAILURE);
    }
    free(str_fname);
}

int main(int argc, char const *argv[])
{
	bool binary;

	if (argc != 3) {
		fprintf(stderr, "usage: packman firstfile secondfile\n"); // "secondfile of '-' means stdout"
		return EXIT_FAILURE;
	}

	FILE *file_one = fopen(argv[1], "rb");
	binary = true;
    // printf("0x%02x\n", binary);
    ENSURE_OPENED(file_one);

    unsigned short potential_magic;


    int read_count = fread(&potential_magic, sizeof(unsigned short), 1, file_one);

    if (read_count == 0 && ferror(file_one)) {
    	perror("The file was unable to be read ");
    } else if (read_count == 0) {
    	rewind(file_one);
        if (fread(&potential_magic, sizeof(uchar), 1, file_one) == 0) {
        	// Empty File
    		return EXIT_SUCCESS;
        }
    }

    if (potential_magic != get_magic()) {
    	fclose(file_one);
    	file_one = fopen(argv[1], "r");
    	binary = false;
    }

	ENSURE_OPENED(file_one);

	FILE *file_two = NULL;

	if (strcmp(argv[2], "-")) {
		file_two = fopen(argv[2], "wb");		
		ENSURE_OPENED(file_two);
	} else {
		file_two = stdout;
	}

	// do the actual encoding/decoding now
	if (binary) {
		decode(file_one, file_two);
	} else {
		encode(file_one, file_two);
	}

	fclose(file_one);
	if (strcmp(argv[2], "-")) {
		fclose(file_two);
	}
	return EXIT_SUCCESS;
}