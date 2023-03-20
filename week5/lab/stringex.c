// stringex.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convert(char []);

int main()
{
  char line[80];

  printf("enter a line: ");
  fgets(line, 80, stdin);
  line[strlen(line)-1] = '\0';

  convert(line);

  printf("%s\n", line);

  return 0;
}

// the convert function
// ...
void convert(char ch[]){
    for(int i = 0; i < strlen(ch); i++){
        if(isblank(ch[i])) {
            ch[i] = '_';
        }
        if(isupper(ch[i])){
            ch[i] = tolower(ch[i]);
        }
    }
}
/*void convert(char ch[]){
    int pch;
    printf("%d", strchr(ch, ' ')-ch+1);
    while(!strchr(ch, ' ')){
        pch = strchr(ch, ' ')-ch+1;
        ch[pch] = ' ';
    }
}*/
