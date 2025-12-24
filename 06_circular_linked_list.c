/* Alper Görünme - 2210205349 */
#include <stdio.h>
#include <stdlib.h>

struct Node { int veri; struct Node *next; };

int main() {
    struct Node *bas = (struct Node*)malloc(sizeof(struct Node));
    struct Node *son = (struct Node*)malloc(sizeof(struct Node));
    bas->veri = 1; bas->next = son;
    son->veri = 2; son->next = bas; // Dairesel baglanti

    printf("Dairesel Liste: %d -> %d -> (Basa Doner)\n", bas->veri, son->next->veri);
    return 0;
}
