#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
  
int main()
{
    int file_desc = open("tricky.txt", O_CREAT |O_WRONLY | O_APPEND, 0777);
      
    // here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1) ; 
          
    // All the printf statements will be written in the file
    // "tricky.txt"
    printf("I will be printed in the file tricky.txt\n");
      
return 0;
}