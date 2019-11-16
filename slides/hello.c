#include <stdio.h>

int main() {
    int a = 10;
    float total = 0;
    char *b = "hello";

    for (int i = 0; i < a; i++) {
        total += i*0.5;
    }

    printf("The total is: %.2f\n", total);
    printf("The word is is: %s\n", b);

    return 0;
}
