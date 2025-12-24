#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev; // Çift bağlı liste için önceki düğüm göstericisi
};

// Yeni düğüm oluşturma (Senin bst.c dosyasındaki mantıkla)
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = temp->prev = NULL;
    return temp;
}

// 1. Listenin sonuna eleman ekleme
void insertEnd(struct Node** head, int data) {
    struct Node* temp = newNode(data);
    if (*head == NULL) {
        *head = temp;
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL) last = last->next;
    last->next = temp;
    temp->prev = last;
}

// 2. Araya eleman ekleme (Belirli bir düğümden sonraya)
void insertAfter(struct Node* prev_node, int data) {
    if (prev_node == NULL) return;
    struct Node* temp = newNode(data);
    temp->next = prev_node->next;
    prev_node->next = temp;
    temp->prev = prev_node;
    if (temp->next != NULL) temp->next->prev = temp;
}

// 3. Tüm listeyi silme (Recursive - Ödev gereksinimi)
void deleteAllRecursive(struct Node* head) {
    if (head == NULL) return;
    deleteAllRecursive(head->next); // Önce sonrakileri sil
    printf("%d siliniyor... ", head->data);
    free(head); // Sonra kendini sil
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);
    insertAfter(head->next, 25); // 20'den sonra 25 ekle

    printf("Çift Bağlı Liste: ");
    printList(head);

    printf("Liste siliniyor:\n");
    deleteAllRecursive(head);
    head = NULL;

    return 0;
}