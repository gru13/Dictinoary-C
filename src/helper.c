#include "./defs.h"

void initTemplate(WINDOW* win, const char* heading){
    wclear(win);
    box(win,0,0);
    mvwprintw(win,1,X/2-strlen(heading)/2, heading);
    mvwhline(win,2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
}

int get1LineInput(WINDOW* win, char output[X], const char Query[X], int x, int y){
    int index = 0;
    output[0] = '\0';
    int choice = 0;
    mvwprintw(win,y,x,Query);
    x += strlen(Query);
    wrefresh(win);
    curs_set(TRUE);
    wmove(win,y,x);
    do{
        choice = wgetch(win);
        if(index == 0 && choice == ' '){
            continue;
        }else if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            output[index] = (char)choice;
            mvwaddch(win,y,x+index,output[index]);
            wrefresh(win);
            index = (index < X)?index+1:index;
            output[index] = '\0';
        }else if(choice == bsc){
            index = (index>=0)?index-1:0;
            mvwaddch(win,y,x+index,' ');
            wrefresh(win);
            output[index] = '\0';
        }else if(choice == 10 &&(index == 0 || strlen(output) == 0)){
            curs_set(FALSE);
            mvwprintw(win, Y-2, x, "Type something to press Enter");
            wrefresh(win);
            Sleep(1000);
            mvwprintw(win, Y-2, x, "                             ");
            wrefresh(win);
            return 1; 
        }else if(choice == ESC){
            curs_set(FALSE);
            output[0] = '\0';
            return -1;
        }
    }while(choice != enter);

    curs_set(FALSE);
    output[index] = '\0';
    return 0;
}

int get2LineInput(WINDOW* win,char output[X+X], const char query[X], int x, int y){
    int index = 0, choice = 0;
    output[0] = '\0';
    curs_set(TRUE);
    mvwprintw(win,y,x,query);
    x += strlen(query);
    wrefresh(win);
    wmove(win,y,x);
    // getting Meaing
    do{
        if(index == X+X/2){
            break;
        }
        choice = wgetch(win);
        if(index == 0 && choice == ' '){
            continue;
        }else if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            output[index] = (char)choice;
            if(x + index < X - 5){
                mvwaddch(win,y,index + x,output[index]);
                wrefresh(win);
            }else{
                mvwaddch(win,y+1,index - (X-6-x) + x,output[index]);
                wrefresh(win);
            }
            index++;
            output[index] = '\0';
        }else if(choice == bsc){
            if(index == 0){
                continue;
            }
            index--;
            if(x + index < X - 5){
                mvwaddch(win,y,x+index,' ');
                wrefresh(win);
            }else{
                mvwaddch(win,y+1,index - (X-6-x) + x,' ');
                wrefresh(win);
            }
            output[index] = '\0';
        }else if(choice == 10 &&(index == 0 || strlen(output) == 0)){
            curs_set(FALSE);
            mvwprintw(win, Y-2, x, "Type something to press Enter");
            wrefresh(win);
            Sleep(1000);
            mvwprintw(win, Y-2, x, "                             ");
            wrefresh(win);
            return 1; 
        }else if(choice == ESC){
            curs_set(FALSE);
            return -1;
        }
    }while(choice != enter);
    output[index] = '\0';
    curs_set(FALSE);
   
}