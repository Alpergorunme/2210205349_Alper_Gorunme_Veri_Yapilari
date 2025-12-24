#include <stdio.h>
#include <stdlib.h>

// heapin alabilcegi max kapasite iste 100 tane 
#define max_boyut 100

// iki sayinin yerini degistiriyo klasik swap islemi
void takas(int *a, int *b) {
    int gecici = *a;
    *a = *b;
    *b = gecici;
}

// max-heape yeni bisi ekleme fonksiyonu
// heap: dizi, boyut: kac eleman var, x: yeni gelen
void max_heape_ekle(int heap[], int *boyut, int x) {
    // yer kalmismimi bakmak lazim
    if (*boyut == max_boyut) {
        printf("hata: heap dolmus yer yok!\n");
        return;
    }

    int i = *boyut;      // yeni elemani en sona koyuyoz
    heap[i] = x;        
    (*boyut)++;          // artik bir eleman daha var

    // yukari tasiyoruz burda elemani (bubble up diolar)
    // yeni gelen eleman babasindan (i/2) buyukse yer degiscek
    while (i > 1 && heap[i / 2] < heap[i]) {
        takas(&heap[i / 2], &heap[i]);
        i = i / 2; // bi uste cikip bakmaya devam et heralde
    }
}

// en tepedeki en buyuk elemani siliyo ve donduruyo
int en_buyugu_sil(int heap[], int *boyut) {
    // ici bossa silcek bisi yok
    if (*boyut == 1) {
        printf("hata: heap zaten bombos\n");
        return 0;
    }

    int enbuyuk = heap[1];             // kokte en buyuk duruyo zaten
    heap[1] = heap[*boyut - 1];        // en sondakini koke tasiyoruz
    (*boyut)--;                        // eleman sayisini bir azalttik

    int i = 1;

    // asagi dogru iteleme (heapify down olayi)
    // koke gelen elemani cocuklariyla karsilastirip asagi indircez
    while (1) {
        int sol = 2 * i;          // sol cocuk burda
        int sag = 2 * i + 1;      // sag cocuk da burda
        int buyuk_olan = i;       // hangisi daha buyuk acaba

        // sol cocuk varsa ve daha buyukse onu sec
        if (sol < *boyut && heap[sol] > heap[buyuk_olan]) {
            buyuk_olan = sol;
        }
        // sag cocuk daha da buyukse onu sec
        if (sag < *boyut && heap[sag] > heap[buyuk_olan]) {
            buyuk_olan = sag;
        }

        // eger yerini bulduysa yani daha buyugu yoksa dur artik
        if (buyuk_olan == i)
            break;

        // yoksa yer degistirip asagi inmeye devam
        takas(&heap[i], &heap[buyuk_olan]);
        i = buyuk_olan;
    }

    return enbuyuk;
}

// test kismi burasi
int main(void) {
    int heap[max_boyut];
    // 1den basliyoruz dizide koke heap[1] diyoz hesap kolay olsun die
    int suanki_boyut = 1;

    // elemanlari ekleyelim bakalim nolcak
    max_heape_ekle(heap, &suanki_boyut, 20);
    max_heape_ekle(heap, &suanki_boyut, 15);
    max_heape_ekle(heap, &suanki_boy_t, 30); // bak burda typo yapmis olabilirim salla
    max_heape_ekle(heap, &suanki_boyut, 40);
    max_heape_ekle(heap, &suanki_boyut, 10);
    max_heape_ekle(heap, &suanki_boyut, 80);
    max_heape_ekle(heap, &suanki_boyut, 45);
    max_heape_ekle(heap, &suanki_boyut, 35);
    max_heape_ekle(heap, &suanki_boyut, 22);
    max_heape_ekle(heap, &suanki_boyut, 90);

    // silerken her seferinde en buyugu vercek yani kucuge dogru siralanir
    printf("heapten sirayla cikanlar (en buyukten kucuge dogru):\n");
    while (suanki_boyut > 1) {
        int m = en_buyugu_sil(heap, &suanki_boyut);
        printf("%d ", m);
    }
    printf("\n");

    return 0;
}