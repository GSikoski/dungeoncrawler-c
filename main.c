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
    
    player c = *c_ptr;

    free(c_ptr);

    saveGame(c);

    char welomeStr[40] = "Hello ";
    strcat(welomeStr, c.name);
    strcat(welomeStr, "\n");
    scrollPrint(welomeStr, 60);

    return c;
}

int runGame() {
    scrollPrint("You wake up in a damp cave...\n", 60);
    scrollPrint("A dim light is glowing in the distance", 60);
    scrollPrint("You can't make out your surroundings so you walk towards the light", 60);
    scrollPrint("A terrible stench attacks your senses as you walk towards entrance", 60);
    scrollPrint("It is almost unbearable\n", 60);
    scrollPrint("As you approach the light you notice bruises on your arms\n", 60);
    scrollPrint("It has been a painful trip, but you remain determined to keep moving forward\n", 60);
    scrollPrint("As you near the dimly lit room you take a moment to survey the surroundings before stepping out of the shadows\n\n", 80);
    scrollPrint("The room is empty,", 80);
    scrollPrint("But an unmistakable odour makes it cler you are still not safe", 60);
    scrollPrint("You take a moment to see what is left of the equipment you came with", 60);
    scrollPrint("\n", 300);
    scrollPrint("All thats left is a small ornate knife that you had tucked in your pants", 60);
    scrollPrint("It looks like the wretches took everything else that you had", 60);
    scrollPrint("You sigh a breath of relief", 60);
    scrollPrint("\n", 300);
    scrollPrint("The knife brings back memories not too long ago", 60);
    
    return 0;
}


int main() {
    player c = initialiseCharacter();
    return runGame();
}

