// Tommy Rozgonyi
// letterfreq.c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NLETTERS (26)

void letterCounts(double []);
void charCounts(double [], int totLetters);

int main(){
    char fname[30];// File name
    double nums[NLETTERS] = {0}; // Create array of zeros that will hold the frequency of each letter
    char letter;
    FILE *fp; //File pointer
    int totChars = 0;//Total characters
    int totLetters = 0;//Total letters

    printf("Enter the text file name:\n"); // Get the file name
    fgets(fname, 30, stdin);
    fname[strlen(fname)-1] = '\0';
    
    fp = fopen(fname, "r"); //Open the file to read
    
    while(1){
        fscanf(fp, "%c", &letter); // Get each letter 
        if(feof(fp)) break;
        totChars++; //Increment total characters
        if (!isalpha(letter)) continue;
        nums[tolower(letter) - 'a']++; //Add 1 for the letter that occured
        totLetters++;
    }

    printf("General summary for %s\n", fname);
    printf("there were %d total characters\n", totChars);
    printf("there were %d total letters\n", totLetters);

    printf("\n");
    letterCounts(nums);
    printf("\n");
    charCounts(nums, totLetters);

}

void letterCounts(double nums[]){
    printf("Letters counts:\n");

    int line = 0;
    printf("   ");
    for(char i = 'a'; i <= 'z'; i++){ //loop from a to z
        printf("%c: %6.0lf    ", i, nums[i - 'a']); //get the value in the i spot in the nums array
        line++; //Formatting
        if (line == 6) {
            printf("\n");
            printf("   ");
            line = 0;
        }
    }
}

void charCounts(double nums[], int totLetters){
    
    int line = 0;
    printf("Letter percentages:\n   ");
    for(char i = 'a'; i <= 'z'; i++){//Loop a to z
        printf("%c: %4.1lf%%  ", i, nums[i - 'a']/totLetters * 100);//print percentages
        line++; //Formatting
        if (line == 6){
            printf("\n");
            printf("   ");
            line = 0;
        }
    }
}
