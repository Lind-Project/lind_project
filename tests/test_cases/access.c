#include <stdio.h>
#include <unistd.h>

int main(){
    const char* filename = "user.txt";
    // Check whether the filename exits by F_OK
    int result = access(filename, F_OK);
    
    if(result == -1){
        perror("access");
        printf("File %s does not exist or cannot be accessed.\n", filename);
        return 1;
    }else{
        
    }
}