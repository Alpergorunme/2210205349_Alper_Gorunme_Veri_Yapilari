#include <stdio.h>
#include <stdlib.h>

// avl agaci icin dugum yapisi, yukseklik de tutuluyo burda
struct avl_dugum {
    int veri;
    struct avl_dugum *sol;
    struct avl_dugum *sag;
    int yukseklik;
};

typedef struct avl_dugum avl_dugum;

// bi dugumun yuksekligini veren basit fonksiyon
int boy(avl_dugum *dugum) {
    if (dugum == NULL)
        return 0; // eleman yoksa boyu da yoktur herhalde
    return dugum->yukseklik;
}

// iki sayidan buyuk olani buluyo, boy hesaplarken lazim
int maks(int a, int b) {
    return (a > b) ? a : b;
}

// sifirdan yeni bi avl dugumu olusturma
avl_dugum *yeni_dugum(int veri) {
    avl_dugum *dugum = (avl_dugum *)malloc(sizeof(avl_dugum));
    dugum->veri = veri;
    dugum->sol = NULL;
    dugum->sag = NULL;
    dugum->yukseklik = 1; // ilk eklenen elemanin boyu 1'dir her zaman
    return dugum;
}

// saga dondurme olayi (agac sola cok yattiginda yapilir)
avl_dugum *saga_dondur(avl_dugum *z) {
    avl_dugum *gecici = z->sol;
    z->sol = gecici->sag;
    gecici->sag = z;

    // dondurme sonrasi boylari guncellememiz lazim
    z->yukseklik = maks(boy(z->sol), boy(z->sag)) + 1;
    gecici->yukseklik = maks(boy(gecici->sol), boy(gecici->sag)) + 1;

    return gecici; // yeni tepe noktasi artik gecici oldu
}

// sola dondurme olayi (agac saga cok yattiginda yapilir)
avl_dugum *sola_dondur(avl_dugum *z) {
    avl_dugum *gecici = z->sag;
    z->sag = gecici->sol;
    gecici->sol = z;

    // buralarda da boylari guncelliyoruz iste
    z->yukseklik = maks(boy(z->sol), boy(z->sag)) + 1;
    gecici->yukseklik = maks(boy(gecici->sol), boy(gecici->sag)) + 1;

    return gecici;
}

// denge bozulmus mu diye bakan fonksiyon (sol eksi sag boyu)
int denge_bul(avl_dugum *dugum) {
    if (dugum == NULL)
        return 0;
    return boy(dugum->sol) - boy(dugum->sag);
}

// agaca eleman ekleyen asil yer
avl_dugum *ekle(avl_dugum *dugum, int veri) {
    // 1. klasik bst ekleme islemi
    if (dugum == NULL)
        return yeni_dugum(veri);
        
    if (veri < dugum->veri)
        dugum->sol = ekle(dugum->sol, veri);
    else if (veri > dugum->veri)
        dugum->sag = ekle(dugum->sag, veri);
    else 
        return dugum; // aynisindan varsa ekleme yapma 

    // 2. yuksekligi guncellemek sart her adimda
    dugum->yukseklik = 1 + maks(boy(dugum->sol), boy(dugum->sag));

    // 3. dengesini kontrol et bakalım bozulmus mu
    int fark = denge_bul(dugum);

    // eger denge bozulduysa 4 tane durum vardi (ll, rr, lr, rl)
    
    // sola yatiksa (sol-sol durumu)
    if (fark > 1 && veri < dugum->sol->veri)
        return saga_dondur(dugum);

    // saga yatiksa (sag-sag durumu)
    if (fark < -1 && veri > dugum->sag->veri)
        return sola_dondur(dugum);

    // solun sagi (zigzag durumu - lr)
    if (fark > 1 && veri > dugum->sol->veri) {
        dugum->sol = sola_dondur(dugum->sol);
        return saga_dondur(dugum);
    }

    // sagin solu (zigzag durumu - rl)
    if (fark < -1 && veri < dugum->sag->veri) {
        dugum->sag = saga_dondur(dugum->sag);
        return sola_dondur(dugum);
    }

    return dugum; // her sey yolundaysa dugumu geri yolla
}

// agaci ekranda yan yatmis sekilde gosteren fonksiyon
void agaci_yazdir(avl_dugum *kok, int bosluk) {
    if (kok != NULL) {
        agaci_yazdir(kok->sag, bosluk + 1);
        for (int i = 0; i < bosluk; i++)
            printf("    ");
        printf("%d\n", kok->veri);
        agaci_yazdir(kok->sol, bosluk + 1);
    }
}

int main() {
    avl_dugum *kokum = NULL;

    // karisik sayilar ekleyelim agac kendi dengelesin
    kokum = ekle(kokum, 10);
    kokum = ekle(kokum, 20);
    kokum = ekle(kokum, 30); // burda kesin dondurme yapar
    kokum = ekle(kokum, 40);
    kokum = ekle(kokum, 50);
    kokum = ekle(kokum, 25); // zigzag olcak heralde burda

    printf("avl agacinin dengelenmis hali:\n");
    agaci_yazdir(kokum, 0);

    return 0;
}