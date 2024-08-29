#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE* fp = fopen("./data.txt","r");
    char p;
    for(int i = 0;i<2;i++){
        while(1){
            p = fgetc(fp);
            if(p == EOF){
                perror("EOF");
                break;
            }
            if(p == '@'){
                break;
            }
        }  
        p = fgetc(fp);
        if(p != EOF){
            putchar(p);
        }
    }
}