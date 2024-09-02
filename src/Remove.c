#include "./defs.h"

int removeWord(WINDOW* win){
    initTemplate(win,options[3]);
    Data* data = (Data*)malloc(sizeof(Data));
    const char query[] = "Enter Word to Remove : ";
    switch (mvwlinput(win,data->Word,query, 1, X/20, Y/5)){
        case 0:
            // sucessfully got input
            break;
        case 1:
            // no input so repeat from first
            return 1;
            break;
        case -1:
            // esc is pressed
            return 0;
            break;
    }
    data->fp = fopen(DATA_FILE,"r");
    int WordIndex = ToWord(win,data);
    switch(WordIndex){
        case -1:
            // NO Word found in letter
            mvwprintw(win,Y/2,X/2 - 10 ,"Word '%s' not Found",data->Word);
            wrefresh(win);
            Sleep(1000);
            return -1;
            break;
        case -2:
            // No Words found in Letter '%c' 
            mvwprintw(win,Y/2,X/2 - 10 ,"No Words Found in Letter '%c'",data->Letter);
            wrefresh(win);
            Sleep(1000);
            return -2;
            break;
        default:
            /* Word Found so continue*/
            break;
    }
    FILE* out = fopen("Out.txt","w");
    // copying until the letter 
    long fpSRC = CopyInRange(out,data->fp,0,data->LetterPos);//constains src
    // updating the nof meanings
    fseek(data->fp,data->LetterPos,SEEK_SET);
    fscanf(data->fp,"%c-%d,", &data->Letter,&data->nof_Words);
    fprintf(out,"%c-%d,",data->Letter,data->nof_Words-1,WordIndex);
    for(int i = 0;i<data->nof_Words;i++){
        int l;
        fscanf(data->fp,"%d,",&l);
        if(WordIndex == i){
            continue;
        }
        fprintf(out,"%d,",l);
    }
    fputc('\n', out);
    // letter line printed to
    // next until the word
    fseek(data->fp,data->LetterPos, SEEK_SET);
    while(fgetc(data->fp) != '\n'){}
    CopyInRange(out,data->fp,ftell(data->fp),data->WordLoc);
    
    // printting from the next letter
    char Ctemp;
    fseek(data->fp, data->Letter,SEEK_SET);
    long loc = NextLetter(data->fp,&Ctemp);
    fputc('@', out);
    switch(loc){
        case -1:
            break;
        default:
            fpSRC = CopyInRange(out,data->fp,loc, -1);//constains src
            break;
    }
    fclose(out);
    fclose(data->fp);
    return 0;
}