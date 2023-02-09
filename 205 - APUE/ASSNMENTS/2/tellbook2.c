// #include<stdio.h>
// #include <unistd.h>
// void main(int argc, char* argv[])
// {
//     char c = getopt(argc,argv,"rw:");
//     printf("char is : %c\n",c);
// }

/**
 * @file tellbook2.c
 * @author sai vignesh s
 * @brief  using getopt from unistd.h to decode the flags from command line arguments
 * * RUN command ./a.out filename -r record_number OR ./a.out filename -w record_number name number
 * @version 2 
 * @date 2023-02-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "/home/student/Desktop/205 - APUE/apue.3e/include/apue.h"

#define RLEN 23
#define MAX 20
#define SEP 3
// ./a.out filename -r record_number 
// ./a.out filename -w record_number name number

void main(int arc, char* arv[])
{
    int fd,rnumber=0,start=0; 
    char readres[2*RLEN],seperator[SEP] = " : ";
    long s1,s2,maxrecords=0;
    // APPEND doesnt allow lseek to happen. if O_CREAT is used, mode argument must be specified.
    if ((fd = open(arv[1],O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) ==-1)
        err_sys("cant create or open the file");

    printf("File opened success!\n");

    char type = getopt(arc,arv,"rw:");

    if(lseek(fd,0,SEEK_SET) == lseek(fd,0,SEEK_END))
    {
        if((maxrecords = lseek(fd,(atoi(arv[2])+1)*RLEN,SEEK_SET))==-1)
            printf("cant seek");

        if(write(fd,"e",1)!=1)               // writing the name
            err_sys("write to file error 1");
        
        // printf("max rec : %ld",maxrecords);

        if(type == 'r')
        {
                printf("Cant read empty file \n");
                exit(0);
        }

    }
    else 
    {
     if((maxrecords = lseek(fd,0,SEEK_END))==-1)
            printf("cant seek");
    

        // printf("max rec 1: %ld",(maxrecords)/RLEN - 1);   
        maxrecords = (maxrecords)/RLEN - 1;
    }
    rnumber = atoi(arv[4]);
    start = RLEN*(rnumber); 

    // printf("max rec new : %ld , %d",maxrecords,rnumber);

    if(rnumber>maxrecords)
    {
                printf("Exceeded the max records of : %ld \n",maxrecords);
                exit(0);
    }
    if (lseek(fd, start, SEEK_SET) == -1)   // seeking to the record position
        err_sys("cant seek");

    switch(type)
    {
        case 'r':
            if(read(fd,readres,2*RLEN)==-1)
                err_sys("read error");
            if(readres[0]=='\0')
                printf("no record!");
            else
                printf("\nthe record is%s",readres);
            break;
        case 'w':
            s1 = strlen((arv[5]));
            s2 = strlen((arv[6]));

            printf("name : %s, number : %s",arv[5],arv[6]);

            if(s1>20 || s2>20)
            {
                printf("name and number must be under 20 characters!\n");
                exit(0);
            }

            if(write(fd,arv[5],s1)!=s1)               // writing the name
                err_sys("write to file error 1");

            if(write(fd,seperator,3)!=3)               // writing the # for readability
                err_sys("write to file error 1.5");

            if(write(fd,arv[6],s2)!=s2)             // writing the number
                err_sys("write to file error 2");
            printf("write success!");
            break;
        default:
            break;

    }
    
    close(fd);
}