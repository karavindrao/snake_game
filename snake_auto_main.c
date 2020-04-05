#include "snake_header.h"

int main(){
    srand(time(NULL));
    char inst;  // direction of the next step
    int bite=0;   // boolean variable for snake bite
    int score=0;
    
    // declare the automatic path
    struct path *auto_path;
    //auto_path = (struct path*)malloc(sizeof(struct path));
    
    // define the snake's head and apple
    struct segment *snake_head, *apple, *dummy=NULL;
    snake_head = (struct segment *)malloc(sizeof(struct segment));
    apple = (struct segment *)malloc(sizeof(struct segment));
    
    snake_head->x = rand()%LEN;
    snake_head->y = rand()%LEN;
    snake_head->back_add = NULL;
    
    apple_update(snake_head, apple);    // randomly place the apple and not on the snake
    
    // begin the game
    printf("Welcome to Snake!\nComputer plays itself!. Press any alphabet key to start\n");
    scanf("%c", &inst);
    flush_input();

    // print the apple's position
    printf("Apple is at (%d, %d)\n", apple->x, apple->y);
    terminal_vis(snake_head, apple);
    
    while(1){
         
        // print the snake
        //print_snake(snake_head);
        
        // get the automatic greedy path
        auto_path = greedy_path(snake_head, apple);
        
        // execute the path pointed by auto_path
        while(auto_path != NULL && bite==0){
            // read the node
            inst = auto_path->move;                        
            
            // if the snake is stuck, move the head randomly
            if(dummy == snake_head)
                inst = rand_dir();
            
            // move according to inst (either random or from the path)
            dummy = snake_head; // will compare the two below:
            snake_head = move_snake(snake_head, apple, inst);
            
            // did the snake bite itself? (head lies on the body?)
            bite = snake_bite(snake_head);
            
            // print the snake
            print_snake(snake_head);
            
            // go to the next step in auto_path if dummy != snake_head
            if(snake_head != dummy){
                // if the previous move was made in a random direction, make a new greedy path
                if(auto_path->move == inst)
                    auto_path = greedy_path(snake_head, apple);
                // the default case: continue with the current greedy path.
                else
                    auto_path = auto_path->nxt;
            }
        }
        
        // exit game if bite == 1
        if(bite == 1){
            printf("Snake ate itself. Game over!\nFinal score = %d\n", score);
            break;
        }
        
        // else... the path is fully traversed, and the snake ate the apple
        score++;
        printf("Snake ate the apple\nScore = %d\n", score);
        // continue with a new apple
        apple_update(snake_head, apple);
        // print the apple's position
        printf("Apple is at (%d, %d)\n", apple->x, apple->y);
        
        // visualise the position of the snake
        printf("Press v to visualise the snake in the garden, c to continue, and x to exit.\n");
        scanf("%c", &inst);
        flush_input();                        
        // visualise?
        if(inst == 'v')
            terminal_vis(snake_head, apple);
        // exit now?
        else if(inst == 'x')
            break;
        
        
        while(inst != 'c'){
            printf("Press c to continue.\n");
            scanf("%c", &inst);
            flush_input();
        }                
    }  
    
    return 0;
}
