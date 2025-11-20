#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#define INITIAL_SIZE 1000

int mainCode() {
    printf("Pie OS\n\n\
         (\n\
          )\n\
     __..---..__\n\
 ,-='  /  |  \\  `=-.\n\
:--..___________..--;\n\
 \\.,_____________,./\n\n\
");
    
    int size = INITIAL_SIZE;
    int *a = malloc(size * sizeof(int));
    if (!a) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }
    for (int i = 0; i < size; i++) a[i] = 2;

    int nines = 0, predigit = 0, digits_printed = 0;
    int expand_threshold = (size * 3) / 10;

    // "Warmup" for the first digit
    {
        long long sum = 0, x;
        for (int i = size - 1; i > 0; i--) {
            x = (long long)a[i] * 10 + sum;
            a[i] = (int)(x % (2LL * i + 1));
            sum = (x / (2LL * i + 1)) * i;
        }
        x = (long long)a[0] * 10 + sum;
        a[0] = (int)(x % 10);
        int carry = (int)(x / 10); // should be 3
        printf("%d.", carry);
        predigit = 0;
        nines = 0;
    }

    while (1) {
        // Expand buffer if needed
        if (digits_printed >= expand_threshold) {
            int new_size = size * 2;
            int *new_a = malloc(new_size * sizeof(int));
            if (!new_a) {
                fprintf(stderr, "\nReallocation failed\n");
                free(a);
                return 1;
            }
            for (int i = 0; i < size; i++) new_a[i] = a[i];
            for (int i = size; i < new_size; i++) new_a[i] = 2;
            free(a);
            a = new_a;
            size = new_size;
            expand_threshold = (size * 3) / 10;
        }

        // Produce next digit
        long long sum = 0, x;
        for (int i = size - 1; i > 0; i--) {
            x = (long long)a[i] * 10 + sum;
            a[i] = (int)(x % (2LL * i + 1));
            sum = (x / (2LL * i + 1)) * i;
        }
        x = (long long)a[0] * 10 + sum;
        a[0] = (int)(x % 10);
        int q = (int)(x / 10);

        // Spigot carry handling
        if (q == 9) {
            nines++;
        } else if (q == 10) {
            putchar(predigit + 1 + '0');
            for (int k = 0; k < nines; k++) putchar('0');
            predigit = 0;
            nines = 0;
            digits_printed += 1 + nines;
        } else {
            putchar(predigit + '0');
            for (int k = 0; k < nines; k++) putchar('9');
            predigit = q;
            digits_printed += 1 + nines;
            nines = 0;
        }
        fflush(stdout);
    }

    // (never reached)
    free(a);
    return 0;
}

#ifndef WRAPPED_BUILD
int main(void) {
  return mainCode();
}
#endif
