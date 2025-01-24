#include <stdio.h>
#include <stdlib.h>

#include "gamelib.h"

player initialiseCharacter() {
    
    player* c_ptr = malloc(sizeof(player));

    scrollPrint("Hello player, welcome to the dungeon!\n", 60);
    scrollPrint("What is your name?\n", 60);
    scanf("%s", c_ptr->name);
    printf("%c", '\n');
    c_ptr->health = 100;

    player c = *c_ptr;
    free(c_ptr);

    return c;
}

int startGame() {
    scrollPrint("You wake up in a damp cave\n", 60);
    scrollPrint("A dim light is glowing in the distance\n", 60);
    scrollPrint("You can't make out your surroundings so you walk towards the light\n", 60);
    scrollPrint("A terrible stench attacks your senses as you walk towards entrance\n", 60);
    scrollPrint("It is almost unbearable\n", 60);
    scrollPrint("As you approach the light you notice bruises on your arms\n", 60);
    return 0;
}


int main() {
    player c = initialiseCharacter();
    char welomeStr[40] = "Hello "
    strcat(welomeStr, c.name);
    strcat(welomeStr, "\n");
    scrollPrint(welomeStr, 60);
    return startGame();
}

