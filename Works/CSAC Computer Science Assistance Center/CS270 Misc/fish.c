/* fish.c
 *
 */

#include <stdio.h>

int main()
{
    int num1 = 5;
    double num2 = 7.07777;
    char letter = 'a';

    printf("Fish is cool\n");
    char *fish = "Fish is cool\n";
    printf("Not %s\n\n", fish);

    printf("This is num1 %d%d%d%d\n", num1, num1, num1, num1);
    printf("This is num2 %f\n", num2);
    printf("This is letter %c\n", letter);
    return 0;
}
