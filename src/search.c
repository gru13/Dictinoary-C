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
    switch (ToWord(win,data)){
        case -1:
            // letter not found
            return -1;
            break;
        case -2:
            // no Word found in letter
            return -2;
            break;
        default:
            // np problem
            break;
    }
    mvwprintw(win,y,x,"Meaning for '%s' :",data->Word);
    x += strlen(data->Word)+18;
    
    int cursorY = 0;
    int ofsetY = 0,ofsetX = 0;
    
    while(TRUE){
        for(int i =0 ;i<data->nof_Meaning && i < Y-y-4;i++){
            if(cursorY == i && strlen(data->Meanings[i+ofsetY]) >= X-x-5){
                mvwprintw(win,y+2+i,x, "[%02d]",i+1+ofsetY);

                for(int j = 0;j<strlen(data->Meanings[i+ofsetY]) && j+x+5 < X - 5;j++){
                    mvwprintw(win,y+2+i,x+5+j,"%c",data->Meanings[i+ofsetY][j+ofsetX]);
                }

            }else if(strlen(data->Meanings[i+ofsetY]) >= X-x-5){
                mvwprintw(win,y+2+i,x, "[%02d]",i+1+ofsetY);
                for(int j = 0;j<strlen(data->Meanings[i+ofsetY]) && j+x+5 < X - 5;j++){
                    mvwprintw(win,y+2+i,x+5+j,"%c",data->Meanings[i+ofsetY][j]);
                }

            }else{
                mvwprintw(win,y+2+i,x,"[%02d] %s",i+1+ofsetY,data->Meanings[i+ofsetY]);
            }

        }

        mvwprintw(win,y+2+cursorY,x-3,"->");
        wrefresh(win);
        int choice = wgetch(win);
        switch (choice){
            case enter:
                return 1;
            case ESC:
                return 0;
            case down:
                ofsetX = 0;
                mvwprintw(win,y+2+cursorY,x-3,"  ");
                cursorY++;
                if(cursorY >= Y-y-4 || cursorY + ofsetY >= data->nof_Meaning){
                    cursorY--;
                    ofsetY++;
                    if(ofsetY + cursorY >=  data->nof_Meaning){
                        ofsetY--;
                    }
                }
                mvwprintw(win,y+2+cursorY,x-3,"->");
                wrefresh(win);
                break;
            case up:
                ofsetX = 0;
                mvwprintw(win,y+2+cursorY,x-3,"  ");
                cursorY--;
                if(cursorY <= -1){
                    cursorY++;
                    ofsetY--;
                    if(ofsetY <= 0){
                        ofsetY = 0;
                    }
                }
                mvwprintw(win,y+2+cursorY,x-3,"->");
                wrefresh(win);
                break;
            case rigth:
                if(ofsetX + X - 10 - x < strlen(data->Meanings[cursorY+ofsetY])){
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