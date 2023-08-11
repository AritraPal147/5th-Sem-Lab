/*
    Write a program in C to find GCD of two numbers using recursion. Read 
    all pair of numbers from a file and store the result in a separate file. 
    Note# Source file name and destination file name taken from command line 
    arguments. The source file must contain at least 20 pairs of numbers.

    Give the contents of the input disc file “inGcd.dat” as  8  12  20  45  30  80

    Contents of the output disc file “outGcd.dat” as 
    The GCD of 8 and 12 is 4
    The GCD of 20 and 45 is 5
    The GCD of 30 and 80 is 10

    Terminal Input:
    $gcc lab2q2.c -o lab2q2
    $./lab2q2 inGcd.dat outGcd.dat

    Output: Display the gcd stored in the output file outGcd.dat
*/

#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) 
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    FILE *sourceFile = fopen(argv[1], "r");
    if (!sourceFile) {
        printf("Error opening source file.\n");
        return 1;
    }

    FILE *destinationFile = fopen(argv[2], "w");
    if (!destinationFile) {
        printf("Error opening destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    int num1, num2;
    while (fscanf(sourceFile, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(destinationFile, "The GCD of %d and %d is %d\n", num1, num2, result);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    // Display the contents of the output file
    destinationFile = fopen(argv[2], "r");
    if (!destinationFile) {
        printf("Error opening destination file for reading.\n");
        return 1;
    }

    printf("Contents of the output file %s:\n", argv[2]);
    char line[100];
    while (fgets(line, sizeof(line), destinationFile)) {
        printf("%s", line);
    }

    fclose(destinationFile);

    return 0;
}
