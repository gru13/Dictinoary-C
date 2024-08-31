#include "defs.h"

int search(WINDOW* win){

    FILE* fp = fopen(DATA,"r");
    if(fp == NULL){
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


    char Word[X];int index = 0;
    Word[0] = '\0';
    int choice = 0;
    switch(mvwlinput(win, Word, Query,1,x,y)){
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
    y += 5;
    char p;
    while(!feof(fp)){
        p = nextLetter(fp);
        mvwprintw(win,y,x,"%c",p);
        wrefresh(win);
        Sleep(100);
        if(p == tolower(Word[0])){
            break;
        }
    }
    char key[X];
    int nof_words;
    fscanf(fp,"-%d,",&nof_words);
    // mvwprintw(win, 21,20,"%d",nof_words);
    // wrefresh(win);
    if(nof_words == 0){
        mvwprintw(win,y,x,"No Words Found in %c, please add the Words to view",Word[0]);
        wrefresh(win);
        Sleep(1000);
        return 1;
    }
    int nofMeaning[nof_words];
    for(int i = 0;i<nof_words;i++){
        fscanf(fp,"%d,", &nofMeaning[i]);
    }
    fgetc(fp); // skipping the '\n'
    int indexOfWord = 0, wordFound = FALSE;
    for(;indexOfWord < nof_words; indexOfWord++){
        nextWord(fp,key);
        mvwprintw(win,y,x,"%s",key);
        wrefresh(win);
        Sleep(300);
        if(strcmp(Word,key) == 0){
            // // debug
            // mvwprintw(win,y+2,x+strlen(Word),"%d",nofMeaning[indexOfWord]);
            // wrefresh(win);
            // Sleep(5000);
            wordFound = TRUE;
            break;
        }else{
            mvwhline(win, y,x,' ',X-x-2);
            wrefresh(win);
            Sleep(300);
        }
    }
    if(wordFound == FALSE){
        mvwprintw(win,y,x,"'%s' Not Found in '%c' Letter, please add the Word to view",Word, Word[0]);
        wrefresh(win);
        Sleep(2000);
        return 1;
    }
    mvwprintw(win,y,x,"Meaning for '%s' :",key);
    int X_mean = x+strlen(Word)+18;
    int cursorY = 0;
    char Meaning[nofMeaning[indexOfWord]][X+X];
    for(int i = 0;i<nofMeaning[indexOfWord];i++){
        nextMeaning(fp,Meaning[i]);
    }
    int ofsetY = 0,ofsetX = 0;
    while(TRUE){
        for(int i =0 ;i<nofMeaning[indexOfWord] && i < Y-y-4;i++){
            if(cursorY == i && strlen(Meaning[i+ofsetY]) >= X-X_mean-5){
                mvwprintw(win,y+2+i,X_mean, "[%02d]",i+1+ofsetY);

                for(int j = 0;j<strlen(Meaning[i+ofsetY]) && j+X_mean+5 < X - 5;j++){
                    mvwprintw(win,y+2+i,X_mean+5+j,"%c",Meaning[i+ofsetY][j+ofsetX]);
                }

            }else
            if(strlen(Meaning[i+ofsetY]) >= X-X_mean-5){
                mvwprintw(win,y+2+i,X_mean, "[%02d]",i+1+ofsetY);

                for(int j = 0;j<strlen(Meaning[i+ofsetY]) && j+X_mean+5 < X - 5;j++){
                    mvwprintw(win,y+2+i,X_mean+5+j,"%c",Meaning[i+ofsetY][j]);
                }

            }else{
                mvwprintw(win,y+2+i,X_mean,"[%02d] %s",i+1+ofsetY,Meaning[i+ofsetY]);
            }

        }

        mvwprintw(win,y+2+cursorY,X_mean-3,"->");
        wrefresh(win);
        choice = wgetch(win);
        switch (choice){
            case enter:
                return 1;
            case ESC:
                return 0;
            case down:
                ofsetX = 0;
                mvwprintw(win,y+2+cursorY,X_mean-3,"  ");
                cursorY++;
                if(cursorY >= Y-y-4 || cursorY + ofsetY >= nofMeaning[indexOfWord]){
                    cursorY--;
                    ofsetY++;
                    if(ofsetY + cursorY >=  nofMeaning[indexOfWord]){
                        ofsetY--;
                    }
                }
                mvwprintw(win,y+2+cursorY,X_mean-3,"->");
                wrefresh(win);
                break;
            case up:
                ofsetX = 0;
                mvwprintw(win,y+2+cursorY,X_mean-3,"  ");
                cursorY--;
                if(cursorY <= -1){
                    cursorY++;
                    ofsetY--;
                    if(ofsetY <= 0){
                        ofsetY = 0;
                    }
                }
                mvwprintw(win,y+2+cursorY,X_mean-3,"->");
                wrefresh(win);
                break;
            case rigth:
                if(ofsetX + X - 10 - X_mean < strlen(Meaning[cursorY+ofsetY])){
                    ofsetX++;
                }
                break;
            case left:
                ofsetX = (ofsetX <= 0)?0:ofsetX-1;
                break;
            default:
                break;
        }
    }
    return 0;
}

