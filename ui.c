#include "gamelib.h"

void gprintf(char format[], char message[]){
    printf(Green);
    printf(format, message);
    printf(White);
}

void gscanfs(char store[]){
    printf(Green);
    scanf("%s", store);
    printf(White);
}

void gscanfi(int* store){
    printf(Green);
    scanf("%i", store);
    printf(White);
}

void rprintf(char format[], char message[]){
    printf(Red);
    printf(format, message);
    printf(White);
}
void bprintf(char format[], char message[]){
    printf(Blue);
    printf(format, message);
    printf(White);
}

void yprintf(char format[], char message[]){
    printf(Yellow);
    printf(format, message);
    printf(White);
}