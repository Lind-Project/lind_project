#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    int row, col;
    long fileSize = 0;
    const int targetSize = 1024 * 1024; // 1MB in bytes

    // Open a file in write mode
    fp = fopen("output.csv", "w");
    if (fp == NULL) {
        printf("Cannot open file.\n");
        return -1;
    }

    // Write column names
    fprintf(fp, "NetID,Price,Outcome,Income,Score\n");

    srand(time(NULL)); // Seed for random number generation

    // Keep writing until file size is approximately 1MB
    while (fileSize < targetSize) {
        for (col = 0; col < 5; col++) {
            int num = rand() % 1000; // Generate a random number (you can adjust the range)
            fprintf(fp, "%d", num);

            if (col < 4) {
                fputc(',', fp); // Add a comma after each number except the last one in a row
            }
        }
        fputc('\n', fp); // Newline after each row

        // Update the estimated file size (approximation)
        fileSize += 5 * 4 + 1; // 4 characters per number and 1 for newline
    }

    // Close the file
    fclose(fp);
    printf("File generated successfully.\n");

    return 0;
}
