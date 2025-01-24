#include <stdio.h>
#include <stdlib.h>

#include "gamelib.h"

#define Green  "\x1B[32m"
#define White "\x1B[0m"

player initialiseCharacter() {
    
    char playerName[20];

    scrollPrint("Hello player, welcome to the dungeon!\n", 60);
    scrollPrint("What is your name?\n", 60);
    printf(Green);
    scanf("%s", playerName);
    printf(White);
    printf("%c", '\n');
    
    char filepath[30] = "./saves/"; 
    strcat(filepath, playerName);
    strcat(filepath, ".txt");

    
    if (exists(filepath)) {
        
        char welomeStr[40] = "Welcome back ";
        strcat(welomeStr, playerName);
        strcat(welomeStr, "\n");
        
        scrollPrint(welomeStr, 60);
        return loadGame(filepath);
    }
    
    player* c_ptr = malloc(sizeof(player));
    strcpy(c_ptr->name, playerName);
    c_ptr->health = 100;
    strcpy(c_ptr->checkpoint, "BEGIN");
    
    player c = *c_ptr;

    free(c_ptr);

    saveGame(c);

    char welomeStr[40] = "Hello ";
    strcat(welomeStr, c.name);
    strcat(welomeStr, "\n");
    scrollPrint(welomeStr, 60);

    return c;
}

int runGame(player c) {
    parseScript(c);
    return 0;
}


int main() {
    player c = initialiseCharacter();
    return runGame(c);
}

