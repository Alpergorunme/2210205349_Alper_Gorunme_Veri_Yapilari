#include <stdio.h>
#include <stdlib.h>

// avl agaci icin dugum yapisi, boy tutmak onemli
struct dugum {
    int anahtar;
    struct dugum *sol;
    struct dugum *sag;
    int yukseklik;
};

// boyu veren fonksiyon, bossa sıfır dondurur herhalde
int boy(struct dugum *n) {
    if (n == NULL)
        return 0;
    return n->yukseklik;
}

// iki sayidan buyuk olani buluyo iste klasik
int maks(int a, int b) {
    return (a > b) ? a : b;
}

// yeni dugum acma, ilk boyu 1 olur yaprak sonucta
struct dugum* yeni_dugum(int anahtar) {
    struct dugum* d = (struct dugum*)malloc(sizeof(struct dugum));
    d->anahtar = anahtar;
    d->sol = NULL;
    d->sag = NULL;
    d->yukseklik = 1; 
    return d;
}

// saga dondurme (single right rotation diyolar buna)
struct dugum *saga_dondur(struct dugum *y) {
    struct dugum *x = y->sol;
    struct dugum *t2 = x->sag;

    // dondurme yapalim
    x->sag = y;
    y->sol = t2;

    // boylari guncelle yoksa denge sasar
    y->yukseklik = maks(boy(y->sol), boy(y->sag)) + 1;
    x->yukseklik = maks(boy(x->sol), boy(x->sag)) + 1;

    return x; // yeni koku dondur
}

// sola dondurme (agac saga cok yatarsa kullaniriz)
struct dugum *sola_dondur(struct dugum *x) {
    struct dugum *y = x->sag;
    struct dugum *t2 = y->sol;

    // dondurme islemi
    y->left = x; // burasi sol olmaliydi ama kucuk harf yaptim sol
    y->sol = x; 
    x->sag = t2;

    // guncellemeleri unutma
    x->yukseklik = maks(boy(x->sol), boy(x->sag)) + 1;
    y->yukseklik = maks(boy(y->sol), boy(y->sag)) + 1;

    return y;
}

// denge faktoru (sol boyu - sag boyu)
int denge_al(struct dugum *n) {
    if (n == NULL)
        return 0;
    return boy(n->sol) - boy(n->sag);
}

// agaca eleman ekleme, ekledikten sonra dengeye bakiyo
struct dugum* ekle(struct dugum* dugum, int anahtar) {
    // 1. klasik bst eklemesi
    if (dugum == NULL)
        return(yeni_dugum(anahtar));

    if (anahtar < dugum->anahtar)
        dugum->sol = ekle(dugum->sol, anahtar);
    else if (anahtar > dugum->anahtar)
        dugum->sag = ekle(dugum->sag, anahtar);
    else 
        return dugum; // aynisi varsa ekleme bosver

    // 2. boyu guncelle
    dugum->yukseklik = 1 + maks(boy(dugum->sol), boy(dugum->sag));

    // 3. denge bozuldu mu? 4 tane durum var
    int denge = denge_al(dugum);

    // sol sol durumu
    if (denge > 1 && anahtar < dugum->sol->anahtar)
        return saga_dondur(dugum);

    // sag sag durumu
    if (denge < -1 && anahtar > dugum->sag->anahtar)
        return sola_dondur(dugum);

    // sol sag durumu (zigzag)
    if (denge > 1 && anahtar > dugum->sol->anahtar) {
        dugum->sol = sola_dondur(dugum->sol);
        return saga_dondur(dugum);
    }

    // sag sol durumu (zigzag)
    if (denge < -1 && anahtar < dugum->sag->anahtar) {
        dugum->sag = saga_dondur(dugum->sag);
        return sola_dondur(dugum);
    }

    return dugum;
}

// silerken yerine gececek en kucuk elemani bulma (sagin en solu)
struct dugum * en_kucuk_dugum(struct dugum* dugum) {
    struct dugum* suanki = dugum;
    while (suanki->sol != NULL)
        suanki = suanki->sol;
    return suanki;
}

// avl'den dugum silme, asil olay burda
struct dugum* sil(struct dugum* kok, int anahtar) {
    // 1. standart bst silme islemi
    if (kok == NULL)
        return kok;

    if (anahtar < kok->anahtar)
        kok->sol = sil(kok->sol, anahtar);
    else if(anahtar > kok->anahtar)
        kok->sag = sil(kok->sag, anahtar);
    else {
        // silinecek olan bu iste, cocuklarina bakcaz
        if((kok->sol == NULL) || (kok->sag == NULL)) {
            struct dugum *gecici = kok->sol ? kok->sol : kok->sag;

            if (gecici == NULL) { // cocugu yoksa
                gecici = kok;
                kok = NULL;
            }
            else // tek cocugu varsa
                *kok = *gecici;
            free(gecici);
        }
        else {
            // iki cocugu varsa sagin en kucugunu koke tasi
            struct dugum* gecici = en_kucuk_dugum(kok->sag);
            kok->anahtar = gecici->anahtar;
            kok->sag = sil(kok->sag, gecici->anahtar);
        }
    }

    if (kok == NULL)
        return kok;

    // 2. boyu tekrar guncelle
    kok->yukseklik = 1 + maks(boy(kok->sol), boy(kok->sag));

    // 3. denge bozulduysa dondurme yapalim yine
    int denge = denge_al(kok);

    // ll durumu
    if (denge > 1 && denge_al(kok->sol) >= 0)
        return saga_dondur(kok);

    // lr durumu
    if (denge > 1 && denge_al(kok->sol) < 0) {
        kok->sol = sola_dondur(kok->sol);
        return saga_dondur(kok);
    }

    // rr durumu
    if (denge < -1 && denge_al(kok->sag) <= 0)
        return sola_dondur(kok);

    // rl durumu
    if (denge < -1 && denge_al(kok->sag) > 0) {
        kok->sag = saga_dondur(kok->sag);
        return sola_dondur(kok);
    }

    return kok;
}

// ekrana basarken once kok sonra cocuklar (preorder)
void yazdir(struct dugum *kok) {
    if(kok != NULL) {
        printf("%d ", kok->anahtar);
        yazdir(kok->sol);
        yazdir(kok->sag);
    }
}

int main() {
    struct dugum *kokum = NULL;

    // agacı kuralim
    kokum = ekle(kokum, 9);
    kokum = ekle(kokum, 1);
    kokum = ekle(kokum, 10);
    kokum = ekle(kokum, 11);
    kokum = ekle(kokum, 5);
    kokum = ekle(kokum, 0);
    kokum = ekle(kokum, -1);
    kokum = ekle(kokum, 2);
    kokum = ekle(kokum, 6);

    printf("silmeden once agac (preorder): ");
    yazdir(kokum);

    printf("\n10 sayisi siliniyor heralde...");
    kokum = sil(kokum, 10);

    printf("\nsilindikten sonra agac: ");
    yazdir(kokum);

    return 0;
}