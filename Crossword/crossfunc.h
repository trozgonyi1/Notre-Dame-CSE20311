#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define _GNU_SOURCE

typedef struct {
    char *word;
    int row;
    int column;
    int direction;
} Key ;

typedef struct {
    char board[15][15];
    int score;
} FinalBoard ;

void bubble_sort(char *[20], int);
void to_upper(char *[20], int);
void display(FILE *, char [15][15]);
void displayBoard(FILE *, FinalBoard);
void dispSolution(FILE *, FinalBoard);
int checkAdjacency(FILE *, int, Key *[20], char [15][15], Key *[20], int, int, int);
int placeSkipped(FILE *, int, Key *[20], char [15][15], Key *[20], int, int);
void placeWord(char [15][15], Key *);
bool checkConflicts(char [15][15], Key *);
bool evalBoardEqual(Key *[20], Key *[20], int); 
FinalBoard generateBoard(FILE *, char *[20], int, Key *[20], int);
FinalBoard makeNBoards(char *[20], int);
bool checkFits(Key *);
void printClues(FILE *, Key *[20], int);
char *mix_letters(char *);
