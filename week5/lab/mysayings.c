//Tommy Rozgonyi, mysayings.c
//03/02/2023
#include <stdio.h>
#include <string.h>

#define MAXLEN 256

int displayMenu(void);              // Function prototypes
void displaySayings(char [50][MAXLEN], int size);
void newSaying(FILE *fp, char [50][MAXLEN], int size);
void listGrep(FILE *fp, char [50][MAXLEN], int size);
void saveSayings(char [50][MAXLEN], int size);

int main(){
    FILE *fp;
    char fname[30];

    printf("Enter a startup file name: "); // Get the startup file name
    fgets(fname, 30, stdin);
    fname[strlen(fname) - 1] = '\0'; //Replace the newline with null char
    fp = fopen(fname, "r");  // open the file
    
    if(fp == NULL) { // exit program if the file is not found
        printf("File not found\n");
        return 0;
    }

    char sayings[50][MAXLEN] = {0}; // Initialize sayings to an empty array of strings
    char tempSaying[MAXLEN]; // storage for each string added to database
    int count = 0; // number of strings added
    while(1){ // Add strings until EOF
        fgets(tempSaying, MAXLEN-1, fp);
        if(feof(fp)) break;
        strcpy(sayings[count], tempSaying);
        count++;
    }
    
    int choice = displayMenu();
    while(choice != 5){ // Display the menu until 5 is chosen
        switch (choice) {
            case 1:
                displaySayings(sayings, count);
                break;
            case 2:
                newSaying(fp, sayings, count);
                count++; 
                break;
            case 3:
                listGrep(fp, sayings, count);
                break;
            case 4:
                saveSayings(sayings, count);
                break;
            default:
                break;
        }
        choice = displayMenu();
    }
    printf("Quitting...\n");

}

int displayMenu(void){
    int choice; // Get the users choice and return it
    printf("1. display all sayings currently in the database\n");
    printf("2. enter a new saying into the database\n");
    printf("3. list sayings that contain a given string entered by the user\n");
    printf("4. save all sayings in a new text file\n");
    printf("5. quit the program\n");
    scanf("%d", &choice);

    return choice;
}

void displaySayings(char sayings[50][MAXLEN], int size){
    int count = 0; // Go through all sayings and print them until theres no more
    while(count < size){
        printf("%s", sayings[count]);
        count++;
    }
}

void newSaying(FILE *fp, char sayings[50][MAXLEN], int size){
    char newPhrase[MAXLEN] = {0};
    int count = 0;
    printf("Enter a new saying: ");
    getchar();
    fgets(newPhrase, 255, stdin);
    strcpy(sayings[size], newPhrase); //Get a new phrase and add it to the database
}

void listGrep(FILE *fp, char sayings[50][MAXLEN], int size){
    char toFind[MAXLEN];
    printf("Enter the string you want to search for: "); // Get the string to search for
    getchar();
    fgets(toFind, MAXLEN-1, stdin);
    toFind[strlen(toFind) - 1] = '\0';
    for(int i = 0; i < size; i++){ //If any saying contains this string, print it
        if(strstr(sayings[i], toFind) != NULL){
            fputs(sayings[i], stdout);
        } 
    }
}

void saveSayings(char sayings[50][MAXLEN], int size){
    char fname[30];
    printf("Enter a file name to save to: ");
    getchar();
    fgets(fname, 30, stdin);
    fname[strlen(fname) - 1] = '\0'; // Get the file name
    
    FILE *fp = fopen(fname, "w"); // Open the file to write
    for(int i = 0; i < size; i++){
        fputs(sayings[i], fp);
    }//write each saying to file
    fclose(fp);
}
