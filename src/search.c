#include "defs.h"

int search(WINDOW* win){
    /*
        return -1 -> cant open old file
        return  0 -> all done exiting the error
        return  1 -> all done and repeating 
    */
    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        perror("Cant open the file in Search");
        mvwprintw(win,Y-1,X/20,"Cant open the file in Search");
        wrefresh(win);
        CloseData(data);
        return -1;
    }
    initTemplate(win,SEARCH);
    int x = X/20;
    int y = Y/7;
    const char Query[X] = "Enter the Word to search : ";
    // mvwprintw(win,y,x,Query);
    mvwhline(win,y+2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
    // getting input from the user 
    switch(mvwlinput(win, data->Word, Query,1,x,y)){
        case 0:
            // sucessfully got input
            data->Letter = tolower(data->Word[0]);
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
            mvwprintw(win,Y/2,X/2 - 19 ,"Word Not Found, <Enter> to Continue");
            wrefresh(win);
            while(wgetch(win) != ENTER);
            return -1;
            break;
        case -2:
            // no Word found in letter
            mvwprintw(win,Y/2,X/2 - 25, "Word not Found in Letter '%c', <Enter> to Continue", data->Letter);
            wrefresh(win);
            while(wgetch(win) != ENTER);
            return -2;
            break;
        default:
            // no problem
            break;
    }
    mvwprintw(win,y,x,"Meaning for '%s' :",data->Word);
    x += strlen(data->Word)+18;
    y += 2;
    DisplayList(win,x,y,data->Meanings,data->nof_Meaning, 0);
    CloseData(data);
    return returnChoice(win);
}

int WordsInLetter(WINDOW* win){
    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        mvwprintw(win,Y/2,X/2-10,"Cant open the file in WordsInLetter");
        perror("Cant open the file in WordsInLetter");
        wrefresh(win);
        CloseData(data);
        return -1;
    }
    int x = X/20;
    int y = Y/7;
    initTemplate(win,"ALL WORDS in Letter");
    const char Query[X] = "Enter the Letter to search : ";
    // mvwprintw(win,y,x,Query);
    mvwhline(win,y+2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
    // getting input from the user 
    switch(mvwlinput(win, data->Word, Query,1,x,y)){
        case 0:
            // sucessfully got input
            data->Letter = tolower(data->Word[0]);
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
    int nofMeaning[X];
    switch(ToLetter(win,data,nofMeaning)){
        case -1:
            //Eof reached
            CloseData(data);
            return 1;
            break;
        case 0:
            // no error 
            break;
        default:
            break;
    }  
    if(data->nof_Words == 0){
        mvwprintw(win, Y/2, X/2 - 17, "No Words Found in the Letter '%c'", data->Letter);
        wrefresh(win);
        CloseData(data);
        return returnChoice(win);
    }
    char WORDS[X][X+X];
    for(int i= 0;i<data->nof_Words;i++){
        long loc = NextWord(data->fp, WORDS[i]);
        switch (loc){
            case -1:
                // return -> -1 reached eof
                break;
            case -2:
                // return -> -2 reached next letter
                break;
            default:
                // return -> >=0 no error 
                break;
        }
    }
    DisplayList(win,x,y,WORDS,data->nof_Words, 0);
    if(fclose(data->fp) != 0) {
        perror("Error closing Data file");
        CloseData(data);
        return -1;
    }
    CloseData(data);
    return returnChoice(win);
}

int AllWords(WINDOW* win){
    FILE* fp = fopen(DATA_FILE,"r");
    if(fp == NULL){
        perror("Cant open the file in Search");
        mvwprintw(win,Y-1,X/20,"Cant open the file in Search");
        wrefresh(win);
        return -1;
    }
    int x = X/20;
    int y = Y/7;
    initTemplate(win,"SEARCH ALL WORDS");
    char WORDS[X][X+X];
    char p, tmpC;
    int index = 0;
    do{
        p = fgetc(fp);
        if(p == (int)WORD_SYMBOL){
            fscanf(fp, "%s-", WORDS[index]);
            index++;
        }
    }while(p != EOF);

    mvwprintw(win, Y-2, X/20, "Number of Words is %d", index);
    wrefresh(win);      
    DisplayList(win, x, y, WORDS,index,0);
    fclose(fp);
    return returnChoice(win);   
}