#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "linkedlists.h"
#include "tree.h"


/* dict3.c
*
* Created by Upnishadd Ksharma (uksharma@student.unimelb.edu.au) 1263652 06/09/2022
*
* Implement the basic functionality for a dictionary allowing the lookup 
* of data by based on a latitude and longitude
*
* To run the program type:
* 
* ./dict3 3 tests/dataset_1.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test1.s3.in > output.stdout.out
* Second and Third command line inputs are a dataset 
* and the output file respectively.
* The following 4 are coords defining a rectangle
*
*/


int main(int argc, char *argv[]) {

    char *remaining_string;
    char *input_string = NULL;
    size_t input_string_buffer_length = 0;
    
    FILE* stream = fopen(argv[INPUT_STREAM], "r");
    FILE* output = fopen(argv[OUTPUT_STREAM], "w");
    assert(stream != NULL);
    assert(output != NULL);

    // Create a rectangle defined by cmd line arguments
    rectangle2D_t root;
    root.bot_left.lat = strtold(argv[Y_BOT_LEFT], &remaining_string);
    root.bot_left.lon = strtold(argv[X_BOT_LEFT], &remaining_string);
    root.top_right.lat = strtold(argv[Y_TOP_RIGHT], &remaining_string);
    root.top_right.lon = strtold(argv[X_TOP_RIGHT], &remaining_string);
    root.centre.lat = (root.bot_left.lat + root.top_right.lat) / 2;
    root.centre.lon = (root.bot_left.lon + root.top_right.lon) / 2;

    quadtreenode_t* tree;
    tree = make_root(root);

    list_t* list = make_empty_list();

    // Remove header from data
    getline(&input_string, &input_string_buffer_length, stream);

    // Create dictionary from dataset
    list = build_data_list(list, stream);
    
    // Convert list to tree
    tree = list_to_tree(list, tree);

    // Sort data arrays in tree nodes by footpath_id
    tree = tree_arr_sort(tree);

    char* string;
    const char s[2] = " ";
    // Scan in points from stdin and search for them within the tree, printing the street data
    while(getline(&input_string, &input_string_buffer_length, stdin) > 0) {
        point2D_t temp;
        int len = strlen(input_string);
        input_string[len - 1] = '\0';
        printf("%s --> ", input_string);
        fprintf(output,"%s\n", input_string);

        // Break string into long doubles
        string = strtok(input_string, s);
        temp.lon = strtold(string, &remaining_string);
        string = strtok(NULL, s);
        temp.lat = strtold(string, &remaining_string);

        search_tree(tree, temp, output);
        printf("\n");
    }

    free_tree(tree);
    free_list(list);
    free(list);
    free(input_string);
    fclose(stream);
    fclose(output);

    return 0;
}








