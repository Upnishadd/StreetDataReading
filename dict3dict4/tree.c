#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "linkedlists.h"
#include "tree.h"

quadtreenode_t *make_root(rectangle2D_t root) {
	quadtreenode_t* tree;
	tree = (quadtreenode_t*)malloc(sizeof(*tree));
	assert(tree!=NULL);
	tree->rect = root;
    tree->status = 'w';
    tree->datapoint.data = malloc(sizeof(*(tree->datapoint.data)));
    assert(tree->datapoint.data);
    tree->datapoint.count = 0;
    tree->child = malloc(CHILDREN*sizeof(*(tree->child)));
    assert(tree->child);
    tree->child[0] = NULL;
    tree->child[1] = NULL;
    tree->child[2] = NULL;
    tree->child[3] = NULL;
    return tree;
}

quadtreenode_t *list_to_tree(list_t *list, quadtreenode_t *tree) {
    node_t *curr = list->head;
    while(curr != NULL) {
        tree = insert_in_tree(tree, &(tree->rect), 0, &(curr->data));
        curr = curr->next;
    }
    return tree;
}

quadtreenode_t *insert_in_tree(quadtreenode_t *tree, rectangle2D_t* prev_rect, int quadrant, data_t *data) {
    // If the parent is null, create a node and insert the data in
    if(tree == NULL){
        tree = make_node(prev_rect, quadrant, data);
    }

    // Insert data into white nodes and change to black (Only applicable for the first data insertion into empty tree)
    else if(tree->status == 'w'){
        tree->datapoint.data[tree->datapoint.count] = data;
        tree->status = 'b';
        tree->datapoint.count++;
    }
    
    // If the node is black, check if the data has the same point enlarge the data array and add the data in
    else if(cmp_points(&(tree->datapoint.data[0]->point), &(data->point)) == 0 && tree->status == 'b'){
        tree->datapoint.data = realloc(tree->datapoint.data, (tree->datapoint.count + 1) * sizeof(*(tree->datapoint.data)));
        assert(tree->datapoint.data);
        tree->datapoint.data[tree->datapoint.count] = data;
        (tree->datapoint.count)++;
    }
    
    // Creating Grey Nodes
    else{
        int curr_quad;

        // Shift the data in the black node to its respective NULL child
        if(tree->status == 'b') {
            tree->status = 'g';
            curr_quad = determine_quadrant(&(tree->datapoint.data[0]->point), &(tree->rect));
            for(int i = 0; i < tree->datapoint.count; i++){
                tree->child[curr_quad] = insert_in_tree(tree->child[curr_quad], 
                &(tree->rect), curr_quad, tree->datapoint.data[i]);
            }
        }
        /* Insert the data into the appropriate child 
        if not null it will traverse tree, otherwise base case will make new node
        */
        curr_quad = determine_quadrant(&(data->point), &(tree->rect));
        tree->child[curr_quad] = insert_in_tree(tree->child[curr_quad], &(tree->rect), curr_quad, data);
    }
    return tree;
}

int cmp_points(point2D_t *tree, point2D_t *data) {
    if(tree->lon == data->lon){
        if(tree->lat == data->lat){
            return 0;
        }
    }
    return -1;
}

int determine_quadrant(point2D_t *point, rectangle2D_t *rect) {
        if(point->lon <= rect->centre.lon){
                if(point->lat < rect->centre.lat){
                        return 0;
                }
                return 1;
        }
        else{
                if(point->lat < rect->centre.lat){
                        return 3;
                }
                return 2;
        }
}

rectangle2D_t determine_rect(rectangle2D_t *rect, int quad) {
        rectangle2D_t temp;
        if(quad == 0) {
                temp.bot_left = rect->bot_left;
                temp.top_right = rect->centre;
        }
        else if (quad == 1) {
                temp.bot_left = rect->bot_left;
                temp.bot_left.lat += (rect->centre.lat - rect->bot_left.lat);
                temp.top_right = rect->centre;
                temp.top_right.lat += (rect->centre.lat - rect->bot_left.lat);
        }
        else if (quad == 2) {
                temp.bot_left = rect->centre;
                temp.top_right = rect->top_right;
        }
        else {
                temp.bot_left = rect->bot_left;
                temp.bot_left.lon += (rect->centre.lon - rect->bot_left.lon);
                temp.top_right = rect->centre;
                temp.top_right.lon += (rect->centre.lon - rect->bot_left.lon);
        }
        temp.centre.lat = (temp.bot_left.lat + temp.top_right.lat) / 2;
        temp.centre.lon = (temp.bot_left.lon + temp.top_right.lon) / 2;
        return temp;
}

