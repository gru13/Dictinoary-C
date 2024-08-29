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
    int choice = 0;
    int locX = x + strlen(Query);
    curs_set(TRUE);
    wmove(win,y,locX);
    // getting word
    Entry_phase :
    do{
        choice = wgetch(win);
        if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            Word[index] = (char)choice;
            mvwaddch(win,y,locX+index,Word[index]);
            wrefresh(win);
            index++;
        }else if(choice == 8){
            index--;
            index = (index>=0)?index:0;
            wmove(win,y,locX+index-2);
            mvwaddch(win,y,locX+index,' ');
            wrefresh(win);
            Word[index] = '\0';
        }
    }while(choice != enter);
    Word[index] = '\0';
    curs_set(FALSE);
    rewind(fp);
    char p;
    int ySearch = y + 5;  
    while (!feof(fp)){
        p = nextLetter(fp);
        mvwprintw(win,ySearch,x,"%c",p);
        wrefresh(win);
        Sleep(400); 
        if(p == tolower(Word[0])){
            break;
        }
    }
    
    return 0;
}
