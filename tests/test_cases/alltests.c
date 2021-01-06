 // using code from from https://stackoverflow.com/questions/41362754/reading-with-pread-and-writing-with-pwrite-in-c

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{

    int fd, r, nr, nr2, w, nw, nw2;
    char filename[]={"pwrite.txt"};
    char buf_wr[]={"Lind is amazing!"};
    char buf_wr2[]={"NYU is amazing!"};
    char buf_wr3[]={"Hello There!"};
    char buf_rd[120];
    char buf_rd2[120];
    char buf_rd3[120];
    char buf_rd4[120];
    
    //clear file
    fclose(fopen(filename, "w"));

    //open file
    fd = open(filename, O_RDWR|O_CREAT, 0777);
    nw = pwrite(fd, buf_wr, strlen(buf_wr), 30);

    //error checking
    if(fd == -1){
        perror("[error in open]\n");
    }
    else if(nw == -1){
        printf("[file is opened]\n");
        perror("[error in pwrite]\n");
    }
    else{
        //display succeeded message about first write and open process
        printf("[file is opened]\n");
        printf("[succeeded pwrite(1) process]\n");
        printf("[reading(1) data] from %s\n", filename);

        /*if open and write process are ok, read first write data
        * from file*/
        nr = pread(fd, buf_rd, strlen(buf_wr)-1,30);

        //read process error control
        if(nr == -1){
            perror("[error in read]\n");
        } else{
            printf("[%s]\n", buf_rd);
        }

    }
    
    w = write(fd, buf_wr3, strlen(buf_wr3)-1);
    
    //write error checking
    if(w == -1){
        perror("[error in write]\n");
    }else{

        /*if write process is correct*/

        printf("-----------------------------------\n");
        printf("[succeeded write process]\n");
        printf("[reading(2) data] from %s\n", filename);
        
        lseek (fd, 0, SEEK_SET);
        
        //read second write data from file
        r = read(fd, buf_rd3, strlen(buf_wr3)-1);

        //read process error control
        if(r == -1){
            perror("[error in read2]\n");
        } else{
            printf("[%s]\n", buf_rd3);
        }
    }
    

    //second pwrite process.
    nw2= pwrite(fd, buf_wr2, strlen(buf_wr2), 50);

    //write error checking
    if(nw2 == -1){
        perror("[error in pwrite 2]\n");
    }else{

        /*if write process is correct
        * second read process*/

        printf("-----------------------------------\n");
        printf("[succeeded pwrite(2) process]\n");
        printf("[reading(3) data] from %s\n", filename);

        //read second write data from file
        nr2 = pread(fd, buf_rd2, strlen(buf_wr2)-1, 50);

        //read process error control
        if(nr2 == -1){
            perror("[error in read3]\n");
        } else{
            printf("[%s]\n", buf_rd2);
        }
        
        
        lseek (fd, 50, SEEK_SET);
        
        read(fd, buf_rd4, strlen(buf_wr3)-1);
        printf("[reading(4) data] from %s\n", filename);
        printf("[%s]\n", buf_rd4);
        
    }
    
    

    //error checking for close process
    if(close(fd) == -1){
        perror("[error in close]\n");
    }else{
        printf("[succeeded in close]\n");
    }

    return 0;
}
