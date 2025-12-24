#include <stdio.h>

// en fazla 20 dugum olsun dedik 
#define max 20

// matrisin icini baslangicta sifir yapiyoz ki eski veri kalmasin
void matris_sifirla(int mat[][max], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            mat[i][j] = 0;
}

// yonsuz ve agirliksiz graf kurma yeri
void yonsuz_graf_kur(int mat[][max], int *n) {
    int m, i, u, v;

    printf("kac tane dugum var (n): ");
    scanf("%d", n);  

    printf("kac tane kenar (cizgi) var (m): ");
    scanf("%d", &m);

    matris_sifirla(mat, *n);

    printf("kenarlari u v seklinde gir (0..%d arasi):\n", *n - 1);
    for (i = 0; i < m; i++) {
        printf("%d. kenar: ", i + 1);
        scanf("%d %d", &u, &v);

        // dugumler dogru mu bakmak lazim
        if (u < 0 || u >= *n || v < 0 || v >= *n) {
            printf("boyle bi dugum yok ki! gectim bunu.\n");
            continue;
        }

        // yonsuz oldugu icin iki tarafa da 1 koyuyoz ayna gibi oluyo
        mat[u][v] = 1;
        mat[v][u] = 1; 
    }
}

// yonlu ve agirlikli graf kurma
void yonlu_agirlikli_kur(int mat[][max], int *n) {
    int m, i, u, v, w;

    printf("dugum sayisini gir: ");
    scanf("%d", n);

    printf("kenar sayisini gir: ");
    scanf("%d", &m);

    matris_sifirla(mat, *n);

    printf("u v w (agirlik) seklinde gir (0..%d):\n", *n - 1);
    for (i = 0; i < m; i++) {
        printf("%d. kenar (u v agirlik): ", i + 1);
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= *n || v < 0 || v >= *n) {
            printf("hatali dugum girdin salla bunu.\n");
            continue;
        }

        // sadece u'dan v'ye yol var agirligi da w olsun
        mat[u][v] = w;
    }
}

// matrisi ekrana duzgunce basan fonksiyon
void matris_yazdir(int mat[][max], int n) {
    int i, j;

    printf("    ");
    for (i = 0; i < n; i++)
        printf("%3d", i);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%3d", i);
        for (j = 0; j < n; j++) {
            printf("%3d", mat[i][j]);
        }
        printf("\n");
    }
}

// yonsuz grafta bi dugumun kac baglantisi var (derece)
int derece_yonsuz(int mat[][max], int n, int v) {
    int i, sayac = 0;
    for (i = 0; i < n; i++) {
        if (mat[v][i] != 0) // baglanti varsa say
            sayac++;
    }
    return sayac;
}

// yonlu grafta gelen giden ok sayilari
void derece_yonlu(int mat[][max], int n, int v, int *gelen, int *giden) {
    int i;
    *gelen = 0;
    *giden = 0;

    // giden oklar: o satirdaki sifir olmayanlar herhalde
    for (i = 0; i < n; i++) {
        if (mat[v][i] != 0)
            (*giden)++;
    }

    // gelen oklar: o sutundaki sifir olmayanlar
    for (i = 0; i < n; i++) {
        if (mat[i][v] != 0)
            (*gelen)++;
    }
}

int main() {
    int matris1[max][max];
    int matris2[max][max];
    int n1 = 0, n2 = 0;
    int secim, v, gelen, giden;

    do {
        printf("\n--- graf menusu  ---\n");
        printf("1) yonsuz graf yap\n");
        printf("2) yonlu-agirlikli graf yap\n");
        printf("3) matrisi goster\n");
        printf("4) dereceye bak\n");
        printf("5) cikis\n");
        printf("secim ne: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                yonsuz_graf_kur(matris1, &n1);
                break;
            case 2:
                yonlu_agirlikli_kur(matris2, &n2);
                break;
            case 3: {
                int m_sec;
                printf("hangisi? (1: yonsuz, 2: yonlu): ");
                scanf("%d", &m_sec);
                if (m_sec == 1 && n1 > 0)
                    matris_yazdir(matris1, n1);
                else if (m_sec == 2 && n2 > 0)
                    matris_yazdir(matris2, n2);
                else
                    printf("grafi daha yapmadin ki!\n");
                break;
            }
            case 4: {
                int g_sec;
                printf("hangisi icin? (1: yonsuz, 2: yonlu): ");
                scanf("%d", &g_sec);

                if (g_sec == 1) {
                    if (n1 == 0) { printf("bos grafin derecesi mi olur?\n"); break; }
                    printf("dugum no gir (0..%d): ", n1 - 1);
                    scanf("%d", &v);
                    if (v < 0 || v >= n1) { printf("yanlis dugum!\n"); break; }
                    printf("%d dugumunun derecesi: %d\n", v, derece_yonsuz(matris1, n1, v));
                } else if (g_sec == 2) {
                    if (n2 == 0) { printf("once bi grafi kursaydin...\n"); break; }
                    printf("dugum no (0..%d): ", n2 - 1);
                    scanf("%d", &v);
                    if (v < 0 || v >= n2) { printf("boyle bi yer yok!\n"); break; }
                    derece_yonlu(matris2, n2, v, &gelen, &giden);
                    printf("%d icin gelen ok: %d, giden ok: %d\n", v, gelen, giden);
                }
                break;
            }
            case 5:
                printf("kapatiliyor...\n");
                break;
            default:
                printf("hatali bastin!\n");
        }
    } while (secim != 5);

    return 0;
}