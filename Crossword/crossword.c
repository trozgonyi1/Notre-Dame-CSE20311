#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "crossfunc.h"

int main(int argc, char *argv[]){
    char *words[20];
    int numWords = 0;
    char board[15][15] = {0};
    Key *skipped[20];// = malloc(20 * sizeof(*skipped));
    int numSkipped = 0;
    FILE *dest = stdout;

    if (argc >= 2){
        FILE *fp;
        char fname[30];

        fp = fopen(argv[1], "r");

        if(!fp){
            printf("File not found");
            return 0;
        }
        
        char tempWord[30];
        bool flag = true;
        while(1){
            fgets(tempWord, 30, fp);
            if(tempWord[0] == '.') break;
            if(feof(fp)) break;
            if(strlen(tempWord) > 15){ 
                continue;
            }

            for(int i = 0; i < strlen(tempWord)-1; i++){
                if(!isalpha(tempWord[i])) {
                    flag = false;
                }
            }
            if(!flag) continue;
            words[numWords] = malloc(strlen(tempWord));
            tempWord[strlen(tempWord)-1] = '\0';
            strcpy(words[numWords], tempWord);
            numWords++;
        }
        if(argc == 3){
            dest = fopen(argv[2], "w");
        }
    }

    else if(argc == 1){
        printf("Enter a list of words:\n");
        char tempWord[30];
        while(1){
            fgets(tempWord, 30, stdin); 
            if(tempWord[0] == '.') break;
            if(strlen(tempWord) > 15) {
                printf("Word too long, skipping...\n");
                continue;
            }
            
            bool flag = true;
            for(int i = 0; i < strlen(tempWord)-1; i++){
                if(!isalpha(tempWord[i])) {
                    flag = false;
                    printf("Invalid word, skipping...\n");
                }
            }
            if(!flag) continue;
            words[numWords] = malloc(strlen(tempWord));
            tempWord[strlen(tempWord)-1] = '\0';
            strcpy(words[numWords], tempWord);
            numWords++;
        }
    }else{
        printf("Wrong amount of arguments\n");
        return 0;
    }
    to_upper(words, numWords);
    bubble_sort(words, numWords);

    /*for(int i = 0; i < numWords; i++){
        key[i] = (Key *)malloc(sizeof(char)*15+sizeof(int)*3);
        key[i]->word = words[i];
    }
    key[0]->column = 7-(int)strlen(words[0])/2;
    key[0]->row = 7;
    key[0]->direction = 0;
    placeWord(board, key[0]);
    
    for(int i = 1; i < numWords; i++){
        checkAdjacency(i, key, board);
        if(key[i]->direction != -1){
            placeWord(board, key[i]);
        }
    }*/
    fprintf(dest, "Anagram Crossword puzzle generator\n");
    fprintf(dest, "----------------------------------\n");
    FinalBoard fBoard = generateBoard(dest, words, numWords, skipped, numSkipped);
}
