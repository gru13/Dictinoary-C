#include "./defs.h"

int removeWord(WINDOW* win){
    /*
        return -3 -> cant open File
        return -2 -> No Words found in Letter '%c' 
        return -1 -> NO Word found in letter
        return  0 ->  all done no issue exiting the process
        return  1 -> repeating the whole function
    */
    initTemplate(win,"Remove the Word and Meaning");
    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        perror("Cant open data file in removeWord");
        return -1;
    }
    const char query[] = "Enter Word to Remove : ";
    switch (mvwlinput(win,data->Word,query, 1, X/20, Y/5)){
        case 0:
            // sucessfully got input
            break;
        case 1:
            // no input so repeat from first
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return 1;
            break;
        case -1:
            // esc is pressed
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return 0;
            break;
    }
    int WordIndex = ToWord(win,data);
    switch(WordIndex){
        case -1:
            // NO Word found in letter
            mvwprintw(win,Y/2,X/2 - 10 ,"Word '%s' not Found",data->Word);
            wrefresh(win);
            Sleep(1000);
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return -1;
            break;
        case -2:
            // No Words found in Letter '%c' 
            mvwprintw(win,Y/2,X/2 - 10 ,"No Words Found in Letter '%c'",data->Letter);
            wrefresh(win);
            Sleep(1000);
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return -2;
            break;
        default:
            /* Word Found so continue*/
            break;
    }

    // updating the file
    // copying until the letter 
    FILE* out = fopen(TMP_FILE, "w");
    if(out == NULL){
        perror("Cant open out file in removeWord");
        return -1;
    }
    long fpSRC = CopyInRange(out,data->fp,0,data->LetterPos);//constains src
    // updating the nof meanings
    fseek(data->fp,data->LetterPos,SEEK_SET);
    fscanf(data->fp,"%c-%d,", &data->Letter,&data->nof_Words);
    fprintf(out,"%c-%d,",data->Letter,data->nof_Words-1);
    for(int i = 0;i<data->nof_Words;i++){
        int l;
        fscanf(data->fp,"%d,",&l);
        if(WordIndex != i){
            fprintf(out,"%d,",l);
        }
    }
    // fputc('\n',out);
    // fgetc(data->fp);
    // fputc(fgetc(data->fp), out); // this add '\n'
    char tmpWord[X];
    int nofMw[X];
    CopyInRange(out,data->fp,ftell(data->fp)+1,data->WordLoc-1);
    ToWord(win, data);
    CopyInRange(out,data->fp,ftell(data->fp),EOF);
    closeFiles(win,data,out,"Successfully delete the Word meaning");
    wrefresh(win);
    
    if (data->fp != NULL) {
        fclose(data->fp);
        data->fp = NULL;
    }
    free(data);
    return returnChoice(win);
}


int removeMeaning(WINDOW* win){
    /*
        return -1 -> cant open file
    */
    initTemplate(win,"Remove the Meaning");
    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE, "r");
    if(data->fp == NULL){
        perror("Cant open file in removeMeaning");
        mvwprintw(win,Y-2,X/20,"Cant open file in removeMeaning");
        wrefresh(win);
        return -1;
    }
    int x = X/20;
    int y = Y/7;
    const char query[] = "Enter the word Remove : ";
    mvwhline(win,y+2,1,WA_HORIZONTAL,X-2);
    wrefresh(win);
    switch (mvwlinput(win,data->Word,query, 1, x, y)){
        case 0:
            data->Letter = data->Word[0];
            // sucessfully got input
            break;
        case 1:
            // no input so repeat from first
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return 1;
            break;
        case -1:
            // esc is pressed
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return 0;
            break;
    }
    int WordIndex = ToWord(win,data);
    switch(WordIndex){
        case -1:
            // NO Word found in letter
            mvwprintw(win,Y/2,X/2 - 10 ,"Word '%s' not Found",data->Word);
            wrefresh(win);
            Sleep(1000);
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return -1;
            break;
        case -2:
            // No Words found in Letter '%c' 
            mvwprintw(win,Y/2,X/2 - 10 ,"No Words Found in Letter '%c'",data->Letter);
            wrefresh(win);
            Sleep(1000);
            if (data->fp != NULL) {
                fclose(data->fp);
                data->fp = NULL;
            }
            free(data);
            return -2;
            break;
        default:
            /* Word Found so continue*/
            break;
    }
    if(data->nof_Meaning == 0){
        mvwprintw(win,Y/2,X/2-16,"NO meaning found in '%s",data->Word);
        wrefresh(win);
        if (data->fp != NULL) {
            fclose(data->fp);
            data->fp = NULL;
        }
        free(data);
        return returnChoice(win);
    }
    y += 5;
    FILE* out = fopen(TMP_FILE, "w");
    mvwprintw(win,y,x,"Select the meaning and type Enter :");
    int indexChosen = DisplayList(win,x+10,y+2,data->Meanings,data->nof_Meaning);

    long fpSRC = CopyInRange(out, data->fp,0,data->LetterPos);

    fscanf(data->fp,"%c-%d,", &data->Letter,&data->nof_Words);
    fprintf(out,"%c-%d,",data->Letter,data->nof_Words);
    for(int i = 0;i<data->nof_Words;i++){
        int l;fscanf(data->fp,"%d,",&l);
        if(i == WordIndex){
            fprintf(out,"%d,",data->nof_Meaning-1);
        }else{
            fprintf(out,"%d,",l);
        }
    }
    fpSRC = CopyInRange(out,data->fp,ftell(data->fp), data->MeaningLoc[indexChosen]-1);
    if(indexChosen == data->nof_Meaning - 1 || (indexChosen == 0 && data->nof_Meaning == 1)){
        char TmpWord[X];
        long loc = NextWord(data->fp,TmpWord);
        if(loc == -2){
            loc = NextLetter(data->fp,&TmpWord[0]);
        }
        fpSRC = CopyInRange(out,data->fp,loc-1,EOF);
    }else{
        fpSRC = CopyInRange(out,data->fp,data->MeaningLoc[indexChosen+1]-1,EOF);
    }
    mvwprintw(win,Y-2,2,"%d",indexChosen);
    wrefresh(win);

    closeFiles(win,data,out,"Successfully delete the Word meaning Pair");
    if (data->fp != NULL) {
        fclose(data->fp);
        data->fp = NULL;
    }
    free(data);
    return returnChoice(win);
}