#include "./defs.h"

int removeWord(WINDOW* win){
    initTemplate(win,"Remove the Word and Meaning");
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

    // updating the file

    FILE* out = fopen(TMP_FILE,"w");
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
    fputc(fgetc(data->fp), out); // this add '\n'
    
    CopyInRange(out,data->fp,ftell(data->fp),data->WordLoc);
    char tmpWord[X];
    NextWord(data->fp,tmpWord);
    CopyInRange(out,data->fp,ftell(data->fp),EOF);

    mvwprintw(win,Y-2,(X/20),"Writing in file");
    wrefresh(win);
    fclose(out);
    fclose(data->fp);

    closeFiles(win,data,out,"Successfully delete the Word meaning Pair");

    wrefresh(win);
    return returnChoice(win);
}