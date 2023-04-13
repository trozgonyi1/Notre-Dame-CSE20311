#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "crossfunc.h"

#define _GNU_SOURCE
void bubble_sort(char *strings[20], int n){
    int i,j;
    char temp[15];
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            if(strlen(strings[i]) < strlen(strings[j])){
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }
    }
}

void to_upper(char *words[20], int length){
    int k = 0;
    for(int i = 0; i < length; i++){
        k = 0;
        while(words[i][k]){
            words[i][k] = toupper(words[i][k]);
            k++;
        }
    }
}

void placeWord(char board[15][15], Key *wordKey){
    int wordLen = strlen(wordKey->word);
    if(wordKey->direction == 0){
        for(int i = 0; i < wordLen; i++){
            board[wordKey->row][wordKey->column+i] = wordKey->word[i];
        }
    }else if(wordKey->direction == 1){
        for(int i = 0; i < wordLen; i++){
            board[wordKey->row+i][wordKey->column] = wordKey->word[i];
        }
    }
}

void display(FILE *dest, char board[15][15]){
    int width = 17;
    int height = 17;
    bool trigger = false;
    int k = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(i == 0 || i == height-1){
                fprintf(dest, "-");
            }else if(j == 0 || j == width-1){
                fprintf(dest, "|");
            }else{
                if(!isalpha(board[i-1][j-1])){
                    fprintf(dest, ".");
                }else{
                    fprintf(dest, "%c", board[i-1][j-1]);
                }
            }
        }
        fprintf(dest, "\n");
    }
}

int placeSkipped(FILE *dest, int totalWords, Key *keys[20], char board[15][15], Key *skipped[20], int numSkipped, int skippedCounter){
    bool flag1 = false;
    bool flag2 = false;
    
        for(int k = 0; k < totalWords; k++){
            if(flag1) break;
            if(keys[k]->word == skipped[skippedCounter]->word) continue;
            for(int i = 0; i < strlen(keys[k]->word); i++){
                if(flag2) break;
                for(int j = 0; j < strlen(skipped[skippedCounter]->word); j++){
                if(keys[k]->word[i] == skipped[skippedCounter]->word[j]){
                    if(keys[k]->direction == 0){
                        if(keys[k]->row-j < 0 || keys[k]->column + strlen(skipped[skippedCounter]->word)-j > 15){
                            continue;
                        }
                        skipped[skippedCounter]->column = keys[k]->column+i;
                        skipped[skippedCounter]->row = keys[k]->row-j;
                        skipped[skippedCounter]->direction = 1;
                    }
                    else if(keys[k]->direction == 1){
                        if(keys[k]->column-j < 0 || keys[k]->column + strlen(skipped[skippedCounter]->word)-j > 15){
                            continue;
                        }
                        skipped[skippedCounter]->column = keys[k]->column-j;
                        skipped[skippedCounter]->row = keys[k]->row+i;
                        skipped[skippedCounter]->direction = 0;
                    }
                    
                    if(checkConflicts(board, skipped[skippedCounter]) || !checkFits(skipped[skippedCounter])){
                        skipped[skippedCounter]->column = -1;
                        skipped[skippedCounter]->row = -1;
                        skipped[skippedCounter]->direction = -1;
                        continue;
                    }
                    flag1 = true;
                    flag2 = true;
                    break;
                }
                }
            }
        }

        for(int k = 0; k < totalWords; k++){
            if(keys[k]->word == skipped[skippedCounter]->word) return k;
        }
        fprintf(dest, "Failed\n");
        return -1;
}

int checkAdjacency(FILE *dest, int numWord, Key *keys[20], char board[15][15], Key *skipped[20], int numSkipped, int skippedCounter, int totalWords){
    for(int k = 0; k < numWord; k++){
        for(int i = 0; i < strlen(keys[k]->word); i++){
            for(int j = 0; j < strlen(keys[numWord]->word); j++){
                if(keys[k]->word[i] == keys[numWord]->word[j]){
                    if(keys[k]->direction == 0){
                        if(keys[k]->row-j < 0 || keys[k]->column + strlen(keys[numWord]->word)-j > 15){
                            continue;
                        }
                        keys[numWord]->column = keys[k]->column+i;
                        keys[numWord]->row = keys[k]->row-j;
                        keys[numWord]->direction = 1;
                    }else if(keys[k]->direction == 1){
                        if(keys[k]->column-j < 0 || keys[k]->column + strlen(keys[numWord]->word)-j > 15){
                            continue;
                        }
                        keys[numWord]->column = keys[k]->column-j;
                        keys[numWord]->row = keys[k]->row+i;
                        keys[numWord]->direction = 0;
                    }else{
                        continue;
                    }
                
                    if(checkConflicts(board, keys[numWord]) || !checkFits(keys[numWord])){
                        keys[numWord]->column = -1;
                        keys[numWord]->row = -1;
                        keys[numWord]->direction = -1;
                        continue;
                    }
                    return 0;
                }
            }
        }
    }

    fprintf(dest, "Skipping ");
    skipped[skippedCounter] = keys[numWord];
    fprintf(dest, "%s\n", skipped[skippedCounter]->word);
    keys[numWord]->row = -1;
    keys[numWord]->column = -1;
    keys[numWord]->direction = -1;
    
    return 1;
}

