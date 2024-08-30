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
    const char Query[X] = "Enter the Word to search :";
    mvwprintw(win,y,x,Query);
    mvwhline(win,y+2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
    
    char Word[X];int index = 0;
    Word[0] = '\0';
    int choice = 0;
    int locX = x + strlen(Query);
    int ySearch = y + 5;  
    curs_set(TRUE);
    wmove(win,y,locX);
    // getting word
    do{
        choice = wgetch(win);
        if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            Word[index] = (char)choice;
            mvwaddch(win,y,locX+index,Word[index]);
            wrefresh(win);
            index++;
            Word[index] = '\0';
        }else if(choice == 8){
            index--;
            index = (index>=0)?index:0;
            wmove(win,y,locX+index-2);
            mvwaddch(win,y,locX+index,' ');
            wrefresh(win);
            Word[index] = '\0';
        }else if(choice == 10 && strlen(Word) == 0){
            mvwprintw(win, ySearch, x, "Enter Word to search");
            Sleep(1000);
            search(win);
        }else if(choice == ESC){
            curs_set(FALSE);
            return 0;
        }
    }while(choice != enter);
    Word[index] = '\0';
    curs_set(FALSE);
    rewind(fp);
    char p;
    while(!feof(fp)){
        p = nextLetter(fp);
        mvwprintw(win,ySearch,x,"%c",p);
        wrefresh(win);
        Sleep(300); 
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
        mvwprintw(win,ySearch,x,"No Words Found , please add the Words to view");
        wrefresh(win);  
        Sleep(1000);
        search(win);
    }
    int nofMeaning[nof_words];
    for(int i = 0;i<nof_words;i++){
        fscanf(fp,"%d,", &nofMeaning[i]);
    } 
    fgetc(fp); // skipping the '\n'
    for(int i = 0 ;i < nof_words; i++){
        nextWord(fp,key);
        mvwprintw(win,ySearch,x,"%s",key);
        wrefresh(win);
        Sleep(300);
        mvwhline(win, ySearch,x,_SPACE,X-x-2);
        wrefresh(win);
        Sleep(300);
    }
    return 0;
}
