#include "snake_header.h"

int main(){
    srand(time(NULL));
    char inst;  // instruction character from stdin
    int bite;   // boolean variable for snake bite
    int score=0;
    
    // define the snake's head and apple
    struct segment *snake_head, *apple;
    snake_head = (struct segment *)malloc(sizeof(struct segment));
    apple = (struct segment *)malloc(sizeof(struct segment));
    
    snake_head->x = rand()%LEN;
    snake_head->y = rand()%LEN;
    snake_head->back_add = NULL;
    
    apple_update(snake_head, apple);    // randomly place the apple and not on the snake
    
    // begin the game
    printf("Welcome to Snake!\n");    
    // print the apple's position
    printf("Apple is at (%d, %d)\n", apple->x, apple->y);
    // print the snake
    print_snake(snake_head);
    
    // take instructions
    printf("Instructions - Enter:\nf for left\nr for up\nj for right\nn for down\nx to abort\n");
    printf("Your move: ");
    scanf("%c", &inst);
    flush_input();
    
    
    while(inst == 'f' || inst == 'r' || inst == 'j' || inst == 'n' || inst == 'x'){
        // abort if inst is x
        if(inst == 'x')
            break;
        
        // move the snake and get the new head position
        snake_head = move_snake(snake_head, apple, inst);                
        
        // if snake at the apple, make a new apple
        if(snake_head->x == apple->x && snake_head->y == apple->y){
            printf("Snake ate the apple\n");
            apple_update(snake_head, apple);
            printf("Apple is at (%d, %d)\n", apple->x, apple->y);
        }
        
        // if snake bit itself (head lies on the body), game over
        bite = snake_bite(snake_head);
        if(bite == 1){
            printf("Snake ate itself. Game over!\n");
            printf("Your score = %d\n", score);
            break;
        }
        
        score++;
        // print snake and get inst
        print_snake(snake_head);        
        printf("Your move: ");
        scanf("%c", &inst);
        flush_input();             
    }                
    
    return 0;
}
