#include <stdlib.h>
#include <stdio.h>

// agac yapisi icin dugum tanimi
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// isimlendirmeyi de kucuk harf yaptim
typedef struct node btree;

// yeni bi dugum acma, agacin ilk dugumu 
btree *new_node(int veri) {
    btree *yeni = (btree*)malloc(sizeof(btree));
    yeni->data = veri;
    yeni->left = yeni->right = NULL; // buralar bos kalsin simdilik
    return yeni;
}

// agaca sirali eleman ekleme fonksiyonu
btree *insert(btree *root, int veri) {
    if(root != NULL) { // icerde veri varsa bakiyoz
        if(veri < root->data)
            root->left = insert(root->left, veri); // kucukse sola at
        else
            root->right = insert(root->right, veri); // buyukse saga at iste
    }
    else
        root = new_node(veri); // kok bossa yeni dugum yap

    return root;
}

// agaci ekrana basan fonksiyon - preorder galiba bu
int traverse(btree *root) {
    if(root != NULL) {
        printf("%d\t", root->data);
        traverse(root->left); // once sola gitmeyi unutma
        traverse(root->right);
    }
    else 
        return 0;
}

// sagdakileri sola soldakileri saga geciren fonksiyon
// aynalama deniyo buna
int mirror(btree *root) {
    if(root != NULL) {
        btree *gecici; // yer degistirmek icin lazim
        mirror(root->left);
        mirror(root->right);
        
        // burada swap yapiyoz sag sol degisiyo
        gecici = root->right;
        root->right = root->left;
        root->left = gecici;
    }
    else
        return 0;
}

// sag tarafin en kucugunu bulmaya calisan sey
btree* min_value_node(btree* node) {
    btree* suanki = node;
    // en sola kadar gitmek lazim en kucuk orda cunku
    while (suanki && suanki->left != NULL)
        suanki = suanki->left;
    return suanki;
}

// agactan eleman silme... burasi biraz karisik
btree* delete(btree* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data) // silincek olan nerde aricaz
        root->left = delete(root->left, data);
    else if (data > root->data)
        root->right = delete(root->right, data);
    else { 
        // silcek dugumu bulduk simdi 3 tane durum vardi
        
        // durum 1: yaprak dugum, yani bebegi yok
        if (root->left == NULL && root->right == NULL) {
            free(root); // sil gitsin direk
            return NULL;
        }
        // durum 2: tek cocugu var (sadece sagda veya solda)
        else if (root->left == NULL) { 
            btree* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            btree* temp = root->left;
            free(root);
            return temp;
        }
        // durum 3: iki tane cocugu varsa napcaz?
        else {
            // sagin en kucugunu bulup onunla yer degiscez heralde
            btree* temp = min_value_node(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

// ana fonksiyon, veri girisi burdan oluyo
int main() {
    btree *bst = NULL;
    int i = 0;
    
    // -1 yazana kadar dongu doncek
    while(i != -1) {
        printf("agaca eklemek icin sayi giriniz (bitirmek icin -1): ");
        scanf("%d", &i);

        if(i != -1)
            bst = insert(bst, i);
    }

    printf("agacin ilk hali:\n");
    traverse(bst);
    
    printf("\n\n5 sayisi siliniyor...");
    bst = delete(bst, 5);
    
    printf("\nsilindikten sonra agac:\n");
    traverse(bst);
    
    printf("\n\nagac aynalaniyor (sag sol takas)...\n");
    mirror(bst);
    traverse(bst); 
    
    return 0;
}