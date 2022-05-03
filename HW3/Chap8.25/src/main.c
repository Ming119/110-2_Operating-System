/*
 *  Chap8.25/src/main.c
 *
 *  Programming Problem Chap. 8.25
 *  
 *  108590050 李浩銘
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PAGE_SIZE 4096

void usage(char *programName)
{
    printf("Usage:\n\t%s <address>\n", programName);
}

int main(int argc, char* argv[]) {

    if ((argc == 2 && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) ||argc != 2) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    unsigned int address = atoi(argv[1]);
    unsigned int pageNum = floor(address / PAGE_SIZE);
    unsigned int offset  = address - (pageNum * PAGE_SIZE);

    printf("The address %u contains:\npage number = %u\noffset = %u\n",address, pageNum, offset);

    exit(EXIT_SUCCESS);
}