#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct player {
    int health;
    char name[20];
    char checkpoint[6];
}player;


// A function that prints a line out character by character.
// It will finish the line by adding a newline character
void scrollPrint(char text[], int rate) {
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++){
        if (text[i] == '\\' && text[i+1] == 'n') {
            printf("%c", '\n');
            i++;
            continue;
        }
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
    fprintf(fptr, "%c", '\n');
    fprintf(fptr, "%s", c.checkpoint);
    

    fclose(fptr);
}


player loadGame(char filepath[]){
    FILE* fptr;
    fptr = fopen(filepath, "r");
    
    if (fptr == NULL) {
        player error = {-1, "Error", ""};
        perror("Error opening file");
        return error;
    }

    player* c_ptr = malloc(sizeof(player));

    fgets(c_ptr->name, 20, fptr);
    char hstring[10];
    fgets(hstring, 10, fptr);
    c_ptr->health = atoi(hstring);
    fgets(c_ptr->checkpoint, 6, fptr);

    player c = *c_ptr;
    free(c_ptr);

    fclose(fptr);

    return c;
}

int isInteger(const char *str) {
    if (str == NULL || *str == '\0' || isspace(*str)) {
        return 0; 
    }
    char *endptr;
    strtol(str, &endptr, 10);

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;  
    }
    return *endptr == '\0';  
}

int isCheckpoint(const char *str) {
    return strncmp(str, "$CHK ", strlen("$CHK ")) == 0;
}

int isChoice(const char *str) {
    return strncmp(str, "$CHOICE ", strlen("$CHOICE ")) == 0;
}

typedef struct parsout {
    player c;
    int error;
}parsout;



typedef struct choicein {
    char message[40];
    char location[5];
}choicein;


player parseChoice(player c, choicein choices[], int noChoices){
    for (int i = 0; i < noChoices; i++){
        printf("%s", choices[i].message);
        printf("%s", "\n");
        printf("%s", choices[i].location);
        printf("%s", "\n");
    }
    return c;
}


parsout parseScript(player c) {
    
    char filepath[30] = "./scripts/"; 
    strcat(filepath, c.checkpoint);
    strcat(filepath, ".txt");
    
    FILE* fptr;
    fptr = fopen(filepath, "r");
    
    if (fptr == NULL) {
        perror("Error opening file");
        parsout pout = {c, 1};
        return pout;
    }

    char line[200];
    int scrollSpeed = 100;

    while (fgets(line, sizeof(line), fptr) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        
        if (isInteger(line)){
            scrollSpeed = atol(line);
        }
        else if (isCheckpoint(line))
        {
            char* name = line + 5;
            strcpy(c.checkpoint, name);
            saveGame(c);
            parsout pout = {c, 0};
            fclose(fptr);
            return pout;
        }
        else if (isChoice(line))
        {
            int noChoices = line[8] - '0';
            choicein choices[noChoices];
            
            int j = 0;

            for (int i = 0; i < noChoices; i++){
                
                choicein choice;

                fgets(line, sizeof(line), fptr);
                line[strcspn(line, "\n")] = '\0';

                strcpy(choice.message, line);

                fgets(line, sizeof(line), fptr);
                line[strcspn(line, "\n")] = '\0';
                char* name = line + 6;
                strcpy(choice.location, name);
                choices[j] = choice;
                j++;
            }
            
            c = parseChoice(c, choices, noChoices);
            fclose(fptr);
            parsout pout = {c, 1};
            return pout;
        }
        else {
            scrollPrint(line, scrollSpeed);
        }
        
    }
    parsout pout = {c, 2};
    fclose(fptr);
    return pout;

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