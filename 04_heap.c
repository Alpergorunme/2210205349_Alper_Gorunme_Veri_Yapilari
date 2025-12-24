/* Alper Görünme - 2210205349 */
#include <stdio.h>

void duzelt(int dizi[], int n, int i) {
    int max = i, sol = 2*i+1, sag = 2*i+2;
    if (sol < n && dizi[sol] > dizi[max]) max = sol;
    if (sag < n && dizi[sag] > dizi[max]) max = sag;
    if (max != i) {
        int gecici = dizi[i]; dizi[i] = dizi[max]; dizi[max] = gecici;
        duzelt(dizi, n, max);
    }
}

int main() {
    int dizi[] = {12, 11, 13, 5, 6};
    int n = 5;
    for (int i = n/2 - 1; i >= 0; i--) duzelt(dizi, n, i);
    printf("Max Heap Dizisi: ");
    for (int i = 0; i < n; i++) printf("%d ", dizi[i]);
    return 0;
}
