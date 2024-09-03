#include "./defs.h"

void initTemplate(WINDOW* win, const char* heading){
    wclear(win);
    box(win,0,0);
    mvwprintw(win,1,X/2-strlen(heading)/2, heading);
    mvwhline(win,2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
}

int blankScreen(WINDOW* win, int x, int y, int h, int w){
    for(int i = 0; i < h; i++){
        mvwhline(win,y+i,x,' ',w);
    }
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

int returnChoice(WINDOW* win){
    mvwprintw(win,Y/2+1,X/2-11,"<Enter> : next entery");
    mvwprintw(win,Y/2+2,X/2-11,"<Esc> : For Escape");
    wrefresh(win);
    int choice;
    while(TRUE){
        choice = wgetch(win);
        if(choice == enter){
            choice = 1;
            break;
        }
        if(choice == ESC){
            choice = 0;
            break;
        }
    }
    return choice;
}
int DisplayList(WINDOW* win,int x, int y,char List[X][X+X], int listLen){
    /*
        return ESC     -> if ESC pressed
        return cursorY -> if enter is pressed
    */
    int cursorY = 0,ofsetY = 0,ofsetX = 0;
    int heigth = Y-y-4;
    int width = X-x-5;
    int arrowX = x;
    x += 3;
    while(TRUE){
         for(int i =0 ;i<listLen && i < heigth;i++){
            if(cursorY == i && strlen(List[i+ofsetY]) >= width){
                mvwprintw(win,y+i,x, "[%02d]",i+1+ofsetY);

                for(int j = 0;j<strlen(List[i+ofsetY]) && j+x+5 < X - 5;j++){
                    mvwprintw(win,y+i,x+5+j,"%c",List[i+ofsetY][j+ofsetX]);
                }

            }else if(strlen(List[i+ofsetY]) >= width){
                mvwprintw(win,y+i,x, "[%02d]",i+1+ofsetY);
                for(int j = 0;j<strlen(List[i+ofsetY]) && j+x+5 < X - 5;j++){
                    mvwprintw(win,y+i,x+5+j,"%c",List[i+ofsetY][j]);
                }

            }else{
                mvwprintw(win,y+i,x,"[%02d] %s",i+1+ofsetY,List[i+ofsetY]);
            }

        }

        mvwprintw(win,y+cursorY,arrowX,"->");
        wrefresh(win);
        int choice = wgetch(win);
        char Num[100];
        int numIndex = 0;
        Num[0] = '\0';
        switch (choice){
            case enter:
                blankScreen(win,x-3,y,heigth,width);
                return cursorY;
            case ESC:
                blankScreen(win,x-3,y,heigth,width);
                return ESC;
            case down:
                ofsetX = 0;
                mvwprintw(win,y+cursorY,arrowX,"  ");
                cursorY++;
                if(cursorY >= heigth || cursorY + ofsetY >= listLen){
                    cursorY--;
                    ofsetY++;
                    if(ofsetY + cursorY >=  listLen){
                        ofsetY--;
                    }
                }
                mvwprintw(win,y+cursorY,arrowX,"->");
                wrefresh(win);
                break;
            case up:
                ofsetX = 0;
                mvwprintw(win,y+cursorY,arrowX,"  ");
                cursorY--;
                if(cursorY <= -1){
                    cursorY++;
                    ofsetY--;
                    if(ofsetY <= 0){
                        ofsetY = 0;
                    }
                }
                mvwprintw(win,y+cursorY,arrowX,"->");
                wrefresh(win);
                break;
            case rigth:
                if(ofsetX + X - 10 - x < strlen(List[cursorY+ofsetY])){
                    ofsetX++;
                }
                break;
            case left:
                ofsetX = (ofsetX <= 0)?0:ofsetX-1;
                break;
            default:
                 while(choice >= '0' && choice <= '9'){
                    Num[numIndex++] = choice;
                    Num[numIndex] = '\0';
                    choice = wgetch(win);
                    if(choice == enter){
                        break;
                    }
                }
                int oldY = cursorY;
                int n = atoi(Num);
                if(n > 0 && n <= listLen){
                    cursorY = n - 1;
                    if(cursorY < heigth){
                        ofsetY = 0;
                    }else if(cursorY >= heigth){
                        ofsetY = cursorY - heigth + 1;
                        cursorY = heigth-1;
                    }
                }
                mvwprintw(win, y+oldY, arrowX, "  ");
                mvwprintw(win, y+cursorY, arrowX, "->");
                wrefresh(win);
                break;
        }
    }
    blankScreen(win,x-3,y,heigth,width);
    return cursorY;
} 

