/* Alper Görünme - 2210205349 */
#include <stdio.h>

void hanoiCoz(int n, char kule1, char kule2, char kule3) {
    if (n == 1) {
        printf("Disk 1: %c -> %c\n", kule1, kule2);
        return;
    }
    hanoiCoz(n - 1, kule1, kule3, kule2);
    printf("Disk %d: %c -> %c\n", n, kule1, kule2);
    hanoiCoz(n - 1, kule3, kule2, kule1);
}

int main() {
    hanoiCoz(3, 'A', 'C', 'B');
    return 0;
}
