#include "./defs.h"

int CreatePair(WINDOW* win){
    /*
        return -3 -> reached eof
        return -2 -> no Word found in letter
        return -1 -> letter not found
        return 0  -> esc is pressed and process end successfully
        return 1  -> no input so do from start
    */

    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        mvwprintw(win,Y/2,X/2-10,"Cant open DATA the file in create pair");
        perror("Cant open the file DATA in create pair");
        wrefresh(win);
    }

    int x = X/20;
    int y = Y/5;
    initTemplate(win, "Insert New Word ");

    const char WordQuery[] = "Enter Word        : ";
    const char MeaningQuery[] = "Enter the Meaning : ";
    char newMeaning[X+x];
    Word_CreatePair:
    switch(mvwlinput(win, data->Word, WordQuery,1,x,y)){
        case 0:
            // successfully got input
            break;
        case 1:
            // no input so repeat from first
            goto Word_CreatePair;
            break;
        case -1:
            // esc is pressed
            CloseData(data);
            return 0;
            break;
    }
    // checking if Word exist
    // moving to word in file
    int wordIndex = ToWord(win,data);
    switch (wordIndex){
        case -1:
            // letter not found
            break;
        case -2:
            // no Word found in letter
            break;
        default:
            mvwprintw(win,Y-2,X/20,"Word Exist in dict, Enter to Continue");
            wrefresh(win);
            while(wgetch(win) != ENTER);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            CloseData(data);
            return 1;
            // word found so printing
            break;
    }
    y += 2;
    Meaning_CreatePair:
    switch(mvwlinput(win, newMeaning,MeaningQuery,2,x,y)){
        case 0:
            // successfully got input
            break;
        case 1:
            // no input so repeat from first
            goto Meaning_CreatePair;
            break;
        case -1:
            // esc is pressed
            CloseData(data);
            return 0;
            break;
    }
    // accessing new file and save
    FILE* out = fopen(TMP_FILE,"w");
    if(out == NULL){
        perror("Cant open out file in CreatePair");
        mvwprintw(win,Y/2,X/2-10,"Cant open the out file in create pair");
        CloseData(data);
        return -1;
    }
    // copying until the letter 
    long fpSRC = CopyInRange(out,data->fp,0,data->LetterPos);//constains src
    // updating the nof meanings
    fscanf(data->fp,"%c-%d,", &data->Letter,&data->nof_Words);
    fprintf(out,"%c-%d,1,",data->Letter,data->nof_Words+1);
    for(int i = 0;i<data->nof_Words;i++){
        int l;fscanf(data->fp,"%d,",&l);
        if(i == wordIndex){
            fprintf(out,"%d,",data->nof_Meaning);
        }else{
            fprintf(out,"%d,",l);
        }
    }
    fputc('\n', out);
    fprintf(out,"^%s\n",data->Word);
    fprintf(out,"~%s",newMeaning);
    long loc = ftell(data->fp);
    fpSRC = CopyInRange(out,data->fp,loc,EOF);
    
    closeFiles(win,data,out,"Successfully created New Word with Meaning");
    CloseData(data);
    return returnChoice(win);
}

int AddMeaning(WINDOW* win){
    /*
        return -3 -> reached eof
        return -2 -> no Word found in letter
        return -1 -> letter not found
        return 0  -> esc is pressed and process end successfully
        return 1  -> no input so do from start
    */

    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        mvwprintw(win,Y/2,X/2-10,"Cant open DATA the file in Add meaning");
        perror("Cant open DATA the file in Add meaning");
        wrefresh(win);
        CloseData(data);

    }
    int x = X/20;
    int y = Y/5;
    initTemplate(win, "Add Another Meaning to Word");

    const char WordQuery[] =    "Enter Word            : ";
    const char MeaningQuery[] = "Enter the new Meaning : ";
    char newMeaning[X+x];
    Word_AddMeaning:
    switch(mvwlinput(win, data->Word, WordQuery,1,x,y)){
        case 0:
            // successfully got input
            break;
        case 1:
            // no input so repeat from first
            goto Word_AddMeaning;
            break;
        case -1:
            // esc is pressed
            CloseData(data);
            return 0;
            break;
    }
    // checking if Word exist
    // moving to word in file
    int wordIndex = ToWord(win,data);
    switch (wordIndex){
        case -1:
            // letter not found
            mvwprintw(win,Y-2,X/20,"Word Doesn't Exist in dict");
            wrefresh(win);
            while(wgetch(win) != ENTER);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            CloseData(data);
            return 1;
            break;
        case -2:
            // no Word found in letter
            mvwprintw(win,Y-2,X/20,"Word Doesn't Exist in dict so Enter a word that exit");
            wrefresh(win);
            while(wgetch(win) != ENTER);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            CloseData(data);
            return 1;
            break;
        default:
            // word found so printing
            break;
    }
    y += 2;
    Meaning_AddMeaning:
    switch(mvwlinput(win, data->Meanings[data->nof_Meaning++],MeaningQuery,2,x,y)){
        case 0:
            // successfully got input
            break;
        case 1:
            // no input so repeat from first
            data->nof_Meaning--;
            goto Meaning_AddMeaning;
            break;
        case -1:
            // esc is pressed
            CloseData(data);
            return 0;
            break;
    }
    // accessing new file and save
    FILE* out = fopen(TMP_FILE,"w");
    if(out == NULL){
        perror("Cant open file out in AddMeaning");
        return -1;
    }
    // copying until the letter 
    long fpSRC = CopyInRange(out,data->fp,0,data->LetterPos);//constains src
    // updating the nof meanings
    fscanf(data->fp,"%c-%d,", &data->Letter,&data->nof_Words);
    fprintf(out,"%c-%d,",data->Letter,data->nof_Words);
    for(int i = 0;i<data->nof_Words;i++){
        int l;fscanf(data->fp,"%d,",&l);
        if(i == wordIndex){
            fprintf(out,"%d,",data->nof_Meaning);
        }else{
            fprintf(out,"%d,",l);
        }
    }
    // updating the before meanings
    long srcLoc = CopyInRange(out,data->fp,ftell(data->fp),data->WordLoc-1);
    fprintf(out,"^%s\n",data->Word);
    for(int i = 0 ;i<data->nof_Meaning;i++){
        fprintf(out,"~%s\n", data->Meanings[i]);
    }
    char tmpWord[X];
    fseek(data->fp,data->WordLoc,SEEK_SET);
    long loc = NextWord(data->fp, tmpWord);
    if(loc == -2){
        fseek(data->fp,data->WordLoc,SEEK_SET);
        loc = NextLetter(data->fp, &tmpWord[0]);
    }
    loc = (loc == -1)?-1:loc - 1; // in case reached EOF
    CopyInRange(out,data->fp,loc,EOF);
    closeFiles(win,data,out,"Successfully create new meaning for the Word");
    CloseData(data);
    return returnChoice(win);
}