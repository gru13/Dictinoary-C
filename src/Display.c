#include "./defs.h"

void initTemplate(WINDOW* win, const char* heading){
    wclear(win);
    box(win,0,0);
    mvwprintw(win,1,X/2-strlen(heading)/2, heading);
    mvwhline(win,2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
}

int mvwlinput(WINDOW* win,char output[X+X], const char query[X],int nofRow, int x, int y){
    /*
        return -1 -> esc is pressed
        return  0 -> sucessfully got the input
        return  1 -> no input typed so recalling the function
    */
    int index = 0, choice = 0;
    output[0] = '\0';
    curs_set(TRUE);
    mvwprintw(win,y,x,query);
    x += strlen(query);
    wrefresh(win);
    wmove(win,y,x);
    // getting Meaing
    int row = 0;
    do{
        if(row >= nofRow){
            break;
        }
        choice = wgetch(win);
        if(choice == -1){
            continue;
        }
        if(index == 0 && choice == ' '){
            continue;
        }else if((choice >= 'a' && choice <= 'z' ) || choice == ' ' || choice == '-'){
            output[index] = (char)choice;
            mvwaddch(win,y+row,index - (X-6-x)*row + x,output[index]);
            wrefresh(win);
            index++;
            row = (index)/(X-x-6);
            output[index] = '\0';
        }else if(choice == bsc){
            if(index == 0){
                continue;
            }
            index--;
            row = (index)/(X-x-6);
            mvwaddch(win,y+row,index - (X-6-x)*row + x,' ');
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
            return -1;
        }
    }while(choice != enter);
    output[index] = '\0';
    curs_set(FALSE);
    return 0;
}
