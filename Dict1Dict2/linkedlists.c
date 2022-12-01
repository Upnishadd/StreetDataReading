/* Linked list defs:
 *
 * Adapted from implementation by Alistair Moffat: Jianzhong Qi, April 2022
 * Edited by: Upnishadd Ksharma 1263652
 *
 * Standard creation, additon and free functions have been adapted. 
 * Build_data_list, findAddress and others were specifically 
 * created for this project.
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

	char *ptr = NULL;
    size_t ptr_buffer_length = 0;

	int len;
    // Scan until no more new lines are found starting with `footpath_id`
    while(getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream) > 0) {
        node_t temp;
        
        /* Replace newline with null terminator 
        (process is repeated several times in the following code)
        */
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        
        temp.data.footpath_id = atoi(ptr);
        
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);

        /* Concat with the following string if initial string 
        starts with " indicating in-string delim.
        */ 
        if(ptr[0] == '\"') {
            char *str = ptr + 1;
            strcpy(temp.data.address, str);

            getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
            len = strlen(ptr);
            ptr[len - 2] = '\0';

            strcat(temp.data.address, ptr);
        }
        else {
            ptr[len - 1] = '\0';
            strcpy(temp.data.address, ptr); 
        }
        
        // Scan in `clue_sa`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        if(ptr[0] == '\"') {
            char *str = ptr + 1;
            strcpy(temp.data.clue_sa, str);

            getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
            len = strlen(ptr);
            ptr[len - 2] = '\0';

            strcat(temp.data.clue_sa, ptr);
        }
        else {
            ptr[len - 1] = '\0';
            strcpy(temp.data.clue_sa, ptr); 
        }
        
        // Scan in `asset_type`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        if(ptr[0] == '\"') {
            char *str = ptr + 1;
            strcpy(temp.data.asset_type, str);

            getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
            len = strlen(ptr);
            ptr[len - 2] = '\0';

            strcat(temp.data.asset_type, ptr);
        }
        else {
            ptr[len - 1] = '\0';
            strcpy(temp.data.asset_type, ptr); 
        }
        
        // Scan in `deltaz`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.deltaz = atof(ptr);

        // Scan in `distance`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.distance = atof(ptr);
        
        // Scan in `grade1in`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.grade1in = atof(ptr);
        
        // Scan in `mcc_id`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.mcc_id = atoi(ptr);
        
        // Scan in `mccid_int`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.mccid_int = atoi(ptr);

        // Scan in `rlmax`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.rlmax = atof(ptr);

        // Scan in `rlmin`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.rlmin = atof(ptr);

        // Scan in `segside`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        if(ptr[0] == '\"') {
            char *str = ptr + 1;
            strcpy(temp.data.segside, str);

            getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
            len = strlen(ptr);
            ptr[len - 2] = '\0';

            strcat(temp.data.segside, ptr);
        }
        else {
            ptr[len - 1] = '\0';
            strcpy(temp.data.segside, ptr); 
        }

        // Scan in `statusid`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.statusid = atoi(ptr);
        
        // Scan in `streetid`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.streetid = atoi(ptr);

        // Scan in `street_group`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.street_group = atoi(ptr);

        // Scan in `start_lat`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.start_lat = atof(ptr);
        
        // Scan in `start_lon`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.start_lon = atof(ptr);
        
        // Scan in `end_lat`
        getdelim(&ptr, &ptr_buffer_length, DELIM_ASCII, stream);
        len = strlen(ptr);
        ptr[len - 1] = '\0';
        temp.data.end_lat = atof(ptr);

        // Scan in `end_lon`
        getline(&ptr, &ptr_buffer_length, stream);
        temp.data.end_lon = atof(ptr);
        
        list = insert_at_foot(list, temp.data);
    }
    free(ptr);
    return list;
}

