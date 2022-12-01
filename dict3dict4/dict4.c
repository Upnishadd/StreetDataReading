#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "linkedlists.h"
#include "tree.h"

/* dict4.c
*
* Created by Upnishadd Ksharma (uksharma@student.unimelb.edu.au) 1263652 06/09/2022
*
* Implement the basic functionality for a dictionary allowing the lookup 
* of data by based on a given rectangle
*
* To run the program type:
* 
* ./dict4 4 tests/dataset_1.csv output.out 144.969 -37.7975 144.971 -37.7955 < tests/test9.s4.in > output.stdout.out
* Second and Third command line inputs are a dataset 
* and the output file respectively.
* The following 4 are coords defining a rectangle
*
*/

int main(int argc, char *argv[]) {

    char* remaining_string;
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
    // Scan in rectangles from stdin and search for streets within rectangle
    while(getline(&input_string, &input_string_buffer_length, stdin) > 0) {

        list_t* streets = make_empty_list();

        rectangle2D_t temp;
        int len = strlen(input_string);
        input_string[len - 1] = '\0';
        printf("%s --> ", input_string);
        fprintf(output, "%s\n", input_string);
        
        // Break string into long doubles
        string = strtok(input_string, s);
        temp.bot_left.lon = strtold(string, &remaining_string);
        string = strtok(NULL, s);
        temp.bot_left.lat = strtold(string, &remaining_string);
        
        string = strtok(NULL, s);
        temp.top_right.lon = strtold(string, &remaining_string);
        string = strtok(NULL, s);
        temp.top_right.lat = strtold(string, &remaining_string);

        streets = find_within_rect(tree, temp, output, streets);

        // Convert linkedlist `streets` into an array which is then sorted on footpath_id
        data_t **sorted_arr;
        sorted_arr = malloc((streets->count + 1) * sizeof (*sorted_arr));
        assert(sorted_arr);

        int count = 0;
        node_t *curr = streets->head;
        while(curr != NULL) {
            sorted_arr[count] = &(curr->data);
            count++;
            curr = curr->next;
        }

        sort_arr(sorted_arr, count);
        // Print all unique streets
        for(int i = 0; i < count; i++){
            if(i == 0){
                print_tree_node(sorted_arr[i], output);
            }
            else{
                if(sorted_arr[i]->footpath_id != sorted_arr[i-1]->footpath_id){
                    print_tree_node(sorted_arr[i], output);
                }
            }
        }
        
        printf("\n");
        free(sorted_arr);
        free_list(streets);
        free(streets);
    }

    free_tree(tree);
    free_list(list);
    free(list);
    free(input_string);
    fclose(stream);
    fclose(output);
    return 0;
}
