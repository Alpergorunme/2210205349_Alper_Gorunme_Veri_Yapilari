/* Alper Görünme - 2210205349 */
#include <stdio.h>

int main() {
    int matris[3][3] = {{5, 0, 0}, {0, 8, 0}, {0, 0, 3}};
    printf("Seyrek Matris Formu (Satir - Sutun - Deger):\n");
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matris[i][j] != 0) {
                printf("%d\t%d\t%d\n", i, j, matris[i][j]);
            }
        }
    }
    return 0;
}
