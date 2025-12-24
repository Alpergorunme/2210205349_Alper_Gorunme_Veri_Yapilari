#include <stdio.h>
#include <stdlib.h>

// avl agaci icin dugum yapisi
struct dugum {
  int anahtar;
  struct dugum *sol;
  struct dugum *sag;
  int yukseklik;
};

// boyu hesaplayan yardimci fonksiyon
int boy(struct dugum *n) {
  if (n == NULL)
    return 0; // bossa boyu yoktur herhalde
  return n->yukseklik;
}

// iki sayidan buyuk olani bulma, yukseklik guncellerken lazim
int maks(int a, int b) {
  return (a > b) ? a : b;
} 

// yeni bi dugum olusturalim
struct dugum *yeni_dugum(int anahtar) {
  struct dugum *d = (struct dugum *)malloc(sizeof(struct dugum));
  d->anahtar = anahtar;
  d->sol = NULL;
  d->sag = NULL;
  d->yukseklik = 1; // ilk basta boyu 1 kabul ediyoz
  return (d);
}

// saga dondurme (agac sola cok yatarsa lazim)
struct dugum *saga_dondur(struct dugum *y) {
  struct dugum *x = y->sol;
  struct dugum *t2 = x->sag;

  x->sag = y;
  y->sol = t2;

  // boylari guncellemeyi unutma yoksa denge sasar
  y->yukseklik = maks(boy(y->sol), boy(y->sag)) + 1;
  x->yukseklik = maks(boy(x->sol), boy(x->sag)) + 1;

  return x;
}

// sola dondurme (agac saga cok yatarsa lazim)
struct dugum *sola_dondur(struct dugum *x) {
  struct dugum *y = x->sag;
  struct dugum *t2 = y->sol;

  y->sol = x;
  x->sag = t2;

  x->yukseklik = maks(boy(x->sol), boy(x->sag)) + 1;
  y->yukseklik = maks(boy(y->sol), boy(y->sag)) + 1;

  return y;
}

// denge faktorunu bulalım (sol eksi sag boyu)
int denge_al(struct dugum *n) {
  if (n == NULL)
    return 0;
  return boy(n->sol) - boy(n->sag); 
}

// agaca eleman ekleme fonksiyonu
struct dugum *ekle(struct dugum *dugum, int anahtar) {
  // bst mantigiyla yerini bulup ekleyelim once
  if (dugum == NULL)
    return (yeni_dugum(anahtar));

  if (anahtar < dugum->anahtar)
    dugum->sol = ekle(dugum->sol, anahtar);
  else if (anahtar > dugum->anahtar)
    dugum->sag = ekle(dugum->sag, anahtar);
  else
    return dugum; // aynisi varsa ekleme salla gitsin

  // boylari guncelle ve dengeyi kontrol et
  dugum->yukseklik = 1 + maks(boy(dugum->sol), boy(dugum->sag));

  int denge = denge_al(dugum);
  
  // ll durumu
  if (denge > 1 && anahtar < dugum->sol->anahtar)
    return saga_dondur(dugum);

  // rr durumu
  if (denge < -1 && anahtar > dugum->sag->anahtar)
    return sola_dondur(dugum);

  // lr durumu (zigzag)
  if (denge > 1 && anahtar > dugum->sol->anahtar) {
    dugum->sol = sola_dondur(dugum->sol);
    return saga_dondur(dugum);
  }

  // rl durumu (zigzag)
  if (denge < -1 && anahtar < dugum->sag->anahtar) {
    dugum->sag = saga_dondur(dugum->sag);
    return sola_dondur(dugum);
  }

  return dugum;
}

// silerken yerine gececek en kucuk elemani bulma (sagin en solu)
struct dugum *en_kucuk_deger_dugumu(struct dugum *dugum) {
  struct dugum *suanki = dugum;
  while (suanki->sol != NULL)
    suanki = suanki->sol;
  return suanki;
}

// agactan eleman silme fonksiyonu
struct dugum *sil(struct dugum *kok, int anahtar) {
  if (kok == NULL)
    return kok;

  if (anahtar < kok->anahtar)
    kok->sol = sil(kok->sol, anahtar);
  else if (anahtar > kok->anahtar)
    kok->sag = sil(kok->sag, anahtar);
  else {
    // silinecek olani bulduk napcaz simdi?
    if ((kok->sol == NULL) || (kok->sag == NULL)) {
      struct dugum *gecici = kok->sol ? kok->sol : kok->sag;

      if (gecici == NULL) { // cocugu yoksa
        gecici = kok;
        kok = NULL;
      } else // tek cocugu varsa
        *kok = *gecici;
      free(gecici);
    } else { 
      // iki cocugu varsa sagin en kucugunu koke tasi
      struct dugum *gecici = en_kucuk_deger_dugumu(kok->sag);
      kok->anahtar = gecici->anahtar;
      kok->sag = sil(kok->sag, gecici->anahtar);
    }
  }

  if (kok == NULL)
    return kok;

  // boyu guncelle ve dengeye bak silince sasmis olabilir
  kok->yukseklik = 1 + maks(boy(kok->sol), boy(kok->sag));

  int denge = denge_al(kok);
  
  // denge sastiysa dondurmeler baslasin
  if (denge > 1) {
    if (denge_al(kok->sol) >= 0)
      return saga_dondur(kok);
    else {
      kok->sol = sola_dondur(kok->sol);
      return saga_dondur(kok);
    }
  }

  if (denge < -1) {
    if (denge_al(kok->sag) <= 0)
      return sola_dondur(kok);
    else {
      kok->sag = saga_dondur(kok->sag);
      return sola_dondur(kok);
    }
  }

  return kok;
}

// kucukten buyuge sirali yazdiralim (inorder)
void sirali_yazdir(struct dugum *kok) {
  if (kok != NULL) {
    sirali_yazdir(kok->sol);
    printf("%d ", kok->anahtar);
    sirali_yazdir(kok->sag);
  }
}

int main() {
  struct dugum *agac = NULL;
  int anahtar, secim;

  printf("veri girin bakalim (bitirmek icin -1): ");
  scanf("%d", &anahtar);

  while (anahtar != -1) {
    agac = ekle(agac, anahtar);
    scanf("%d", &anahtar);
  }

  do {
    printf("\n1-ekle\n2-boy\n3-yazdir\n4-sil\n5-cik\nseciminiz: ");
    scanf("%d", &secim);
    switch (secim) {
      case 1:
        printf("sayi gir: ");
        scanf("%d", &anahtar);
        agac = ekle(agac, anahtar);
        sirali_yazdir(agac);
        break;
      case 2:
        if(agac) printf("boyu = %d", agac->yukseklik);
        else printf("agac bos!");
        break;
      case 3:
        sirali_yazdir(agac);
        break;
      case 4:
        printf("neyi siliyoruz: ");
        scanf("%d", &anahtar);
        agac = sil(agac, anahtar);
        sirali_yazdir(agac);
        break;
      case 5:
        exit(0);
      default:
        printf("hatali secim yaptin!");
        break;
    }
  } while (1);

  return 0;
}