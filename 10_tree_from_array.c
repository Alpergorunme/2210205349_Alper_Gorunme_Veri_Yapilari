/* Alper Görünme - 2210205349 */
#include <stdio.h>
#include <stdlib.h>

struct Node { int veri; struct Node *sol, *sag; };

struct Node* agacYap(int dizi[], int i, int n) {
    if (i >= n) return NULL;
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->veri = dizi[i];
    root->sol = agacYap(dizi, 2*i+1, n);
    root->sag = agacYap(dizi, 2*i+2, n);
    return root;
}

int main() {
    int dizi[] = {1, 2, 3, 4, 5};
    struct Node* kok = agacYap(dizi, 0, 5);
    printf("Agac Kökü: %d, Solu: %d, Sagi: %d\n", kok->veri, kok->sol->veri, kok->sag->veri);
    return 0;
}
