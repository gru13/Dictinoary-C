#include "defs.h"

int DEBUG = 0;

int main(){
    char options[][X+X] = {"Search for Word",
                        "Create a Word and Meaning",
                        "Add Meaning to Word",
                        "Remove Word and Meaning",
                        "Remove a Meaning",
                        "list Words in a letter",
                        "Print All Words",
                        "Reset the file",
                        "Exit"};
    int State = TRUE;
    int nof_opts = 8;

    initscr();
    WINDOW* win = newwin(Y,X,0,0);
    keypad(win,TRUE);
    cbreak();
    noecho();
    curs_set(FALSE);
    int Exit;

    if(!checkFileExist(DATA_FILE)){
        box(win,0,0);
        mvwprintw(win,Y/2,X/2-11,"The Data File not Found");
        mvwprintw(win,Y/2+1,X/2-15,"Enter to continue and create new");
        mvwprintw(win,Y/2+2,X/2-38,"Esc,If you have a old data file please move the data file to this directory");
        wrefresh(win);
        while(TRUE){
            int choice = wgetch(win);
            if(choice == ENTER){
                ResetFile(win,0);
                break;
            }
            if(choice == ESC){
                Exit = 0;
                break;
            }
        }      
    }
    
    int x = X/2 - maxlenArray(options,nof_opts)/2 - 15;
    int y = Y/2 - nof_opts/2;
    int choice = 0;
    START_MAIN:
    Exit = 1;
    while(Exit){
        initTemplate(win,TITLE);
        if(checkFileExist(TMP_FILE)){
            int remove_attempts = 0;
            while (remove(DATA_FILE) != 0 && remove_attempts < 5) {
                Sleep(500);  // Wait a bit before trying again
                remove_attempts++;
            }

            if (remove_attempts == 5) {
                return -1;
            }

            if (rename(TMP_FILE, DATA_FILE) != 0) {
                return -2;
            }
        }
        choice = DisplayList(win,x,y,options,nof_opts, choice);
        switch (choice){
            case ESC:
                Exit = 0;
                break;
            case 0:
                while(search(win));
                break;
            case 1:
                while(CreatePair(win));
                break;
            case 2:
                while(AddMeaning(win));
                break;
            case 3:
                while(removeWord(win));
                break;
            case 4:
                while(removeMeaning(win));
                break;
            case 5:
                while(WordsInLetter(win));
                break;
            case 6:
                while(AllWords(win));
                break;
            case 7:
                ResetFile(win,1);
                break;
            case 8:
                Exit = 0;
                break;
            default:
                break;
        }  
        Sleep(500);
    }
    initTemplate(win,"EXIT");
    mvwprintw(win, Y/2, X/2 - 10, "Press <ESC> To Exit");
    mvwprintw(win, Y/2 + 1, X/2 - 21, "Press <Enter> to continue without exiting");
    wrefresh(win);
    while(TRUE){
        char c = wgetch(win);
        if(c == ENTER){
            goto START_MAIN;
            break;
        }
        if(c == ESC){
            break;
        }
    }
    endwin();
    return 0;
}


int maxlenArray(char arr[X][X+X],int arrLen){
    int len = 0, m = 0;
    for(int i = 0;i<len;i++){
        len = strlen(arr[i]);
        m = (m >= len)?m:len;
    }
    return m;
}


