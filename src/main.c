#include "defs.h"

char options[NOP][X] = {"Search for Word",
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
    while(Exit){
        int choice = menu(win);
        switch (choice){
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

