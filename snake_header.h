#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define LEN 10

struct segment{
    int x;
    int y;
    struct segment *back_add;
};

struct path{
    char move;
    struct path *nxt;
};

// print the snake
void print_snake(struct segment *head);

// trim the snake to a particular length
void trim(struct segment  *head, int len);

// move the snake and check if it ate the apple
struct segment* move_snake(struct segment *head, struct segment *fruit, char dir);

// periodic boundary correction for the neighbouring site
void pbc_correct(int *a);

// get a random direction to move, if the snake is stuck
char rand_dir();

// create a new apple
void apple_update(struct segment *head, struct segment *fruit);

// flush the standard input after scanf
void flush_input();

// check for snake biting itself
int snake_bite(struct segment *head);

// get an automatic path from snake_head to apple
struct path* greedy_path(struct segment *head, struct segment *fruit);

// add the next step to the automatic path by queueing
struct path* queue_path(struct path* queue, char c);

// visualise the snake  in the garden
void terminal_vis(struct segment *snake, struct segment *fruit);
