#include<stdio.h>
#include<string.h>
#include"view.h"
#include"edit.h"
#include"types.h"

void MP3_edit(char *id,char *new_name,char *filename){
    //open original MP3 file
    FILE *fp=fopen(filename,"rb");
    if(fp==NULL){
        printf("Invalid File Name\n");
        return;
    }

    //open duplicate MP3 file in write mode
    FILE *dup_fp=fopen("duplicate.mp3","wb");
    if(dup_fp==NULL){
        printf("Invalid File Name\n");
        return;
    }

    //read and write the first 10 bytes of header
    char buffer[10];
    fread(buffer,10,1,fp);
    fwrite(buffer,10,1,dup_fp);

    for(int i=0;i<6;i++){
        //Read the 4 bytes of tag ID
        char tags[5];//4 bytes + NULL
        fread(tags,4,1,fp);
        tags[4]='\0';

        if(strcmp(tags,id)==0){
            //write the tag to the duplicate.mp3
            fwrite(tags,4,1,dup_fp);

            //read the size, convert endianess and store it in variable
            int size=0;
            fread(&size,sizeof(int),1,fp);
            char *ptr=(char *)&size;
            for(int j=0;j<sizeof(size)/2;j++){
                char temp=ptr[j];
                ptr[j]=ptr[sizeof(size)-1-j];
                ptr[sizeof(size)-1-j]=temp;
            }
            int old_size=size;

            //get size of the new content
            int new_size=1+strlen(new_name);
            char *nptr = (char *)&new_size;
            for(int i=0;i<sizeof(new_size)/2;i++){
                char temp=nptr[i];
                nptr[i]=nptr[sizeof(new_size)-1-i];
                nptr[sizeof(new_size)-1-i]=temp;
            }
            fwrite(&new_size,4,1,dup_fp);

            //read and write the flag and null
            char flags[2];
            fread(flags, 2, 1, fp);
            fwrite(flags, 2, 1, dup_fp);

            //Move the file offset to the next tag
            fseek(fp, old_size, SEEK_CUR);

            //write the new content to the duplicate file
            char encoding = 0x00;
            fwrite(&encoding, 1, 1, dup_fp);
            fwrite(new_name, strlen(new_name), 1, dup_fp);

            //Read and write the remaining contents from original to duplicate.mp3
            char ch;
            while (fread(&ch, 1, 1, fp) == 1) {
                fwrite(&ch, 1, 1, dup_fp);
            }
            break;
        }
        else{
            //write the tag to the duplicate.mp3
            fwrite(tags, 4, 1, dup_fp);

            //read the size and write
            //convert size into little endian
            int size=0;
            fread(&size,sizeof(int),1,fp);
            char *ptr=(char *)&size;
            for(int j=0;j<sizeof(size)/2;j++){
                char temp=ptr[j];
                ptr[j]=ptr[sizeof(size)-1-j];
                ptr[sizeof(size)-1-j]=temp;
            }
            fwrite(&size,sizeof(int),1,dup_fp);

            //read and write the flag and null
            char flags[2];
            fread(flags, 2, 1, fp);
            fwrite(flags, 2, 1, dup_fp);

            //based on th size read the content one by one and write it
            char ch;
            for(int i = 0; i < size; i++) {
                fread(&ch, 1, 1, fp);
                fwrite(&ch, 1, 1, dup_fp);
            }
  
        }
    }
    fclose(fp);
    fclose(dup_fp);

    //remove the original file
    remove(filename);
    //rename the duplicate file as an original file
    if (rename("duplicate.mp3", filename) == 0)
    {
        printf("INFO: Tag edited successfully\n");
    }
    else
    {
        printf("ERROR: Failed to update MP3 file\n");
    }
}
