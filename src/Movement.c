#include<defs.h>



int toLetter(WINDOW* win ,FILE* fp,char L, int* nofWord, int nofMeaning[X]){
    char p = 'a';
    while(p < 'z'){
        p = nextLetter(fp);
        mvwprintw(win,Y-2,X/20,"Letter : %c",p);
        wrefresh(win);
        Sleep(200);
        if(p == L){
            mvwhline(win,Y-2,X/20,' ',X - X/20);
            wrefresh(win);
            fscanf(fp,"-%d,",nofWord);
            if(*nofWord == 0){
                return 2;
            }
            for(int i = 0;i<*nofWord;i++){
                fscanf(fp,"%d,", &nofMeaning[i]);
            }
            return 0;
        }
        mvwhline(win,Y-2,X/20,' ',X - X/20);
        wrefresh(win);
    }
    return 1;
}
int toWord(WINDOW* win,FILE* fp, char Word[X], int nofWord, int nofMeaning[nofWord], char Meaning[X][X+X]){
    /*
        return -1 -> if word not found
        return index -> if word is found
    */
    char key[X];
    for(int i = 0; i < nofWord; i++){
        nextWord(fp,key);
        mvwprintw(win,Y-2,X/20,"Word : %s",key);
        wrefresh(win);
        Sleep(300);
        if(strcmp(key,Word) == 0){
            mvwhline(win,Y-2,X/20,' ',X - X/20);
            wrefresh(win);
            for (int j = 0; j < nofMeaning[i]; j++){
                nextMeaning(fp,Meaning[j]);
            }
            
            return i;
        }
        mvwhline(win,Y-2,X/20,' ',X - X/20);
        wrefresh(win);
    }
    return -1;
}

char nextLetter(FILE* fp){
    char p;
    while (TRUE){
        p = fgetc(fp);
        if(p == EOF){
            perror("reached end of file in next Letter");
        }
        if(p == '@'){
            break;
        }
    }
    p = fgetc(fp);
    return p;
}
int nextWord(FILE* fp, char words[X]){
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
    fscanf(fp,"%[^\n]s",words);
    return 0;
}
int nextMeaning(FILE* fp, char sent[X+X]){
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
    fscanf(fp,"%[^\n]s",sent);
    return 0;
}