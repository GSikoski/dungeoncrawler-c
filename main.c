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
    printf("You wake up in a damp cave\n");
    printf("A dim light is glowing in the distance\n");
    printf("You can't make out your surroundings so you walk towards the light\n");
    printf("A terrible stench attacks your senses as you walk towards entrance\n");
    printf("It is almost unbearable\n");
    printf("As you approach the light you notice a bruises on your arms\n");
    return 0;
}


int main() {
    player c = initialiseCharacter();
    printf("Hello %s\n", c.name);
    return startGame();
}

