/* 
*
* Linked Lists adapted from Assignment 1 of Comp20003 by Upnishadd Ksharma
* The scanning in of the data set and formation of linked lists was taken and built upon for further implementation
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "linkedlists.h"

// Malloc an empty linked list
list_t *make_empty_list(void) {
	list_t* list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = NULL;
    list->foot = NULL;
    list->count = 0;
	return list;
}

/* Malloc a node and assign `value` to node->data inserting at the 
foot of the list 
*/
list_t *insert_at_foot(list_t *list, data_t value) {
	node_t *temp;
	temp = (node_t*)malloc(sizeof(*temp));
	assert(list!=NULL && temp!=NULL);
	temp->data = value;
	temp->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = temp;
	} else {
		list->foot->next = temp;
		list->foot = temp;
	}
    
    list->count++;
	return list;
}

// Free all nodes of the list
void free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

// Unique Functions

// Scan all inputs in `stream` and create a dictionary (linked list) 
list_t *build_data_list(list_t *list, FILE* stream) {

	char *insert_string = NULL;
    size_t insert_string_buffer_length = 0;
    char *remaining_string;
	int len;
    // Scan until no more new lines are found starting with `footpath_id`
    while(getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream) > 0) {
        node_t temp;
        
        /* Replace newline with null terminator 
        (process is repeated several times in the following code)
        */
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        
        temp.data.footpath_id = atoi(insert_string);
        
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);

        /* Concat with the following string if initial string 
        starts with " indicating in-string delim.
        */ 
        if(insert_string[0] == '\"') {
            char *str = insert_string + 1;
            strcpy(temp.data.address, str);

            getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
            len = strlen(insert_string);
            insert_string[len - 2] = '\0';

            strcat(temp.data.address, insert_string);
        }
        else {
            insert_string[len - 1] = '\0';
            strcpy(temp.data.address, insert_string); 
        }
        
        // Scan in `clue_sa`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        if(insert_string[0] == '\"') {
            char *str = insert_string + 1;
            strcpy(temp.data.clue_sa, str);

            getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
            len = strlen(insert_string);
            insert_string[len - 2] = '\0';

            strcat(temp.data.clue_sa, insert_string);
        }
        else {
            insert_string[len - 1] = '\0';
            strcpy(temp.data.clue_sa, insert_string); 
        }
        
        // Scan in `asset_type`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        if(insert_string[0] == '\"') {
            char *str = insert_string + 1;
            strcpy(temp.data.asset_type, str);

            getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
            len = strlen(insert_string);
            insert_string[len - 2] = '\0';

            strcat(temp.data.asset_type, insert_string);
        }
        else {
            insert_string[len - 1] = '\0';
            strcpy(temp.data.asset_type, insert_string); 
        }
        
        // Scan in `deltaz`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.deltaz = strtold(insert_string, &remaining_string);;

        // Scan in `distance`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.distance = strtold(insert_string, &remaining_string);;
        
        // Scan in `grade1in`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.grade1in = strtold(insert_string, &remaining_string);;
        
        // Scan in `mcc_id`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.mcc_id = atoi(insert_string);
        
        // Scan in `mccid_int`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.mccid_int = atoi(insert_string);

        // Scan in `rlmax`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.rlmax = strtold(insert_string, &remaining_string);;

        // Scan in `rlmin`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.rlmin = strtold(insert_string, &remaining_string);;

        // Scan in `segside`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        if(insert_string[0] == '\"') {
            char *str = insert_string + 1;
            strcpy(temp.data.segside, str);

            getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
            len = strlen(insert_string);
            insert_string[len - 2] = '\0';

            strcat(temp.data.segside, insert_string);
        }
        else {
            insert_string[len - 1] = '\0';
            strcpy(temp.data.segside, insert_string); 
        }

        // Scan in `statusid`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.statusid = atoi(insert_string);
        
        // Scan in `streetid`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.streetid = atoi(insert_string);

        // Scan in `street_group`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.street_group = atoi(insert_string);

         // Scan in `start_lat`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.start_lat = strtold(insert_string, &remaining_string);
        
        // Scan in `start_lon`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.start_lon = strtold(insert_string, &remaining_string);
        
        // Scan in `remaining_string_lat`
        getdelim(&insert_string, &insert_string_buffer_length, DELIM_ASCII, stream);
        len = strlen(insert_string);
        insert_string[len - 1] = '\0';
        temp.data.end_lat = strtold(insert_string, &remaining_string);

        // Scan in `remaining_string_lon`
        getline(&insert_string, &insert_string_buffer_length, stream);
        temp.data.end_lon = strtold(insert_string, &remaining_string);

        // Insert street at start and end points
        temp.data.point.lat = temp.data.start_lat;
        temp.data.point.lon = temp.data.start_lon;
        list = insert_at_foot(list, temp.data);
        
        temp.data.point.lat = temp.data.end_lat;
        temp.data.point.lon = temp.data.end_lon;
        list = insert_at_foot(list, temp.data);
    }
    free(insert_string);
    return list;
}



