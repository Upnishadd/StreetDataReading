#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "linkedlists.h"

#define INPUT_STREAM 2
#define OUTPUT_STREAM 3

/* dict2.c
*
* Created by Upnishadd Ksharma (uksharma@student.unimelb.edu.au) 1263652 09/08/2022
*
* Construct an index on a single attribute and search on that attribute.
* Attribute: grade1in
*
* To run the program type:
* 
* ./dict2 2 tests/dataset_2.csv output.out < tests/test1.s2.in > output.stdout.out
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

    // Storage for sorted dictionary
    data_t **sorted_arr;
    sorted_arr = malloc((list->count + 1) * sizeof (*sorted_arr));
    
    // Sort the dictionary
    sort_list(list, sorted_arr);

    // Search for input in dictionary
    list_cmp_grade1in(output, sorted_arr);
 
   
    free(sorted_arr);
    free_list(list);
    free(list);
    free(ptr);
    fclose(stream);
    fclose(output);

    return 0;

}
