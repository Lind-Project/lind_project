#include <stdio.h>
#include <string.h>

int main() {
    const char *filename = "testfile.txt";

    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    const int buffer_size = 9000;
    char buffer[buffer_size];
    const char* base_string = "discussions of his work—which has inquired into the mechanisms of pain, manipulation, and lies—with a reminder";
    buffer[0] = '\0';

    printf("1");

    for (int i = 0; i < 80; ++i) {
        strcat(buffer, base_string);
    }

    fprintf(file, "%s", buffer);

    fclose(file);

    printf("File created: %s\n", filename);

    return 0;
}
