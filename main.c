#include <stdio.h>
#include <stdlib.h>

#include "gameStructs.h"

player initialiseCharacter() {
    
    player* c_ptr = malloc(sizeof(player));

    printf("Hello player, welcome to the dungeon!\n");
    printf("What is your name?\n");
    scanf("%s", c_ptr->name);
    c_ptr->health = 100;

    player c = *c_ptr;
    free(c_ptr);

    return c;
}

int startGame() {
    return 0;
}


int main() {
    player c = initialiseCharacter();
    printf("Hello %s\n", c.name);
    return startGame();
}

