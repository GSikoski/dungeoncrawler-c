#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct player {
    int health;
    char name[20];
}player;


// A function that prints a line out character by character.
// It will finish the line by adding a newline character
void scrollPrint(char text[], int rate) {
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++){
        printf("%c", text[i]);
        fflush(stdout);
        usleep(rate * 1000);
    }
    printf("%c", '\n');
}

void saveGame(player c){
    FILE* fptr;
    char filepath[30] = "./saves/"; 
    strcat(filepath, c.name);
    strcat(filepath, ".txt");
    
    fptr = fopen(filepath, "w");
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(fptr, "%s", c.name);
    fprintf(fptr, "%c", '\n');
    fprintf(fptr,"%i", c.health);

    fclose(fptr);
}