///
/// @file dissector.c
/// @brief Dissects a file of packets and returns the headers of those packets
///
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_PACKET_SIZE 2048

// Grabs the nibble out of a char, n = 0 is the first nibble and 1 is the second
// when looking at it like an array (left to right).
#define GET_NIBBLE(x, n) (x & (n == 0?0xF0:0x0F)) 

/// gets the bits requested out of one of the halfs of byte
/// 
/// @param x : the byte that we are pulling the bits out of
/// @param n : the side of the byte we are pulling from. If we are pulling from the
///        front half of the bits we use a 0 and a 1 for the back half
///
/// @return bytes shifted all to the left with half removed
int get_bytes(int x, int n) {
    if (n==0) {
        return GET_NIBBLE(x, n) >> 4;
    }
    return GET_NIBBLE(x, n);
}

/// prints out the field in the standard format
/// 
/// @param name : the name of the field to be printed
/// @param data : the data to be printed out in both hex and decimal
void print_field(char *name, int data) {
    printf("%s:\t\t0x%x (%d)\n", name, data, data);
}

/// the main dissection program
/// 
/// @param argc : the number of arguments passed into the method
/// @param argv : the arguments passed into the method
///
/// @return EXIT_SUCCESS on a sucessful dissection
///         EXIT_FAILURE on a failed dissection
int main(int argc, char *argv[]) {
        
    if (argc == 1) {
        fprintf(stderr, "%s\n",
        	"usage: dissectPackets inputFile");
        return EXIT_FAILURE;
    }

    char *f_name = argv[1];

    FILE *file = fopen(f_name, "rb");

    if (file == NULL) {
    	perror("Failed to open input file ");
    	return EXIT_FAILURE;
    }

    int packet_count;

    int read_count = fread(&packet_count, sizeof(int), 1, file);

    if (read_count == 0 && ferror(file)) {
    	perror("The file was unable to be read ");
    } else if (read_count == 0 && feof(file)) {
        //printf("==== File %s contains 0 packets.\n", f_name);
    	return EXIT_SUCCESS;
    }

    printf("==== File %s contains %d Packets.\n", f_name, 
        packet_count);

    for (int i = 1; i <= packet_count; i++) {
    	
        printf("==>Packet %d\n", i);
    	
        unsigned char packet[MAX_PACKET_SIZE];
        int packet_size;
        read_count = fread(&packet_size, sizeof(int), 1, file);
        if (read_count == 0) {
            fprintf(stderr, "Failed to read count of packets.\n");
            return EXIT_SUCCESS;
        }

    	read_count = fread((void *) packet, sizeof(char), packet_size, file);

	    if (read_count == 0 && ferror(file)) {
	    	perror("The file was unable to be read ");
	    } else if (read_count == 0 && feof(file)) {
	    	printf("EOF\n");
	    	return EXIT_SUCCESS;
	    }

        print_field("Version", get_bytes(packet[0], 0));
        print_field("IHL (Header Length)", get_bytes(packet[0], 1));
        print_field("Type of Service (TOS)", packet[1]);
        int temp;
        memcpy(&temp, &packet[2], sizeof(temp));
        print_field("Total Length", ntohs(temp));
        memcpy(&temp, &packet[4], sizeof(temp));
        print_field("Identification", ntohs(temp));
        memcpy(&temp, &packet[6], sizeof(temp));
        print_field("IP Flags", packet[6] & 0xE0);
        print_field("Fragment Offset", ntohs(temp) & 0x1F);
        print_field("Time To Live (TTL)", packet[8]);
        char *protocol;

        switch(packet[9]) {
            case 1:
                protocol = "ICMP";
                break;
            case 2:
                protocol = "IGMP";
                break;
            case 6:
                protocol = "TCP";
                break;
            case 9:
                protocol = "IGRP";
                break;
            case 17:
                protocol = "UDP";
                break;
            case 47:
                protocol = "GRE";
                break;
            case 50:
                protocol = "ESP";
                break;
            case 51:
                protocol = "AH";
                break;
            case 57:
                protocol = "SKIP";
                break;
            case 88:
                protocol = "EIGRP";
                break;
            case 89:
                protocol = "OSPF";
                break;
            case 115:
                protocol = "L2TP";
                break;
            default:
                protocol = "";
        }

        printf("Protocol:\t\t%s 0x%x (%d)\n", protocol, packet[9], packet[9]);
        memcpy(&temp, &packet[10], sizeof(temp));
        print_field("Header Checksum", ntohs(temp));
        printf("Source Address:\t\t%d.%d.%d.%d\n", packet[12], packet[13], packet[14], packet[15]);
        printf("Destination Address:\t\t%d.%d.%d.%d\n", packet[16], packet[17], packet[18], packet[19]);
    }

    fclose(file);


    return EXIT_SUCCESS;
}
