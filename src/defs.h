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
#define DATA_FILE "D:\\codings\\Dictinoary\\src\\data.txt"
#define NOP 6
#define Y 30
#define X 100
#define WAIT 500
#define TITLE "DICTIONARY"
#define SEARCH "Searching Meaning for the Word"
extern char options[NOP][X];

typedef struct data{
    FILE* fp;
    char Letter;
    long LetterPos;
    int nof_Words;
    char Word[X];
    long WordLoc;
    int  nof_Meaning;
    char Meanings[X][X+X];
    long MeaningLoc[X];
}Data;
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
int AddMeaning(WINDOW* win);
/*
    Defined in Movement.c
        this file contains the movement in file and updation 
*/

int ToWord(WINDOW* win, Data* data);
int ToLetter(WINDOW* win ,Data* data,int nofMeaning[X]);
long NextLetter(FILE* fp, char*p);
long NextWord(FILE* fp, char words[X]);
long NextMeaning(FILE* fp, char sent[X+X]);

/*
    defined in helper.c
    helper function
*/

void initTemplate(WINDOW* win, const char* heading);
int get1LineInput(WINDOW* win, char output[X], const char Query[X], int x, int y);
int mvwlinput(WINDOW* win,char output[X+X], const char query[X],int nofRow, int x, int y);
int CopyInRange(FILE* to, FILE* from ,long start, long until);



