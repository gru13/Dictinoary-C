#include<defs.h>


int ToWord(WINDOW* win,Data* data){
   int nofMeaning[X]; char Meaning[X][X+X];
    /*
        return -1 -> if word not found
        return index -> if word is found
    */
    switch(ToLetter(win,data,nofMeaning)){
        case -1:
            // letter not found
            mvwprintw(win,Y-2,X/20,"Letter '%c' not Found",data->Letter);
            wrefresh(win);
            Sleep(WAIT);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            return -1;
        case -2:
            // no Word found in letter
            mvwprintw(win,Y-2,X/20,"No Words found in Letter '%c' ",data->Letter);
            wrefresh(win);
            Sleep(WAIT);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            return -2;
        default :
            // no problem so proceed
            break;
    }
  
    char key[X];
    for(int i = 0; i < data->nof_Words; i++){
        long loc = NextWord(data->fp,key);
        mvwprintw(win,Y-2,X/20,"Word : %s",key);
        wrefresh(win);
        Sleep(WAIT);
        if(strcmp(key,data->Word) == 0){
            data->WordLoc = loc;
            data->nof_Meaning = nofMeaning[i];
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            for (int j = 0; j < data->nof_Meaning; j++){
                data->MeaningLoc[j] = NextMeaning(data->fp,data->Meanings[j]);
            }
            return 0;
        }
        mvwhline(win,Y-2,X/20,' ',X - X/20-2);
        wrefresh(win);
    }

    mvwprintw(win,Y-2,X/20,"Word '%s' not found in Letter '%c' ",data->Word,data->Letter);
    wrefresh(win);
    Sleep(WAIT);
    mvwhline(win,Y-2,X/20,' ',X - X/20-2);
    wrefresh(win);
    return -1;
}

int ToLetter(WINDOW* win ,Data* data,int nofMeaning[X]){
    char p;
    while(TRUE){
        long loc = NextLetter(data->fp, &p);
        switch(loc){
            case -1:
                // Letter not Found
                return -1;
                break;
            default:
                break;
        }
        mvwprintw(win,Y-2,X/20,"Letter : %c",p);
        wrefresh(win);
        Sleep(200);
        if(p == data->Letter){
            data->LetterPos = loc;
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            fscanf(data->fp,"-%d,",&data->nof_Words);
            if(data->nof_Words == 0){
                return -2;
            }
            for(int i = 0;i<data->nof_Words;i++){
                fscanf(data->fp,"%d,", &nofMeaning[i]);
            }
            return 0;
        }
        mvwhline(win,Y-2,X/20,' ',X - X/20-2);
        wrefresh(win);
    }
    return -1;
}

long NextLetter(FILE* fp, char*p){
    while (TRUE){
        *p = fgetc(fp);
        if(*p == EOF){
            perror("reached end of file in next Letter");
            return -1;
        }
        if(*p == '@'){
            break;
        }
    }
    long loc = ftell(fp);
    *p = fgetc(fp);
    return loc;
}

long NextWord(FILE* fp, char words[X]){
    char p;
    while(TRUE){
        p = fgetc(fp);
        if(p == EOF){
            perror("reached end of file in next Word");
        }
        if(p == '^'){
            break;
        }
    }
    long loc = ftell(fp);
    fscanf(fp,"%[^\n]s",words);
    return loc;
}

long NextMeaning(FILE* fp, char sent[X+X]){
    char p;
    while(TRUE){
        p = fgetc(fp);
        if(p == EOF){
            perror("reached end of file in next Word");
        }
        if(p == '~'){
            break;
        }
    }
    long loc = ftell(fp);
    fscanf(fp,"%[^\n]s",sent);
    return loc;
}