#include <stdio.h>

// diziyi tersine cevirelim simdi
void ters_cevir(int dizi[], int boyut) {
    int gecici, i;
    // ortaya kadar gitsek yetiyo herhalde, hepsini gezsek eski haline doner yine
    for (i = 0; i < boyut / 2; i++) {
        gecici = dizi[i];
        dizi[i] = dizi[boyut - 1 - i];
        dizi[boyut - 1 - i] = gecici;
    }
}


// araya bi seyler ekleme (insert)
void eleman_ekle(int dizi[], int *n, int eleman, int sira) {
    // sondan baslayip saga dogru kaydiriyoz yer acilsin diye
    for (int i = *n; i > sira; i--) {
        dizi[i] = dizi[i - 1];
    }
    dizi[sira] = eleman; // acilan yere yeni sayiyi koyduk bitti
    (*n)++; // eleman sayisi artti haliyle
}


// eleman silme islemi burda
void eleman_sil(int dizi[], int *n, int sira) {
    // silinen yer bos kalmasin diye her seyi sola cekiyoruz
    for (int i = sira; i < *n - 1; i++) {
        dizi[i] = dizi[i + 1];
    }
    (*n)--; // bi eleman eksildi iste
}

int main() {
    int sayilar[100] = {10, 20, 30, 40, 50};
    int adet = 5;

    printf("ilk hali: ");
    for(int i=0; i<adet; i++) printf("%d ", sayilar[i]);

    // ters cevir bakalim nolcak
    ters_cevir(sayilar, adet);
    printf("\nters donmus hali: ");
    for(int i=0; i<adet; i++) printf("%d ", sayilar[i]);

    // araya 99 sokusturalim
    eleman_ekle(sayilar, &adet, 99, 2); // 2. indexe 99 koyalim
    printf("\n99 ekledikten sonra: ");
    for(int i=0; i<adet; i++) printf("%d ", sayilar[i]);

    return 0; 
}