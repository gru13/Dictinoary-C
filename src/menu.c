#include <defs.h>



int maxlenoption(){
    int len = 0, m = 0;
    for(int i = 0;i<NOP;i++){
        len = strlen(options[i]);
        m = (m >= len)?m:len;
    }
    return m;
}

int menu(WINDOW* win){
    
    initTemplate(win,TITLE);

    int x = X/2 - maxlenoption()/2;
    int y = Y/2-NOP/2;
    
    for(int i = 0 ; i<NOP; i++){
        mvwprintw(win,y+i,x,"[%d] %s",i+1,options[i]);
    }
    
    int choice = '1', i = 0;

    mvwprintw(win,y,x-3,"->");
    wrefresh(win);
    do{
        choice = wgetch(win);
        // mvwprintw(win,20,20,"%c",choice); // uncomment for debugging

        switch(choice){
        case ERR:
            mvwprintw(win,20,20,"Error in getting input");
            continue;
        case down:
            if(i < NOP-1){
                mvwprintw(win,y+i,x-3,"  ");
                i++;
                mvwprintw(win,y+i,x-3,"->");
            }
            break;
        case up:
            if(i){
                mvwprintw(win,y+i,x-3,"  ");
                i--;
                mvwprintw(win,y+i,x-3,"->");
            }
            break;
        case ESC:
            choice = '\n';
            i = NOP-1;
            break;
        default:
            if(choice >= 49 && choice <= 48 + NOP){
                mvwprintw(win,y+i,x-3,"  ");
                i = choice - 49;
                mvwprintw(win,y+i,x-3,"->");
            }
            break;
        }
        wrefresh(win);
    }while(choice != '\n');
    box(win,0,0);
    wrefresh(win);
    return i;
}
