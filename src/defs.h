#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>


#ifdef __linux__
    #include<unistd.h>
    #define CLEAR_SCRN "clear"
    #define Sleep(t) usleep((t)*(1000))
#elif defined(_WIN32)
    #define CLEAR_SCRN "cls"
    #include <windows.h>
    #include <io.h>
#endif

#define ENTER  10
#define ESC 27  
#define BACKSPACE 8
#define DATA_FILE "./data.txt"
#define TMP_FILE "./tmp.txt"
#define Y 30
#define X 100
#define WAIT 300
#define TITLE "DICTIONARY"
#define SEARCH "Searching Meaning for the Word"

extern int DEBUG; 

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
    Defined in main.c
        this is the Entry point
*/
int main();
int maxlenArray(char arr[X][X+X],int arrLen);


/*
    Defined in search.c
        this contains the search controls 
*/
int search(WINDOW* win);
int WordsInLetter(WINDOW* win);

/*
    Defined in create.c
        this contains the creating part
*/
int CreatePair(WINDOW* win);
int AddMeaning(WINDOW* win);
/*
    Defined in FileHandling.c
        this file contains the movement in file and updating 
*/

int ToWord(WINDOW* win, Data* data);
int ToLetter(WINDOW* win ,Data* data,int nofMeaning[X]);
long NextLetter(FILE* fp, char*p);
long NextWord(FILE* fp, char words[X]);
long NextMeaning(FILE* fp, char sent[X+X]);
int CopyInRange(FILE* to, FILE* from ,long start, long until);
int closeFiles(WINDOW* win, Data* data, FILE* out, const char successText[X]);
int ResetFile(WINDOW* win, int flag);
int checkFileExist(const char* file_name);
int CloseData(Data* data);

/*
    defined in Display.c
    Display and window
*/

void initTemplate(WINDOW* win, const char* heading);
int get1LineInput(WINDOW* win, char output[X], const char Query[X], int x, int y);
int mvwlinput(WINDOW* win,char output[X+X], const char query[X],int nofRow, int x, int y);
int returnChoice(WINDOW* win);
int DisplayList(WINDOW* win,int x, int y,char List[X][X+X], int listLen, int initLoc);
int blankScreen(WINDOW* win, int x, int y, int h, int w);
/*
    defined in Remove.c
*/
int removeWord(WINDOW* win);
int removeMeaning(WINDOW* win);
