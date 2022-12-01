#ifndef _TREE_H_
#define _TREE_H_

#define INPUT_STREAM 2
#define OUTPUT_STREAM 3
#define X_BOT_LEFT 4
#define Y_BOT_LEFT 5
#define X_TOP_RIGHT 6
#define Y_TOP_RIGHT 7
#define CHILDREN 4

typedef struct{
        point2D_t bot_left;
        point2D_t top_right;
        point2D_t centre;
} rectangle2D_t;

typedef struct{
        data_t **data;
        int count;
} datapoint_t;

typedef struct{
        data_t **data;
        int count;
} streets_t;

typedef struct quadnode quadtreenode_t;
struct quadnode {
        rectangle2D_t rect;
        datapoint_t datapoint;
        char status;
        quadtreenode_t **child;
};

// Creates the root node for the tree having input of the initial rectangle.
quadtreenode_t *make_root(rectangle2D_t root);

// Converts a linked list into a quadtree, having inputs the completed list and the root node for the tree.
quadtreenode_t *list_to_tree(list_t *list, quadtreenode_t *tree);

/* Inserts nodes into the tree recursively traveling down the tree, inputs being the parent node, the rectangle defined for the parent node, the quadrant of the new node, and the inserting data.
*/
quadtreenode_t *insert_in_tree(quadtreenode_t *tree, rectangle2D_t* prev_rect, int quadrant, data_t *data);

// Compares two points to determine if equal or not.
int cmp_points(point2D_t *tree, point2D_t *data);

// Determines the quadrant of a point given a rectangle.
int determine_quadrant(point2D_t *point, rectangle2D_t *rect);

// Determines the rectangle forming a given quadrant of the parent rectangle
rectangle2D_t determine_rect(rectangle2D_t *rect, int quad);

// Creates a quadtreenode to store to store the stree data into
quadtreenode_t *make_node(rectangle2D_t* prev_rect, int quadrant, data_t *data);

// Sorts an array of pointers based on footpath_id
void sort_arr(data_t **data, int count);

// Recursively travels down a tree sorting each array of pointers found in black nodes
quadtreenode_t *tree_arr_sort(quadtreenode_t *tree);

// Prints all the stored data in a node
void print_tree_node(data_t *data, FILE* output);

// Travels down the tree searching for the noded associated with a given point and printing the nodes data
void search_tree(quadtreenode_t *tree, point2D_t point, FILE* output);

// Finds all the unique streets in a tree provided a rectangle
list_t *find_within_rect(quadtreenode_t *tree, rectangle2D_t rect, FILE* output, list_t *streets);

// Determines if a node's associated rectangle is within the search rectangle
int does_overlap(rectangle2D_t tree, rectangle2D_t rect);

// Determines if a node's associated point is within the search rectangle
int in_rect(data_t *point, rectangle2D_t rect);

// Free's all the nodes of a quadtree
void free_tree(quadtreenode_t *tree);

#endif
