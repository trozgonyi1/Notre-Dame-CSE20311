#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lifefunc.h"

int main(int argc, char *argv[]){
    char board[40][40] = {0}; // Create the board
    char tempBoard[40][40] = {0}; 

    if(argc == 1){ // If no args
        int flag = 1;
        char* input = malloc(8);
        input = getInput();
        int * nums;
        while(flag){
            switch (input[0]) {
                case 'a':
                    nums = getNums(input); // Get the location on the board
                    birth(board, nums[0], nums[1]); // give life to that location
                    displayBoard(board);
                    break;
                case 'r':
                    nums = getNums(input);
                    death(board, nums[0], nums[1]);
                    displayBoard(board);
                    break;
                case 'c':
                    nums = getNums(input);
                    printf("%d\n", checkNeighbors(board, nums[0], nums[1]));
                    break;
                case 'n':
                    advance(board);
                    displayBoard(board);
                    break;
                case 'p':
                    while(1){
                        system("clear");
                        advance(board);
                        displayBoard(board);
                        usleep(50000);
                    }
                    break;
                case 'q':
                    printf("Quitting...\n");
                    flag = 0;
                    break;
                default:
                    printf("Not\n");
                    flag = 0;
            }
            if(flag){
                input = getInput();
                nums = getNums(input);
            }
        }
    } else if (argc == 2){
        FILE *fp;
        char fname[30];
        
        fp = fopen(argv[1], "r");
        
        if(!fp) {
            printf("File not found.");
            return 0;
        }

        char tempCommand[10];
        while(1){
            fgets(tempCommand, 10, fp);
            if(feof(fp)) break;
            runCommand(board, tempCommand);
        }        
    } else {
        printf("Error. Wrong amount of command line arguments.\n");
    }
}