bool checkConflicts(char board[15][15], Key *key){
    int wordLen = strlen(key->word);
    int count = 0;
    int offset = 0;

    if (key->direction == 0 && key->column+wordLen < 15){
        if(isalpha(board[key->row][key->column+wordLen])){
            count++;
        }
    }else if(key->direction == 1 && key->row+wordLen < 15){
        if(isalpha(board[key->row+wordLen][key->column])){
            count++;
        }
    }

    if(key->direction == 0 && key->column != 0){
        if(isalpha(board[key->row][key->column-1])){
            count++;
        }
    }else if(key->direction == 1 && key->row != 0){
        if(isalpha(board[key->row-1][key->column])){
            count++;
        }
    }

    for(int i = 0; i < wordLen; i++){
        if(key->direction == 0){
            if(isalpha(board[key->row][key->column+i])){
                count++;
            }else if(isalpha(board[key->row-1][key->column+i])){
                count++;
            }else if (isalpha(board[key->row+1][key->column+i])){ 
                count++;
            }
        }else if(key->direction == 1){
            if(isalpha(board[key->row+i][key->column])){
                count++;
            }else if(isalpha(board[key->row+i][key->column-1])){
                count++;
            }else if (isalpha(board[key->row+i][key->column+1])){ 
                count++;
            }
        }
    }
    if (count > 1) return true;
    return false;
}

void dispSolution(FILE *dest, FinalBoard board){
    int width = 17;
    int height = 17;
    bool trigger = false;
    int k = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(i == 0 || i == height-1){
                fprintf(dest, "-");
            }else if(j == 0 || j == width-1){
                fprintf(dest, "|");
            }else{
                if(!isalpha(board.board[i-1][j-1])){
                    fprintf(dest, "#");
                }else{
                    fprintf(dest, " ");
                }
            }
        }
        fprintf(dest, "\n");
    }
}

bool evalBoardEqual(Key *board1Keys[20], Key *board2Keys[20], int words){
   for(int i = 0; i < words; i++){
       if(board1Keys[i]->word != board2Keys[i]->word || board1Keys[i]->column != board2Keys[i]->row || board1Keys[i]->direction != board2Keys[i]->direction) return false;
   }
   return true;
}

FinalBoard generateBoard(FILE *dest, char *words[20], int numWords, Key *skipped[20], int numSkipped){
    Key *keys[20];
    char board[15][15];
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            board[i][j] = '\0';
        }
    }
    
    for(int i = 0; i < numWords; i++){
        keys[i] = (Key *)malloc(sizeof(Key));
        keys[i]->word = words[i];
    }

    keys[0]->column = 7-(int)strlen(words[0])/2;
    keys[0]->row = 7;
    keys[0]->direction = 0;
    placeWord(board, keys[0]);

    int totSkipped = 0;
    int skippedCounter = 0;
    for(int j = 0; j < totSkipped; j++){
        skipped[j] = malloc(sizeof(Key));
    }

    for(int i = 1; i < numWords; i++){
        if(1 == checkAdjacency(dest, i, keys, board, skipped, totSkipped, skippedCounter, numWords)){
            totSkipped++;
            skippedCounter++;
        }
        
        if(keys[i]->direction != -1){
            placeWord(board, keys[i]);
        }
    }

    int index = 0;
    for(int i = 0; i < totSkipped; i++){
        index = placeSkipped(dest, numWords, keys, board, skipped, totSkipped, i);
        if(keys[i]->direction != -1){
            placeWord(board, keys[index]);
        }
    }

    int score = numWords;
    for(int i = 0; i < numWords; i++){
        if(keys[i]->direction == -1){
            score--;
        }
    }

    FinalBoard boardOut;
    memcpy(boardOut.board, board, sizeof(char)*15*15);
    boardOut.score = score;

    fprintf(dest, "Solution:\n");
    displayBoard(dest, boardOut);

    fprintf(dest, "Crossword puzzle:\n");
    dispSolution(dest, boardOut);
    
    printClues(dest, keys, numWords);
    return boardOut;
}

void displayBoard(FILE *dest, FinalBoard board){
    display(dest, board.board);
}

bool checkFits(Key *word){
    int wordLen = strlen(word->word);
    if(word->direction == 0){
        return word->row+wordLen <= 15;
    }else{ 
        return word->column+wordLen <= 15;
    }
}

char *mix_letters(char *str) {
    int len = strlen(str);
    char *mixed = malloc(len + 1);
    mixed = str;
    srand(time(NULL)); 
    for (int i = 0; i < len; i++) {
        int j = rand() % len; 
        char temp = str[i];
        mixed[i] = mixed[j];
        mixed[j] = temp;
    }
    mixed[len] = '\0'; 
    return mixed;
}

void printClues(FILE *dest, Key *keys[20], int numWords){
    char *direction;
    char *scrambled;
    fprintf(dest, "Clues:\n");
    for(int i = 0; i < numWords; i++){
        scrambled = malloc(sizeof(keys[i]->word)+1);
        scrambled = mix_letters(keys[i]->word);
        if(keys[i]->direction == 0){
            direction = malloc(7);
            direction = "Across";
        }else if(keys[i]->direction == 1){
            direction = malloc(5);
            direction = "Down";
        }else{
            continue;
        }
        fprintf(dest, "%2d, %2d, %-6s %s\n", keys[i]->row+1, keys[i]->column+1, direction, scrambled);
    }
}
