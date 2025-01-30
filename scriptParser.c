#include <unistd.h>
#include <ctype.h>
#include "gamelib.h"

// Check if a file exists
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

// Load a game from a .txt file in the saves dir
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
    c_ptr->name[strcspn(c_ptr->name, "\n")] = '\0';
    char hstring[10];
    fgets(hstring, 10, fptr);
    c_ptr->health = atoi(hstring);
    fgets(c_ptr->checkpoint, 6, fptr);

    player c = *c_ptr;
    free(c_ptr);

    fclose(fptr);

    return c;
}

// Check if a string is an integer
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

// Check if a string starts with $CHK
int isCheckpoint(const char *str) {
    return strncmp(str, "$CHK ", strlen("$CHK ")) == 0;
}

// Check if a string starts with $CHOICE
int isChoice(const char *str) {
    return strncmp(str, "$CHOICE ", strlen("$CHOICE ")) == 0;
}

// Choice input type containing the choice message and the 
// filename for the text content following that branch
typedef struct choicein {
    char message[40];
    char location[5];
}choicein;

/// @brief Parse a player choice given  and the number of choices
/// @param c the player character details
/// @param choices an array of choiceins, representing the option and the branch locations
/// @param noChoices size of the choices array
/// @return the updated player character (TODO: Im scared of pointers)
player parseChoice(player c, choicein choices[], int noChoices){
    for (int i = 0; i < noChoices; i++){
        char choicestr[200];
        sprintf(choicestr, "%d) ", i+1);
        strcat(choicestr, choices[i].message);
        scrollPrint(choicestr, 60);
    }
    
    int choice = -1;
    while(choice == -1){
        gscanfi(&choice);
        if (choice <= 0 || choice > noChoices) {
            scrollPrint("Invalid input, please enter a valid number", 20);
            while (getchar() != '\n'); // flush the input buffer
            choice = -1;
        }
    }

    strcpy(c.checkpoint, choices[choice-1].location);
    saveGame(c);
    return c;
}

/// @brief Parse the currently selected script in a players checkpoint parameter
/// @param c the player character details
/// @return a parsout containing the updated player character and an error code
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
            parsout pout = {c, 0};
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