/* Alper Görünme - 2210205349 */
#include <stdio.h>

int main() {
    int dizi[10] = {10, 20, 30, 40};
    int n = 4;
    
    // Sona ekleme
    dizi[n++] = 50;
    
    // Silme (2. eleman)
    for(int i = 1; i < n; i++) dizi[i] = dizi[i+1];
    n--;

    printf("Dizi Son Durum: ");
    for(int i=0; i<n; i++) printf("%d ", dizi[i]);
    return 0;
}
