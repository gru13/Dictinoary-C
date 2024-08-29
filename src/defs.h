#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>

#ifdef __linux__
    #include<unistd.h>
    #define CLEAR_SCRN "clear"
#elif defined(_WIN32)
    #define CLEAR_SCRN "cls"
    #include <windows.h>
#endif

#define enter 10
#define down 'P' // down
#define up 'H' // up
#define rigth 'M' // rigth
#define left 'K' // left

#define DATA "D:\\codings\\Dictinoary\\src\\data.txt"
#define NOP 6
#define Y 30
#define X 100
#define TITLE "DICTIONARY"
#define SEARCH "Searching Meaning for the Word"
extern char options[NOP][X];


/*
    Defined in menu.c
        this contains the menu controls 
*/
int maxlenoption();
int menu(WINDOW* win);
void initTemplate(WINDOW* win, const char* heading);


/*
    Defined in dataHandle.c
        this contains the menu controls 
*/
int search(WINDOW* win);


/*
    Defined in Movement.c
        this file contains the movement in file and updation 
*/

char nextLetter(FILE* fp);
int nextWord(FILE* fp);
int nextMeaning(FILE* fp);