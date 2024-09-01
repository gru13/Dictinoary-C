#include "./defs.h"

int CreatePair(WINDOW* win){
    int x = X/20;
    int y = Y/5;
    initTemplate(win, "Insert Word with Meaning");

    const char WordQuery[] = "Enter Word        : ";
    const char MeaningQuery[] = "Enter the Meaning : ";
    char Word[X],Meaning[X+x];

    switch(mvwlinput(win, Word, WordQuery,1,x,y)){
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
    y += 2;
    switch(mvwlinput(win, Meaning,MeaningQuery,2,x,y)){
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

int AddMeaning(WINDOW* win){

    int x = X/20;
    int y = Y/5;
    initTemplate(win, "Add Another Meaning to Word");

    const char WordQuery[] = "Enter Word        : ";
    const char MeaningQuery[] = "Enter the Meaning : ";
    char Word[X],Meaning[X+x];

    switch(mvwlinput(win, Word, WordQuery,1,x,y)){
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
    // checking if Word exist
    FILE* fp = fopen(DATA_FILE,"r");
    if(fp == NULL){
        mvwprintw(win,Y/2,X/2-10,"Cant open the file");
        wrefresh(win);
    }
    y += 2;
    switch(mvwlinput(win, Meaning,MeaningQuery,2,x,y)){
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