#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "linkedlists.h"

#define INPUT_STREAM 2
#define OUTPUT_STREAM 3

/* dict1.c
*
* Created by Upnishadd Ksharma (uksharma@student.unimelb.edu.au) 1263652 09/08/2022
*
* Implement the basic functionality for a dictionary allowing the lookup 
* of data by attribute.
* Attribute: address
*
* To run the program type:
* 
* ./dict1 1 tests/dataset_1.csv output.out < tests/test1.s1.in > output.stdout.out
* Second and Third command line inputs are a dataset 
* and the output file respectively.
*
*/

int main(int argc, char *argv[]) {

    char *ptr = NULL;
    size_t ptr_buffer_length = 0;
    
    FILE* stream = fopen(argv[INPUT_STREAM], "r");
    FILE* output = fopen(argv[OUTPUT_STREAM], "w");
    assert(stream != NULL);
    assert(output != NULL);

    list_t* list = make_empty_list();

    // Remove header from data
    getline(&ptr, &ptr_buffer_length, stream);

    // Create dictionary from dataset
    list = build_data_list(list, stream);
    
    while(getline(&ptr, &ptr_buffer_length, stdin) > 0) {
        // Replace newline with null terminator
        int len = strlen(ptr);
        ptr[len-1] = '\0';
        
        printf("%s --> ", ptr);

        // Search for address in dictionary
        findAddress(list->head, ptr, output);
    }

    free_list(list);
    free(list);
    free(ptr);
    fclose(stream);
    fclose(output);

    return 0;
}
