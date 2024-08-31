#include "./defs.h"

int CreateTemplate(WINDOW* win,char Word[X],char Meaning[X+X]){

}

int CreatePair(WINDOW* win){
    initTemplate(win, "Insert Word with Meaning");

    int x = X/20;
    int y = Y/2 - 5;
    const char WordQuery[] = "Enter Word        : ";
    const char MeaningQuery[] = "Enter the Meaning : ";
    char Word[X],Meaning[X+x];

    switch(get1LineInput(win, Word, WordQuery,x,y)){
        case 0:
            // sucessfully got input
            break;
        case 1:
            // no input so repeat from first
            return 1;
            break;
        case -1:
            // esc is pressed
            return 0;
            break; 
    }
    y++;y++;
    char ;
    switch(get2LineInput(win, Meaning,MeaningQuery,x,y)){
        case 0:
            // sucessfully got input
            break;
        case 1:
            // no input so repeat from first
            return 1;
            break;
        case -1:
            // esc is pressed
            return 0;
            break; 
    }

    return 0;
}   