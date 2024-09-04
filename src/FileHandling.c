#include<defs.h>


int ToWord(WINDOW* win,Data* data){
    /*
        return -1  -> NO Word found in letter
        return -2  -> No Words found in Letter '%c' 
        return -3  -> reached end of file
        return -4  -> reacheed next Letter
        return >=0 -> if word is found
    */
    rewind(data->fp);
   int nofMeaning[X]; char Meaning[X][X+X];
    data->Letter = data->Word[0];
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
        switch (loc){
            case -1:
                // reached eof
                return -3;
                break;
            case -2:
                // reached next letter
                return -4;
                break;
            default:
                break;
        }
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
            return i;
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
    /*
        return -1  -> Letter not Found and reached eof
        return -2  -> No Words found in Letter '%c' 
        return >=0 -> if word is found
    */
    char p;
    while(TRUE){
        long loc = NextLetter(data->fp, &p);
        switch(loc){
            case -1:
                // Letter not Found and reached eof
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
    /*
        return -> -1 reached eof
        return -> >=0 no error 
    */ 
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
    /*
        return -> -1 reached eof
        return -> -2 reached next letter
        return -> >=0 no error 
    */ 
    char p;
    while(TRUE){
        p = fgetc(fp);
        if(p == EOF){
            perror("reached end of file in next Word");
            return -1;
        }
        if(p == '@'){
            return -2;
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
    /*
        return -> -1 reached eof
        return -> -2 reached next Word
        return -> >=0 no error 
    */ 
    char p;
    while(TRUE){
        p = fgetc(fp);
        if(p == EOF){
            perror("reached end of file in next Word");
            return -1;
        }
        if(p == '^'){
            return -2;
        }
        if(p == '~'){
            break;
        }
    }
    long loc = ftell(fp);
    fscanf(fp,"%[^\n]s",sent);
    return loc;
}

int CopyInRange(FILE* to, FILE* from ,long start, long until){
    /*
        return 0 -> sucessfull
        return -1 -> if reaced the eof
    */
    if(until == -1){
        fseek(from,0,SEEK_END);
        until =  ftell(from);
    }
    fseek(from,start,SEEK_SET);
    while(ftell(from) < until){
        char c = fgetc(from);
        if(c == EOF){
            return -1;
        }
        fputc(c,to);
    }
    return 0;
}


int ResetFile(WINDOW* win, int flag){
    /*
        flag -> 0 will not print in window
        flag -> 1 will print the details in window
        return -1 -> cant open the file
        return -2 -> cant close the file4
        return  0 -> all ok
     */
   FILE* fp = fopen(DATA_FILE,"w");
   if(fp == NULL){
    return -1;
   }
   if(flag){
        initTemplate(win,"Reseting the file");
   }

   for (char l = 'a'; l <= 'z'; l++){
    fprintf(fp,"@%c-0,\n",l);
   }
   if(fclose(fp) != 0) {
        perror("Error closing Data file");
        return -2;
    }

   if(flag){
        mvwprintw(win, Y/2,X/2-10,"FILE RESET Complete");
        wrefresh(win);
        return returnChoice(win);
   }else{
    return 0;
   }
}

int checkFileExist(const char* file_name){
    /*
        return 1 -> if exist 
        return 0 -> if not exist
    */
    if (access(file_name, F_OK) != -1){
        return 1;
    }else{
        return 0;
    }
}


int closeFiles(WINDOW* win, Data* data, FILE* out, const char successText[X]) {
    mvwprintw(win, Y-2, (X/20), "Writing in file");
    wrefresh(win);
    Sleep(1000);

    if (data->fp != NULL) {
        fclose(data->fp);
        data->fp = NULL;
    }
    if (out != NULL) {
        fclose(out);
        out = NULL;
    }

    Sleep(500);

    int remove_attempts = 0;
    while (remove(DATA_FILE) != 0 && remove_attempts < 5) {
        Sleep(500);  // Wait a bit before trying again
        remove_attempts++;
    }

    if (remove_attempts == 5) {
        mvwprintw(win, Y-2, X/20, "Error in deleting the old file");
        wrefresh(win);
        Sleep(1000);
        return -1;
    }

    if (rename(TMP_FILE, DATA_FILE) != 0) {
        mvwprintw(win, Y-2, X/20, "Error in renaming the file");
        wrefresh(win);
        Sleep(1000);
        return -2;
    } else {
        mvwprintw(win, Y/2, X/2-strlen(successText)/2, successText);
        wrefresh(win);
    }

    return 0;
}