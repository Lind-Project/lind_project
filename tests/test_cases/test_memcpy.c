#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    for (size_t i = 0; i<1000000; i++)
    {
        char* str = (char*) malloc(sizeof(char)*1024);
        strcpy(str,"abcdefg");

        char* new_str = (char*) malloc(sizeof(char)*1024);
        memcpy(new_str,str,1024);	
    }

    return 0;
}