// Find all occurances of a specified address and print in `output`
void findAddress(struct node *head, char *ptr, FILE* output) {
    
    struct node *temp = head;
    
    int count = 0;
    fprintf(output,"%s\n", ptr);
    while(temp != NULL) {

        if(strcmp(ptr, temp->data.address) == 0) {
            fprintf(
                output,
                "--> footpath_id: %d || address: %s || clue_sa: %s || "
                "asset_type: %s || deltaz: %.2lf || distance: %.2lf || "
                "grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
                "rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d "
                "|| streetid: %d || street_group: %d || start_lat: %lf || "
                "start_lon: %lf || end_lat: %lf || end_lon: %lf || \n", 
                temp->data.footpath_id, temp->data.address, temp->data.clue_sa, 
                temp->data.asset_type, temp->data.deltaz, temp->data.distance, 
                temp->data.grade1in, temp->data.mcc_id, temp->data.mccid_int, 
                temp->data.rlmax, temp->data.rlmin, temp->data.segside, 
                temp->data.statusid, temp->data.streetid, 
                temp->data.street_group, 
                temp->data.start_lat, temp->data.start_lon, temp->data.end_lat, 
                temp->data.end_lon
                );
            count++;
        }

        temp = temp->next;
    }
    if(count != 0) {
        printf("%d\n", count);
    }
    else {
        printf("NOTFOUND\n");
    }
}

/* Sort dictionary and update `sorted_arr` holding 
one record for each unique occurances of grade1in
*/
void sort_list(list_t* list, data_t **sorted_arr) {
    
    // Store the last lowest value used
    double last_min = -1;
    
    int counter = 0;
    
    for(int i = 0; i < list->count; i++) {
        /* At the start of every iteration we wont have a current minimum 
        so we flag this and set 
        the first node greater than out 'last_min' as out current min 
        */
        bool is_min = false;
        struct node *temp = list->head;
        sorted_arr[i] = NULL;
        while(temp != NULL) {

            if(temp->data.grade1in > last_min) {

                if(is_min == false) {
                    counter++;
                    sorted_arr[i] = &temp->data;
                    is_min = true;
                }

                if(temp->data.grade1in < sorted_arr[i]->grade1in) {
                    sorted_arr[i] = &temp->data;
                }
            }
            temp = temp->next;
        }

        if(sorted_arr[i]) {
            last_min = sorted_arr[i]->grade1in; 
        }

        is_min = false;
    }
    sorted_arr[counter] = NULL;
}

// Search for the input into stdin in the sorted linked list
void list_cmp_grade1in(FILE* output, data_t **sorted_arr) {
    
    char *ptr = NULL;
    size_t ptr_buffer_length = 0;
    
    double grade1in;
    while(getline(&ptr, &ptr_buffer_length, stdin) > 0) {
        ptr[strlen(ptr) - 1] = '\0';
        grade1in = atof(ptr);

        double min_dist = fabs(grade1in - (sorted_arr[0]->grade1in));
        int match = 0;
        int i = 0;
        
        // Find the minimum distance between any element in the list and grade1in
        while(sorted_arr[i]) {
            double dist = fabs( (sorted_arr[i]->grade1in) - grade1in );
            if(dist < min_dist) {
                min_dist = dist;
                match = i;
            }
            i++;
        }
        
        print_sorted_list_arr(output, ptr, sorted_arr, match);
    }
    free(ptr);
}

// Print data from the dictionary that matches with the input
void print_sorted_list_arr(FILE* output, char *ptr, 
data_t **sorted_arr, int match) {

    fprintf(
        output,
        "%s-->\n footpath_id: %d || address: %s || clue_sa: %s ||"
        " asset_type: %s || deltaz: %.2lf || distance: %.2lf || "
        "grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
        "rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: "
        "%d || streetid: %d || street_group: %d || start_lat: %lf "
        "|| start_lon: %lf || end_lat: %lf || end_lon: %lf || \n", 
        ptr, sorted_arr[match]->footpath_id, sorted_arr[match]->address, 
        sorted_arr[match]->clue_sa, sorted_arr[match]->asset_type, 
        sorted_arr[match]->deltaz, sorted_arr[match]->distance, 
        sorted_arr[match]->grade1in, sorted_arr[match]->mcc_id, 
        sorted_arr[match]->mccid_int, sorted_arr[match]->rlmax, 
        sorted_arr[match]->rlmin, sorted_arr[match]->segside, 
        sorted_arr[match]->statusid, sorted_arr[match]->streetid, 
        sorted_arr[match]->street_group, sorted_arr[match]->start_lat, 
        sorted_arr[match]->start_lon, sorted_arr[match]->end_lat, 
        sorted_arr[match]->end_lon
    );
    
    printf("%s --> %0.1lf\n", ptr, sorted_arr[match]->grade1in);
}
