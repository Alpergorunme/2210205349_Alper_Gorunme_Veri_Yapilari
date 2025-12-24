#include <stdio.h>
#include <stdlib.h> // malloc icin bu lazim heralde

// dugum yapisini kucuk harf yaptim
struct dugum {
    int veri;
    struct dugum *sol;
    struct dugum *sag;
};

typedef struct dugum btree; // artik struct yazmaya gerek yok btree diycez

// yeni dugum olusturan yer
btree *yeni_dugum(int veri) {
    btree *p = (btree*) malloc(sizeof(btree));
    p->veri = veri;
    p->sol = NULL; // buralar basta bos kalsin
    p->sag = NULL;
    return p;
}

// agaca eleman eklemece (recursive yapiyo hoca)
btree *ekle(btree *kok, int veri) {
    if(kok != NULL) {
        if(veri < kok->veri) // kucukse sola itele
            kok->sol = ekle(kok->sol, veri);
        else // buyukse saga itele iste
            kok->sag = ekle(kok->sag, veri);
    } else // agac bossa ilk elemani koy
        kok = yeni_dugum(veri);
    
    return kok;
}

// once kok, sonra sol, sonra sag (preorder)
void once_kok(btree *kok) {
    if(kok != NULL) {
        printf("%3d  ", kok->veri); // koku bastik
        once_kok(kok->sol);
        once_kok(kok->sag);
    }
}

// sol, sonra kok, sonra sag (inorder)
// bu sirali gosteriyo galiba
void orta_kok(btree *kok) {
    if(kok != NULL) {
        orta_kok(kok->sol);
        printf("%3d  ", kok->veri);
        orta_kok(kok->sag);
    }
}

// once cocuklar sonra kok (postorder)
void sonra_kok(btree *kok) {
    if(kok != NULL) {
        sonra_kok(kok->sol);
        sonra_kok(kok->sag);
        printf("%3d  ", kok->veri);
    }
}

int main() {
    btree *kokum = NULL;
    int i = 0;
    
    // -1 yazana kadar doncek bu dongu
    do {
        printf("\nagaca veri ekle (bitirmek icin -1): ");
        scanf("%d", &i);
        if(i != -1)
            kokum = ekle(kokum, i);
    } while(i != -1);

    printf("\nonce kok (preorder): ");
    once_kok(kokum);
    
    printf("\norta kok (inorder): ");
    orta_kok(kokum);
    
    printf("\nsonra kok (postorder): ");
    sonra_kok(kokum);

    printf("\nbitti heralde...");
    return 0;
}