quadtreenode_t *make_node(rectangle2D_t* prev_rect, int quadrant, data_t *data) {
    quadtreenode_t* tree;

	tree = (quadtreenode_t*)malloc(sizeof(*tree));
	assert(tree!=NULL);
    tree->child = malloc(CHILDREN*sizeof(*(tree->child)));
    assert(tree->child);
    tree->datapoint.data = malloc(sizeof(*(tree->datapoint.data)));
    assert(tree->datapoint.data);
	
    tree->rect = determine_rect(prev_rect, quadrant);
    tree->status = 'b';
    tree->datapoint.data[0] = data;
    tree->datapoint.count = 1;
    tree->child[0] = NULL;
    tree->child[1] = NULL;
    tree->child[2] = NULL;
    tree->child[3] = NULL;

    return tree;
}

void sort_arr(data_t **data, int count) {
    // Use bubble sort to sort array
    int i, j;
    for(i = 0; i < (count - 1); i++){
        for(j = 0; j < (count - i - 1); j++){
            if(data[j]->footpath_id > data[j + 1]->footpath_id){
                data_t *temp;
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

quadtreenode_t *tree_arr_sort(quadtreenode_t *tree) {
    // Only sort black nodes.
    if(tree->status == 'g') {
        for(int i = 0; i < CHILDREN; i++){
            if(tree->child[i] != NULL){
                tree->child[i] = tree_arr_sort(tree->child[i]);
            }
        }
    }
    else{
        sort_arr(tree->datapoint.data, tree->datapoint.count);
    }
    return tree;
}

void print_tree_node(data_t *data, FILE* output) {
    fprintf(output , 
                "--> footpath_id: %d || address: %s || clue_sa: %s || "
                "asset_type: %s || deltaz: %.2lf || distance: %.2lf || "
                "grade1in: %.1lf || mcc_id: %d || mccid_int: %d || "
                "rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d "
                "|| streetid: %d || street_group: %d || start_lat: %lf || "
                "start_lon: %lf || end_lat: %lf || end_lon: %lf || \n",   
                data->footpath_id, data->address, data->clue_sa, 
                data->asset_type, data->deltaz, data->distance, 
                data->grade1in, data->mcc_id, data->mccid_int, 
                data->rlmax, data->rlmin, data->segside, 
                data->statusid, data->streetid, 
                data->street_group, 
                data->start_lat, data->start_lon, data->end_lat, 
                data->end_lon
                );
}

void search_tree(quadtreenode_t *tree, point2D_t point, FILE* output) {
    // Traverse to a black node
    if(tree->status == 'g') {
        int quad = determine_quadrant(&point, &(tree->rect));
        if(quad == 0) {
            printf("SW ");
        }
        else if (quad == 1) {
            printf("NW ");
        }
        else if (quad == 2) {
            printf("NE ");
        }
        else {
            printf("SE ");
        }
        if(tree->child[quad] != NULL){
            search_tree(tree->child[quad], point, output);
        }
    }
    else{
        for(int i = 0; i < tree->datapoint.count; i++){
            print_tree_node(tree->datapoint.data[i], output);
        }
    }
}

list_t* find_within_rect(quadtreenode_t *tree, rectangle2D_t rect, FILE* output, list_t* streets) {
    if(does_overlap(tree->rect, rect) == 0){
        return streets;
    }
    if(tree->status == 'g') {
        for(int i = 0; i < CHILDREN; i++){
            rectangle2D_t quad_rect = determine_rect(&(tree->rect), i);

            if((tree->child[i] != NULL) && does_overlap(quad_rect, rect) == 1){
                if(i == 0) {
                    printf("SW ");
                }
                else if (i == 1) {
                    printf("NW ");
                }
                else if (i == 2) {
                    printf("NE ");
                }
                else {
                    printf("SE ");
                }
                streets = find_within_rect(tree->child[i], rect, output, streets);
            }
        }
    }
    else{
        for(int i = 0; i < tree->datapoint.count; i++){
            if(in_rect(tree->datapoint.data[i], rect) == 1) {
                streets = insert_at_foot(streets, *(tree->datapoint.data[i]));
            }
        }
    }
    return streets;
}

int does_overlap(rectangle2D_t tree, rectangle2D_t rect) {
    if(rect.bot_left.lon <= tree.top_right.lon) {
        if(rect.bot_left.lat <= tree.top_right.lat) {
            if(rect.top_right.lat >= tree.bot_left.lat) {
                if(rect.top_right.lon >= tree.bot_left.lon) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int in_rect(data_t *point, rectangle2D_t rect) {
    if(point->point.lat > rect.bot_left.lat && point->point.lon > rect.bot_left.lon){
        if(point->point.lat < rect.top_right.lat && point->point.lon < rect.top_right.lon){
            return 1;
        }
    }
    return 0;
}

void free_tree(quadtreenode_t *tree) {
    if(tree == NULL){
        return;
    }
    for(int i = 0; i < 4; i++){
        free_tree(tree->child[i]);
        tree->child[i] = NULL;
    }
    free(tree->child);
    free(tree->datapoint.data);
    free(tree);
}
