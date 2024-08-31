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
#define ESC 27  
#define left 'K' // left
#define bsc 8
#define DATA "D:\\codings\\Dictinoary\\src\\data.txt"
#define NOP 6
#define Y 30
#define X 100
#define TITLE "DICTIONARY"
#define SEARCH "Searching Meaning for the Word"
extern char options[NOP][X];
extern FILE* fp;

/*
    Defined in menu.c
        this contains the menu controls 
*/
int maxlenoption();
int menu(WINDOW* win);


/*
    Defined in search.c
        this contains the search controls 
*/
int search(WINDOW* win);

/*
    Defined in create.c
        this contains the creating part
*/
int CreatePair(WINDOW* win);

/*
    Defined in Movement.c
        this file contains the movement in file and updation 
*/

char nextLetter(FILE* fp);
int nextWord(FILE* fp, char words[X]);
int nextMeaning(FILE* fp, char sent[X]);
int toLetter(WINDOW* win ,FILE* fp,char L, int* nofWord, int nofMeaning[X]);
int toWord(WINDOW* win,FILE* fp, char Word[X], int nofWord, int nofMeaning[nofWord], char Meaning[X][X+X]);


/*
    defined in helper.c
    helper function
*/

void initTemplate(WINDOW* win, const char* heading);
int get1LineInput(WINDOW* win, char output[X], const char Query[X], int x, int y);
int mvwlinput(WINDOW* win,char output[X+X], const char query[X],int nofRow, int x, int y);