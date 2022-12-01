/* 
*
* Linked Lists adapted from Assignment 1 of Comp20003 by Upnishadd Ksharma
* The scanning in of the data set and formation of linked lists was taken and built upon for further implementation
*
*/
 

#ifndef _LINKEDLISTS_H_
#define _LINKEDLISTS_H_

            // Constant defnitions
#define MAX_STR_LEN 128
#define DELIM_ASCII 44 // Ascii value for ',' (comma)

            // Data definitions

typedef struct{
        long double lon;
        long double lat;
} point2D_t;

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
        point2D_t point;

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

#endif
