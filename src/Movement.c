#include<defs.h>


char nextLetter(FILE* fp){
    char p;
    while (TRUE){
        p = fgetc(fp);
        if(p == EOF){
            perror("cant print");
        }
        if(p == '@'){
            break;
        }
    }
    p = fgetc(fp);
    return p;
}
int nextWord(FILE* fp, char words[X]){
    return 0;
}
int nextMeaning(FILE* fp){

    return 0;
}