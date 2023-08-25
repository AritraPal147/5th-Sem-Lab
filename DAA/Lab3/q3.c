/*
    A and B are playing a guessing game where B first thinks up an 
    integer X (positive, negative or zero and could be of rbitrarily large magnitude)
    and A tries to guess it. In response to A's guess, B gives exactly
    the following three replies:
    a) Try a bigger number
    b) Try a smaller number or
    c) You got it.
    Write a program by designing an efficient algorithm to minimize the number
    of guesses A has to make. An example (not necessarily an efficient one) is
    given below:
    Assume B thinks up the number 35.
    A's guess B's response
    10 Try a bigger number
    20 Try a bigger number
    30 Try a bigger number
    40 Try a smaller number
    35 You got it
*/

#include <stdio.h>
int main() {
    int num;
    printf("Enter B's number: ");
    scanf("%d", &num);

    int max = 9999, min = -9999;
    int guess;
    while (min <= max) {
        guess = min + (max - min)/2;
        if (guess > num) {
            max = guess-1;
            printf("\n%d Try a smaller number", guess);
        }
        else if (guess < num) {
            min = guess+1;
            printf("\n%d Try a bigger number", guess);
        }
        else {
            printf("\n%d You got it\n\n", guess);
            break;
        }
    }

    return 0;
}