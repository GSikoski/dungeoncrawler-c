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

// Dumps the player details into a text file in the saves folder
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


player loadGame(char filepath[]){
    FILE* fptr;
    fptr = fopen(filepath, "r");
    
    if (fptr == NULL) {
        player error = {-1, "Error"};
        perror("Error opening file");
        return error;
    }

    player* c_ptr = malloc(sizeof(player));

    fgets(c_ptr->name, 20, fptr);
    char hstring[3];
    fgets(hstring, 3, fptr);
    c_ptr->health = atoi(hstring);

    player c = *c_ptr;
    free(c_ptr);

    fclose(fptr);

    return c;
}

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}