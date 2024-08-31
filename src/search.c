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
    int nof_words,nofMeaning[X];
    switch(toLetter(win,fp,Word[0],&nof_words,nofMeaning)){
        case 0:
            // run sucessfully and move to letter 
            break;
        case 1:
            // letter not found
            mvwprintw(win,y,x,"Letter '%c' not found", Word[0]);
            wrefresh(win);
            Sleep(1000);
            return 1;
            break;
        case 2:
            // no Word found
            mvwprintw(win,y,x,"No Words Found in %c, please add the Words to view",Word[0]);
            wrefresh(win);
            Sleep(1000);
            return 1;

    }
    char Meaning[X][X+X];
    int indexOfWord = toWord(win,fp,Word,nof_words,nofMeaning,Meaning);
    switch (indexOfWord){
        case -1:
            // Word not found
            mvwprintw(win,y,x,"'%s' Not Found in '%c' Letter, please add the Word to view",Word, Word[0]);
            wrefresh(win);
            Sleep(1000);
            return 1;
            break;
        default:
            // Word found , index found
            break;
    }
    mvwprintw(win,y,x,"Meaning for '%s' :",Word);
    int X_mean = x+strlen(Word)+18;
    int cursorY = 0;
    int ofsetY = 0,ofsetX = 0;
    while(TRUE){
        for(int i =0 ;i<nofMeaning[indexOfWord] && i < Y-y-4;i++){
            if(cursorY == i && strlen(Meaning[i+ofsetY]) >= X-X_mean-5){
                mvwprintw(win,y+2+i,X_mean, "[%02d]",i+1+ofsetY);

                for(int j = 0;j<strlen(Meaning[i+ofsetY]) && j+X_mean+5 < X - 5;j++){
                    mvwprintw(win,y+2+i,X_mean+5+j,"%c",Meaning[i+ofsetY][j+ofsetX]);
                }

            }else if(strlen(Meaning[i+ofsetY]) >= X-X_mean-5){
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

