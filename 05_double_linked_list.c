/* Alper Görünme - 2210205349 */
#include <stdio.h>
#include <stdlib.h>

struct Node { int veri; struct Node *next, *prev; };

int main() {
    struct Node *n1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *n2 = (struct Node*)malloc(sizeof(struct Node));
    n1->veri = 50; n1->prev = NULL; n1->next = n2;
    n2->veri = 100; n2->prev = n1; n2->next = NULL;

    printf("Liste (Ileri): %d -> %d\n", n1->veri, n2->veri);
    return 0;
}
