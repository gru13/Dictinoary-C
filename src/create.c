#include "./defs.h"

int CreatePair(WINDOW* win){
    
    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        mvwprintw(win,Y/2,X/2-10,"Cant open the file");
        wrefresh(win);
    }

    int x = X/20;
    int y = Y/5;
    initTemplate(win, "Insert New Word ");

    const char WordQuery[] = "Enter Word        : ";
    const char MeaningQuery[] = "Enter the Meaning : ";
    char newMeaning[X+x];
    strcpy(data->Word,"dart");
    switch(mvwlinput(win, data->Word, WordQuery,1,x,y)){
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
            mvwprintw(win,Y-2,X/20,"Word Exist in dict");
            wrefresh(win);
            Sleep(WAIT);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            return 1;
            // word found so printing
            break;
    }
    y += 2;
    switch(mvwlinput(win, newMeaning,MeaningQuery,2,x,y)){
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
    // acessing new file and save
    FILE* out = fopen("Out.txt","w");
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
    fprintf(out,"~%s\n",newMeaning);
    char temp[X];
    int itemp[X];
    fseek(data->fp, data->LetterPos,SEEK_SET);
    // ToLetter(win,data,itemp);
    long loc;
    while(fgetc(data->fp) != '\n'){}

    loc = ftell(data->fp);
    fpSRC = CopyInRange(out,data->fp,loc,-1);
    
    mvwprintw(win,Y-2,(X/20),"Writing in file");
    wrefresh(win);
    Sleep(1000);
    fclose(out);
    fclose(data->fp);
    remove(DATA_FILE);
    rename("Out.txt",DATA_FILE);
    return 0;
}

int AddMeaning(WINDOW* win){
    /*
        return -3 -> reached eof
        retrun -2 -> no Word found in letter
        return -1 -> letter not found
        return 0  -> esc is pressed and process end sucessfully
        return 1  -> no input so do from start
    */

    Data* data = (Data*)malloc(sizeof(Data));
    data->fp = fopen(DATA_FILE,"r");
    if(data->fp == NULL){
        mvwprintw(win,Y/2,X/2-10,"Cant open the file");
        wrefresh(win);
    }

    int x = X/20;
    int y = Y/5;
    initTemplate(win, "Add Another Meaning to Word");

    const char WordQuery[] =    "Enter Word            : ";
    const char MeaningQuery[] = "Enter the new Meaning : ";
    char newMeaning[X+x];
    switch(mvwlinput(win, data->Word, WordQuery,1,x,y)){
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
    // checking if Word exist
    // moving to word in file
    int wordIndex = ToWord(win,data);
    switch (wordIndex){
        case -1:
            // letter not found
            mvwprintw(win,Y-2,X/20,"Word Doesn't Exist in dict");
            wrefresh(win);
            Sleep(WAIT);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            return 1;
            break;
        case -2:
            // no Word found in letter
            mvwprintw(win,Y-2,X/20,"Word Doesn't Exist in dict so Enter a word that exit");
            wrefresh(win);
            Sleep(WAIT);
            mvwhline(win,Y-2,X/20,' ',X - X/20-2);
            wrefresh(win);
            return 1;
            break;
        default:
            // word found so printing
            break;
    }
    y += 2;
    switch(mvwlinput(win, data->Meanings[data->nof_Meaning++],MeaningQuery,2,x,y)){
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
    // acessing new file and save
    FILE* out = fopen("Out.txt","w");
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
    fputc('\n', out);
    fputc('^', out);
    // updated the topbar
    fseek(data->fp,data->LetterPos,SEEK_SET);
    char temp[X];
    long loc = NextWord(data->fp,temp);
    switch (loc){
        case -1:
            // reached eof
            return -3;
            break;
        default:
            break;
    }

    fpSRC = CopyInRange(out,data->fp,loc,data->WordLoc);//constains src

    fprintf(out,"%s\n",data->Word);
    for(int i =0;i<data->nof_Meaning;i++){
        fprintf(out,"~%s\n",data->Meanings[i]);
    }

    fseek(data->fp,data->WordLoc,SEEK_SET);    
    loc = NextWord(data->fp,temp);
    fpSRC = CopyInRange(out,data->fp,loc,-1);//constains src
    fclose(out);
    mvwprintw(win,Y-2,(X/20),"Writing in file");
    wrefresh(win);
    Sleep(1000);
    fclose(out);
    fclose(data->fp);
    remove(DATA_FILE);
    rename("Out.txt",DATA_FILE);
    return 0;
}