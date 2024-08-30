#include<defs.h>


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