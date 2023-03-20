#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

void displayBoard(char board[40][40]){
    for(int i = -1; i < 41; i++){
        for(int j = -1; j < 41; j++){
            if (i == -1 || i == 40) {
                printf("-");
            }else if(j == -1 || j == 40){
                printf("|");
            }else{
                if(board[i][j] == 'X'){
                    printf("%c", board[i][j]);
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

char*  getInput(){
    char *input = malloc(8);
    size_t len = 0;
    printf("Enter your input: ");
    getline(&input, &len, stdin);
    return input; 
}

int* getNums(char* inpt){
    int *nums = malloc(8);
    sscanf(inpt, "%*c %d %d", &nums[0], &nums[1]);
    return nums;
    
}

void flipCell(char board[40][40], int i, int j){
    if(board[i][j] == 'X'){
        board[i][j] = '\0';
    }else{
        board[i][j] = 'X';
    }
}

void birth(char board[40][40], int i, int j){
    board[i][j] = 'X';
}

void death(char board[40][40], int i, int j){
    board[i][j] = '\0';
}

int checkNeighbors(char board[40][40], int i, int j){
    // 1 if it lives, 0 if it dies
    int count = 0;
    int debug = 0;
    if(i > 0 && i < 40 && j > 0 && j < 40){
        for(int l = -1; l <= 1; l++){
            for(int k = -1; k <= 1; k++){
                if (debug) printf("Checking %d (%d), %d (%d)...", i+l, l, j+k, k);
                if(board[i+l][j+k] == 'X' && !(l == 0 && k == 0)){
                    count++;
                    if (debug) printf("counted ");
                }
                if (debug) printf("\n");
            }
        }
    }
    if (debug) printf("Count: %d\n", count);

    if((count == 3 && board[i][j] == '\0') || (board[i][j] == 'X' && (count == 2 || count == 3))){
        return 1;
    }
    return 0;
}

void advance(char board[40][40]){
    char storageBoard[40][40] = {0};
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            if(checkNeighbors(board, i, j)){
                storageBoard[i][j] = 'X';
            }else{
                storageBoard[i][j] = '\0';
            }
        }
    }

    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            board[i][j] = storageBoard[i][j];
        }
    }
}

void runCommand(char board[40][40], char command[10]){
    int *nums;
    switch(command[0]){
        case 'a':
            nums = getNums(command);
            birth(board, nums[0], nums[1]);
            break;
        case 'r':
            nums = getNums(command);
            death(board, nums[0], nums[1]);
            break;
        case 'n':
            advance(board);
            break;
        case 'p':
            while(1){
                system("clear");
                advance(board);
                displayBoard(board);
                usleep(50000);
            }
            break;

    }
}
