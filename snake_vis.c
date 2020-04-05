#include "snake_header.h"

void terminal_vis(struct segment *snake, struct segment *fruit){
    /* design convention:
     * '*' for the border
     * 'X' for snake's body
     * 'O' for snake's head
     * 'A' for apple
     * ' ' for empty space
     */ 
    char border, body, head, apple, space;
    border = '*';
    body = 'X';
    head = 'O';
    apple = 'A';
    space = ' ';
    
    // array to store the characters
    char garden[LEN][LEN];
    
    int i, j;   // index variables
    
    // initialise garden
    for(i=0; i<LEN; i++)
        for(j=0; j<LEN; j++)
            garden[i][j] = space;
        
    // place the apple
    i = fruit->x;
    j = fruit->y;
    garden[i][j] = apple;
    
    // place the snake's head
    i = snake->x;
    j = snake->y;
    garden[i][j] = head;
    
    // traverse the body and place them
    snake = snake->back_add;
    while(snake != NULL){
        i = snake->x;
        j = snake->y;
        garden[i][j] = body;
        snake = snake->back_add;
    }
    
    // now draw it on the terminal!
    
    // top border
    printf("\n");
    for(i=0; i<LEN+2; i++)
        printf("%c ", border);
    printf("\n");
    
    // draw each row of the array
    for(i=0; i<LEN; i++){
        printf("%c ", border);
        for(j=0; j<LEN; j++)
            printf("%c ", garden[j][i]);
        printf("%c", border);
        printf("\n");
    }
        
    // bottom border
    for(i=0; i<LEN+2; i++)
        printf("%c ", border);
    printf("\n\n");
    
    return;
}
