#include "defs.h"

char options[NOF_OPTS][X+X] = {"Search for Word",
                    "Create a Word and Meaning",
                    "Add Meaning to Word",
                    "Remove Word and Meaning",
                    "Remove a Meaning",
                    "list Words in a letter",
                    "Exit"};



int main(){
    int State = TRUE;
    initscr();
    keypad(stdscr,TRUE);
    cbreak();
    noecho();
    curs_set(FALSE);
    WINDOW* win = newwin(Y,X,0,0);
    int Exit = 1;
    int x = X/2 - maxlenoption()/2 - 10;
    int y = Y/2-NOF_OPTS/2;
    while(Exit){
        // int choice = menu(win);
        initTemplate(win,TITLE);
        int choice = DisplayList(win,x,y,options,NOF_OPTS);
        switch (choice){
            case ESC:
                Exit = 0;
                break;
            case 0:
                while(search(win)){}
                break;
            case 1:
                while(CreatePair(win)){}
                break;
            case 2:
                while(AddMeaning(win)){}
                break;
            case 3:
                while(removeWord(win)){}
                break;
            case 4:
                break;
            case 5:
                while(0){}
                break;
            case 6:
                Exit = 0;
                break;
            default:
                break;
        }  
    }
    endwin();
    return 0;
}



int maxlenoption(){
    int len = 0, m = 0;
    for(int i = 0;i<NOF_OPTS;i++){
        len = strlen(options[i]);
        m = (m >= len)?m:len;
    }
    return m;
}
