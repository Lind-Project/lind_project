#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    int row, col;
    long fileSize = 0;
    const int targetSize = 10 * 1024; 

    // Open a file in write mode
    fp = fopen("10K.csv", "w");
    if (fp == NULL) {
        printf("Cannot open file.\n");
        return -1;
    }

    // Write column names
    fprintf(fp, "ID,Age,Income,Score\n");

    srand(time(NULL)); // Seed for random number generation

    while (fileSize < targetSize) {
        for (col = 0; col < 4; col++) { // Change to 4 columns
            int num = rand() % 1000; // Generate a random number between 0 and 999
            fprintf(fp, "%d", num);

            if (col < 3) {
                fputc(',', fp); // Add a comma after each number except the last one in a row
            }
        }
        fputc('\n', fp); // Newline after each row

        // Update the estimated file size (approximation)
        fileSize += 4 * 4 + 1; // 4 characters per number and 1 for newline
    }

    // Close the file
    fclose(fp);
    printf("File generated successfully.\n");

    return 0;
}
