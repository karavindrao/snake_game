#include "snake_header.h"

void print_snake(struct segment *head){
    //printf("Snake is at...\n");
    while(1){        
        if(head->back_add == NULL){
            printf("(%d,%d)\n", head->x, head->y);
            break;
        }        
        printf("(%d,%d)->", head->x, head->y);
        head = head->back_add;
    }
        
    return;
}

void trim(struct segment  *head, int len){
    int i=1;    // current length of the snake; included the head
    
    while(1){
        if(head->back_add == NULL || i == len){
            head->back_add = NULL;
            break;
        }
        else{
            i++;
            head = head->back_add;
        }
    }
    
    return;
}

struct segment* move_snake(struct segment *head, struct segment *fruit, char dir){    
    struct segment *dummy, *head_new;
    head_new = (struct segment*)malloc(sizeof(struct segment*));
    /* dummy is a dummy pointer
     * head_new is the value we return upon successful movement */
    
    int x_curr, y_curr, x_new, y_new;
    x_curr = head->x;
    y_curr = head->y;
    
    // finding the new position of the head
    x_new = x_curr;
    y_new = y_curr;
    
    if(dir == 'r'){  // head moves up
        y_new--;
        pbc_correct(&y_new);
    }
    else if(dir == 'f'){    // head moves left
        x_new--;
        pbc_correct(&x_new);
    }
    else if(dir == 'j'){    // head moves right
        x_new++;
        pbc_correct(&x_new);
    }
    else if(dir == 'n'){    // head moves down
        y_new++;
        pbc_correct(&y_new);
    }
        
    // snake cannot "go back" relative to its orientation; abort the function!
    if(head->back_add != NULL && x_new == head->back_add->x && y_new == head->back_add->y)
        return head;
    
    // did the snake eat the apple?
    if(fruit->x == x_new && fruit->y == y_new){        
        head_new->x = x_new;
        head_new->y = y_new;
        head_new->back_add = head;
        return head_new;
    }
    
    // normal movement    
    head_new->x = x_new;
    head_new->y = y_new;
    
    // if snake has length 1
    if(head->back_add == NULL)
        head_new->back_add = NULL;
    else{   // remove the bottom element of the stack if length > 1
        dummy = head;
        while(1){
            if(dummy->back_add->back_add == NULL){
                dummy->back_add = NULL;
                break;
            }
            else
                dummy = dummy->back_add;
        }
        // attach the new head to the front
        head_new->back_add = head;
    }
    

    return head_new;
}

void pbc_correct(int *a){
    // correcting a
    if(*a <  0)
        *a = (*a+LEN)%LEN;
    else if(*a >= LEN)
        *a = *a%LEN;
        
    return;
}   

char rand_dir(){
    int i;
    char dir_list[4] = {'r', 'f', 'j', 'n'};
    i = rand()%4;
    return dir_list[i];
}

void apple_update(struct segment *head, struct segment *fruit){
    int x_new, y_new;
    struct segment *dummy;
    while(1){
        x_new = rand()%LEN;
        y_new = rand()%LEN;
        dummy = head;
        while(dummy != NULL){
            if(dummy->x == x_new && dummy->y == y_new)
                break;
            else
                dummy = dummy->back_add;
        }
        if(dummy == NULL)
            break;
    }
    fruit->x = x_new;
    fruit->y = y_new;
    fruit->back_add = NULL;
        
    return;
}

void flush_input(){
    while(getchar() != '\n');
    return;
}

int snake_bite(struct segment *head){
    int x_head, y_head, ans;
    
    // if snake is just the head, it can't bite itself
    if(head->back_add == NULL)
        return 0;
    
    // else...:
    x_head = head->x;
    y_head = head->y;
    head = head->back_add;
    while(1){
        if(head == NULL){
            ans = 0;
            break;
        }
        else if(head->x == x_head && head->y == y_head){
            ans = 1;
            break;
        }
        else
            head = head->back_add;
    }
    return ans;
}

struct path* greedy_path(struct segment *head, struct segment *fruit){
    int hor_disp, ver_disp;
    
    // declare the queue
    struct path *greedy_queue;
    greedy_queue=NULL;
    
    // define hor_disp and ver_disp
    hor_disp = (fruit->x)-(head->x);
    ver_disp = (fruit->y)-(head->y);
    
    // moving horizontally first
    while(hor_disp < 0){    // should move left
        greedy_queue = queue_path(greedy_queue, 'f');
        hor_disp++;
    }
    while(hor_disp > 0){    // should movie right
        greedy_queue = queue_path(greedy_queue, 'j');
        hor_disp--;
    }        
    
    // moving vertically
    while(ver_disp < 0){    // should move up
        greedy_queue = queue_path(greedy_queue, 'r');
        ver_disp++;
    }
    while(ver_disp > 0){    // should move down
        greedy_queue = queue_path(greedy_queue, 'n');
        ver_disp--;
    }
    
    return greedy_queue;
}

struct path* queue_path(struct path* queue, char c){
    struct path *new_step, *dummy=NULL;
    
    // defining new_step
    new_step = (struct path*)malloc(sizeof(struct path));
    new_step->move = c;
    new_step->nxt = NULL;
    
    // if queue is empty:
    if(queue == NULL){
        queue = new_step;
        return queue;
    }
    
    // else... add new_step to the end of the queue
    dummy = queue;
    while(dummy->nxt != NULL)
        dummy = dummy->nxt;
    
    // now we reached the end; attach new_step
    dummy->nxt = new_step;
    
    return queue;
}
