#include <stdio.h>
#include <stdlib.h>

// oncelikli kuyruk icin dugum yapisi iste
// kucuk harf yaptim hepsini
typedef struct dugum {
    int veri;       // saklancak sayi 
    int oncelik;    // oncelik degeri (sayi ne kadar kucukse o kadar acil)
    struct dugum* sonraki; // bi sonrakini gosteren pointer
} dugum;

// yeni bi dugum acmak icin lazim olan fonksiyon
dugum* yeni_dugum(int d, int p) {
    dugum* gecici = (dugum*)malloc(sizeof(dugum));
    gecici->veri = d;
    gecici->oncelik = p;
    gecici->sonraki = NULL; // basta bos kalsin burasi heralde
    return gecici;
}

// en bastaki yani en acil olan veriye bakiyoz sadece
int bak(dugum** kafa) {
    return (*kafa)->veri;
}

// en yuksek oncelikli olani kuyruktan atma/silme
void sil(dugum** kafa) {
    dugum* gecici = *kafa;
    (*kafa) = (*kafa)->sonraki;
    free(gecici); // hafizayi geri verelim yazik
}

// veriyi onceligine gore araya bi yere sokuşturma
void ekle(dugum** kafa, int d, int p) {
    dugum* bas = (*kafa);

    // yeni elemani olustur
    dugum* gecici = yeni_dugum(d, p);

    // ozel durum: eger gelen eleman listenin basindakinden daha acilse
    // direk en basa koymamiz lazim kafa degisiyo yani
    if ((*kafa)->oncelik > p) {
        gecici->sonraki = *kafa;
        (*kafa) = gecici;
    }
    else {
        // liste icinde dolasip nereye gircek bu eleman ona bakiyoz
        // siradaki elemanin onceligi daha kucuk oldugu surece devam et 
        while (bas->sonraki != NULL && bas->sonraki->oncelik <= p) {
            bas = bas->sonraki;
        }

        // bulduk yeri simdi araya bagla
        gecici->sonraki = bas->sonraki;
        bas->sonraki = gecici;
    }
}

// kuyruk bombos mu diye kontrol eden basit bisi
int bos_mu(dugum** kafa) {
    return (*kafa) == NULL;
}

// asil program burda basliyo
int main() {
    // ilk elemani olusturarak basla (veri 4 oncelik 1)
    dugum* ok = yeni_dugum(4, 1);

    // bi suru eleman ekleyelim karisik onceliklerde
    ekle(&ok, 5, 2);
    ekle(&ok, 6, 3);
    ekle(&ok, 7, 0);  // bu en acili (0 numara)
    ekle(&ok, 8, 1);
    ekle(&ok, 11, 2);
    ekle(&ok, 18, 1);

    // kuyruk bitene kadar en acil olandan baslayip ekrana bas
    printf("oncelik sirasina gore listeliyoz:\n");
    while (!bos_mu(&ok)) {
        printf("%d ", bak(&ok));
        sil(&ok);
    }

    return 0; // bitti gitti
}