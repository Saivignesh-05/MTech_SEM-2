/**
 * @file tellbook.c
 * @author Sai vignesh (you@domain.com)
 * @brief to register name and number (each only 20 bytes) using unix system calls (lseek,open,write,read)
 * * RUN command ./a.out filename -r record_number OR ./a.out filename -w record_number name number
 * @version 1
 * @date 2023-02-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "/home/student/Desktop/205 - APUE/apue.3e/include/apue.h"

#define LEN 23

void main(int arg, char* arv[])
{
    int fd,rnumber=0,start=0,option; 
    char name[20],number[20],temp=':',readres[40];
    long s1,s2;
    // APPEND doesnt allow lseek to happen. if O_CREAT is used, mode argument must be specified.
    if ((fd = open(arv[1],O_RDWR | O_CREAT, O_APPEND|S_IRUSR | S_IWUSR)) ==-1)
        err_sys("cant create or open the file");

    char *type = (arv[2]);
    printf("File opened success!\n");
    rnumber = atoi(arv[3]);
    start = LEN*(rnumber-1); 


    if (lseek(fd, start, SEEK_SET) == -1)   // seeking to the record position
        err_sys("cant seek");

    if(*type=='w')
    {

        s1 = strlen((arv[4]));
        s2 = strlen((arv[5]));

        if(s1>20 || s2>20)
        {
            printf("name and number must be under 20 characters!\n");
            exit(0);
        }

        if(write(fd,arv[4],s1)!=s1)               // writing the name
            err_sys("write to file error 1");

        if(write(fd," : ",3)!=3)               // writing the # for readability
            err_sys("write to file error 1.5");

        if(write(fd,arv[5],s2)!=s2)             // writing the number
            err_sys("write to file error 2");
        printf("write success!");
    }
    else if(*type=='r')
    {
        if(read(fd,readres,2*LEN)==-1)
            err_sys("read error");
        if(readres[0]=='\0' || readres[0] == 0)
            printf("no record!");
        else
            printf("%s",readres);
    }
    else 
    {
            printf("Invalid argument!\n");
            exit(0);
    }
    
    close(fd);
}

