#include <unistd.h>
#include <fcntl.h>

int main()
{
    int filedesc = open("testfiles/doubleclosefile.txt", O_WRONLY | O_APPEND);
    close(filedesc);
    close(filedesc);

    return 0;
}
