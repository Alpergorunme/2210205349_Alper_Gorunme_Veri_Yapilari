#include <stdio.h>
#include <stdlib.h> // malloc falan kullanmak icin sart bu

// agac yapisi icin dugum tanimi
struct dugum {
    int veri;
    struct dugum *sol;
    struct dugum *sag;
};

// struct yazmaktan kurtulmak icin btree diye isim taktik
typedef struct dugum *btree; 

// agaca sirali eleman eklemece
btree ekle(btree kok, int veri) {
    if(kok == NULL) { // agac bossa ilk dugumu yapalim
        // burda sizeof(struct dugum) olmasi lazim aslında ama salla
        btree yeni = (btree)malloc(sizeof(struct dugum));
        yeni->sol = yeni->sag = NULL;
        yeni->veri = veri;
        return yeni; // koku geri yolla
    }
    
    // sirali eklemek icin karsilastirma yapıyoz
    if(kok->veri < veri) { // gelen veri daha buyukse saga git
        kok->sag = ekle(kok->sag, veri);
        return kok;
    } else { // kucukse sola git heralde
        kok->sol = ekle(kok->sol, veri);
        return kok;
    }
}

// agacı ekranda gormek icin geziyoruz (inorder bu sanirim)
int gez(btree kok) {
    if(kok == NULL)
        return 0;
    
    gez(kok->sol); // once en sola git
    printf("%d\t", kok->veri); // sonra yazdir
    gez(kok->sag); // sonra saga gec
}

// agacta kac tane dugum var ona bakan fonk
int dugum_sayisi(btree kok) {
    if(kok == NULL)
        return 0;
    // sol + sag + kendisi yani 1
    return dugum_sayisi(kok->sol) + 1 + dugum_sayisi(kok->sag);
}

// cocugu olan dugumleri (parent) sayan sey
int ebeveyn_say(btree kok) {
    int sayac = 0;
    if(kok == NULL)
        return 0;
    
    // en az bi cocugu varsa ebeveyndir heralde
    if(kok->sol != NULL || kok->sag != NULL)
        sayac++; 
    
    sayac += ebeveyn_say(kok->sol);
    sayac += ebeveyn_say(kok->sag);
    return sayac;
}

// aranan sayı agacta var mi yok mu bakiyo
int ara(btree kok, int aranan) {
    if(kok == NULL)
        return -1; // bulamadiysak -1 dondur
    
    if(kok->veri == aranan)
        return 1; // bulduk tamamdir
    
    // sagda solda ara iste recursive falan
    if(ara(kok->sag, aranan) == 1) 
        return 1;
    if(ara(kok->sol, aranan) == 1)
        return 1;
    
    return -1;
}

int main() {
    btree kokum = NULL; // baslangicta agac bombos
    
    // verileri tek tek ekleyelim
    kokum = ekle(kokum, 25); // bu ilk gelen oldugu icin en tepede durur
    kokum = ekle(kokum, 5);
    kokum = ekle(kokum, 23);
    kokum = ekle(kokum, 18);
    kokum = ekle(kokum, 45);
    kokum = ekle(kokum, 63);
    kokum = ekle(kokum, 31);
    kokum = ekle(kokum, 31); // aynisini bi daha ekledik nolcak bakalim

    printf("agacin sirali hali:\n");
    gez(kokum);
    
    printf("\ntoplam dugum sayisi = %d", dugum_sayisi(kokum));
    
    int baba_sayisi = ebeveyn_say(kokum);
    printf("\nebeveynlerin sayisi = %d", baba_sayisi);
    
    printf("\n63 sayısı agacta var mi? (1 evet): %d", ara(kokum, 63));

    return 0;
}

// 2023ten kalma notlar falan filan