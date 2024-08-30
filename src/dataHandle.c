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
        if(index == 0 && choice == ' '){
            continue;
        }else if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
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
        }else if(choice == 10 &&(index == 0 || strlen(Word) == 0)){
            mvwprintw(win, ySearch, x, "Before Pressing Enter, Enter words for searching");
            wrefresh(win);
            Sleep(1000);
            return 1;
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
        mvwprintw(win,ySearch,x,"No Words Found in %c, please add the Words to view",Word[0]);
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
        mvwprintw(win,ySearch,x,"%s",key);
        wrefresh(win);
        Sleep(300);
        if(strcmp(Word,key) == 0){
            // // debug  
            // mvwprintw(win,ySearch+2,x+strlen(Word),"%d",nofMeaning[indexOfWord]);
            // wrefresh(win);
            // Sleep(5000);
            wordFound = TRUE;
            break;
        }else{
            mvwhline(win, ySearch,x,' ',X-x-2);
            wrefresh(win);
            Sleep(300);
        }
    }
    if(wordFound == FALSE){
        mvwprintw(win,ySearch,x,"'%s' Not Found in '%c' Letter, please add the Word to view",Word, Word[0]);
        wrefresh(win);  
        Sleep(2000);
        return 1;
    }
    for(int i = 0;i<nofMeaning[indexOfWord];i++){
        char Meaning[X+X];
        nextMeaning(fp,Meaning);
        mvwprintw(win,ySearch+i+1,x+strlen(Word)+1,"[%d] %s",i+1,Meaning);
    }
    choice = wgetch(win);
    if(choice == enter){
        return 1;
    }else if(choice == ESC){
        return 0;
    }
    return 0;
}
