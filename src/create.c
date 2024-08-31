#include "./defs.h"

int CreatePair(WINDOW* win){
    initTemplate(win, "Insert Word with Meaning");

    int x = X/20;
    int y = Y/2 - 5;
    char WordQuery[] = "Enter Word        : ";
    char MeaningQuery[] = "Enter the Meaning : ";
    mvwprintw(win,y,x,WordQuery);
    mvwprintw(win,y+2,x,MeaningQuery);
    wrefresh(win);
    int cursorX = x + strlen(WordQuery);
    int cursorY = y;
    int choice;
    curs_set(TRUE);
    wmove(win,cursorY,cursorX);
    wrefresh(win);

    char Word[X];
    int Wordindex = 0;
    Word[0] = '\0';
    // getting word
    do{
        choice = wgetch(win);
        if(Wordindex == 0 && choice == ' '){
            continue;
        }else if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            Word[Wordindex] = (char)choice;
            mvwaddch(win,y,cursorX+Wordindex,Word[Wordindex]);
            wrefresh(win);
            Wordindex++;
            Word[Wordindex] = '\0';
        }else if(choice == bsc){
            Wordindex--;
            Wordindex = (Wordindex>=0)?Wordindex:0;
            mvwaddch(win,y,cursorX+Wordindex,' ');
            wrefresh(win);
            Word[Wordindex] = '\0';
        }else if(choice == 10 &&(Wordindex == 0 || strlen(Word) == 0)){
            mvwprintw(win, cursorY + 12, x, "Enter Something in Word");
            wrefresh(win);
            Sleep(1000);
            curs_set(FALSE);
            return 1;
        }else if(choice == ESC){
            curs_set(FALSE);
            return 0;
        }
    }while(choice != enter);
    Word[Wordindex] = '\0';
    
    char Meaning[X+x];
    Meaning[0] ='\0';
    curs_set(TRUE);
    wmove(win,y+2,cursorX);
    wrefresh(win);
    int Meaningindex = 0;
    // getting Meaing
    do{
        if(Meaningindex == X+X-2){
            break;
        }
        choice = wgetch(win);
        if(Meaningindex == 0 && choice == ' '){
            continue;
        }else if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            Meaning[Meaningindex] = (char)choice;
            if(cursorX + Meaningindex < X - 5){
                mvwaddch(win,y+2,Meaningindex + cursorX,Meaning[Meaningindex]);
                wrefresh(win);
            }else{
                mvwaddch(win,y+3,Meaningindex - (X-6-cursorX) + cursorX,Meaning[Meaningindex]);
                wrefresh(win);
            }
            Meaningindex++;
            Meaning[Meaningindex] = '\0';
        }else if(choice == bsc){
            if(Meaningindex == 0){
                continue;
            }
            Meaningindex--;
            if(cursorX + Meaningindex < X - 5){
                mvwaddch(win,y+2,cursorX+Meaningindex,' ');
                wrefresh(win);
            }else{
                mvwaddch(win,y+3,Meaningindex - (X-6-cursorX) + cursorX,' ');
                wrefresh(win);
            }
            Meaning[Meaningindex] = '\0';
        }else if(choice == 10 &&(Meaningindex == 0 || strlen(Meaning) == 0)){
            mvwprintw(win, cursorY + 12, x, "Enter Something in Meaning");
            wrefresh(win);
            Sleep(1000);
            mvwprintw(win, cursorY + 12, x, "                          ");
            wrefresh(win);
        }else if(choice == ESC){
            curs_set(FALSE);
            return 0;
        }
    }while(choice != enter);
    Meaning[Meaningindex] = '\0';
    curs_set(FALSE);
    return 0;
}