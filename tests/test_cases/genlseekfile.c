#include <stdio.h>

int main() {
    const char *filename = "testfile.txt";

    // 打开文件以写入方式
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    const int buffer_size = 2048;
    char buffer[buffer_size];

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    size_t bytes_written = fwrite(buffer, 1, buffer_size, file);

    if (bytes_written != buffer_size) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }
    
    fclose(file);

    printf("File created: %s\n", filename);

    return 0;
}
