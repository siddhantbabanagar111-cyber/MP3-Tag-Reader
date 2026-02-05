#include<stdio.h>
#include<string.h>
#include"view.h"
#include"edit.h"
#include"types.h"

void MP3_view(char *argv[]){
    char buffer[4]; //3 bytes + NULL

    //open sample MP3 file
    FILE *fptr=fopen(argv[2],"rb");
    if(fptr==NULL){
        printf("Invalid File Name\n");
        return;
    }

    //fetch the first 3 bytes of header  
    fread(buffer,3,1,fptr);
    buffer[3]='\0';

    //compare the buffer with "ID3" to check file is MP3 or not
    if(strcmp(buffer,"ID3")==0){
        printf("This File is an MP3 file\n");
    }
    else{
        printf("Error: This File is not an MP3 file\n");
        fclose(fptr);
        return;
    }

    //skip the next 7 bytes after "ID3"
    fseek(fptr,7,SEEK_CUR);
    
    for(int i=0;i<6;i++){
        //Read the 4 bytes of tag ID
        char tags[5];//4 bytes + NULL
        fread(tags,4,1,fptr);
        tags[4]='\0';

        //read the 4 bytes of size content
        int size=0;
        fread(&size,sizeof(int),1,fptr);
        char *ptr=(char *)&size;
        for(int j=0;j<sizeof(size)/2;j++){
            char temp=ptr[j];
            ptr[j]=ptr[sizeof(size)-1-j];
            ptr[sizeof(size)-1-j]=temp;
        }
        //printf("Size is %d\n",size);

        //skip 2 bytes of data(2 flags + 1 NULL)
        fseek(fptr,2,SEEK_CUR);
        
        char content[size + 1];
        fread(content, size, 1, fptr);
        content[size] = '\0';

        printf("%s : %s\n", tags,content+1);
    }
    fclose(fptr);
}  