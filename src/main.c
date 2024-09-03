#include "defs.h"




int main(){
    char options[][X+X] = {"Search for Word",
                        "Create a Word and Meaning",
                        "Add Meaning to Word",
                        "Remove Word and Meaning",
                        "Remove a Meaning",
                        "list Words in a letter",
                        "Reset the file",
                        "Exit"};
    int State = TRUE;
    int nof_opts = 8;
    initscr();
    keypad(stdscr,TRUE);
    cbreak();
    noecho();
    curs_set(FALSE);
    WINDOW* win = newwin(Y,X,0,0);
    int Exit = 1;
    int x = X/2 - maxlenArray(options,nof_opts)/2 - 15;
    int y = Y/2 - nof_opts/2;
    while(Exit){
        initTemplate(win,TITLE);
        int choice = DisplayList(win,x,y,options,nof_opts);
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
                break;
            case 5:
                while(WordsInLetter(win));
                break;
            case 6:
                ResetFile(win,1);
                break;
            case 7:
                Exit = 0;
                break;
            default:
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


