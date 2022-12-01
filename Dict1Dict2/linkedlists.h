/* Linked list defs:
 *
 * Adapted from implementation by Alistair Moffat: Jianzhong Qi, April 2022
 * Edited by: Upnishadd Ksharma 1263652
 * Standard creation, additon and free functions have been adapted 
 * build_data_list and findAddress were specifically created for this project
 */
 

#ifndef _DATA_H_
#define _DATA_H_

            // Constant defnitions
#define MAX_STR_LEN 128
#define DELIM_ASCII 44 // Ascii value for ',' (comma)

            // Data definitions
typedef struct {
        int footpath_id; 
        char address[MAX_STR_LEN + 1];
        char clue_sa[MAX_STR_LEN + 1];
        char asset_type[MAX_STR_LEN + 1];
        double deltaz;
        double distance;
        double grade1in;
        int mcc_id;
        int mccid_int;
        double rlmax;
        double rlmin;
        char segside[MAX_STR_LEN + 1];
        int statusid;
        int streetid;
        int street_group;
        double start_lat;
        double start_lon;
        double end_lat;
        double end_lon;
} data_t;

typedef struct node node_t;

struct node {
	data_t data;
	node_t *next;
};

typedef struct{
    node_t *head;
    node_t *foot;
    int count;
} list_t;



            // Function definition


// Malloc an empty linked list
list_t *make_empty_list(void);

/* Malloc a node and assign `value` to node->data inserting at the 
foot of the list 
*/
list_t *insert_at_foot(list_t *list, data_t value);

// Free all nodes of the list
void free_list(list_t *list);

// Scan all inputs in `stream` and create a dictionary (linked list)
list_t *build_data_list(list_t *list, FILE* stream);

// Find all occurances of a specified address and print in `output`
void findAddress(struct node *head, char *ptr, FILE* output);

/* Sort dictionary and update `sorted_arr` holding one record 
for each unique occurances of grade1in
*/
void sort_list(list_t* list, data_t **sorted_arr);

// Search for the input into stdin in the sorted linked list
void list_cmp_grade1in(FILE* output, data_t **sorted_arr);

// Print data from the dictionary that matches with the input
void print_sorted_list_arr(FILE* output, char *ptr,
 data_t **sorted_arr, int match);


#endif
