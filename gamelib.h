#ifndef UTILS_H
#define UTILS_H

#define Green  "\x1B[32m"
#define White "\x1B[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct player {
    int health;
    char name[20];
    char checkpoint[6];
}player;

typedef struct parsout {
    player c;
    int error;
}parsout;

// Linked functions script parser -> main
void scrollPrint(char text[], int rate);
player loadGame(char filepath[]);
parsout parseScript(player c);
void saveGame(player c);
int exists(const char *fname);

#endif