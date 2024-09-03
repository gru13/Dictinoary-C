#include "defs.h"

int search(WINDOW* win){

    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        mvwprintw(win,20,20,"Cant open the file");
        wrefresh(win);
    }
    initTemplate(win,SEARCH);
    int x = X/20;
    int y = Y/7;
    const char Query[X] = "Enter the Word to search : ";
    mvwprintw(win,y,x,Query);
    mvwhline(win,y+2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
    // getting input from the user 
    switch(mvwlinput(win, data->Word, Query,1,x,y)){
        case 0:
            // sucessfully got input
            data->Letter = data->Word[0];
            break;
        case 1:
            // no input so repeat from first
            return 1;
            break;
        case -1:
            // esc is pressed
            return 0;
        case -2:
            // no words in letter
            return -1;
            break;
    }
    
    y += 5;

    // moving to word in file
    int wordIndex = ToWord(win,data);
    switch (wordIndex){
        case -1:
            // letter not found
            return -1;
            break;
        case -2:
            // no Word found in letter
            return -2;
            break;
        default:
            // no problem
            break;
    }
    mvwprintw(win,y,x,"Meaning for '%s' :",data->Word);
    x += strlen(data->Word)+18;
    y += 2;
    DisplayList(win,x,y,data->Meanings,data->nof_Meaning);
    return returnChoice(win);
}