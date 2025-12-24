# 2210205349_Alper_Gorunme_Veri_Yapilari
Veri Yapıları Dersi Çalışmalarım
Bu depoda, Veri Yapıları dersi boyunca laboratuvarlarda yazdığım kodları ve ödev projelerimi topluyorum. Genellikle C dili kullanarak temel veri yapılarını ve algoritmaları uygulamaya çalıştım.

Neler Var?
1. Öncelikli Kuyruklar (Priority Queues)
Öncelikli kuyruk mantığını iki farklı şekilde uyguladım. Birinde bağlı liste (linked list) yapısını kullandım, diğerinde ise daha performanslı olan Heap (yığın) yapısıyla çalıştım.

01-Priority-Queues/priority_queue_linked_list.c
01-Priority-Queues/priority_queue_heap.c
2. İkili Arama Ağaçları (BST)
Burada standart İkili Arama Ağacı operasyonları var. Düğümlerin eklenmesi, silinmesi ve ağacın simetriğini alan "mirror" fonksiyonu gibi kısımları yazdım. Ayrıca ağacı gezmek için kullanılan üç temel yöntem (Preorder, Inorder, Postorder) de kodlarda mevcut.

3. AVL Ağaçları
Ağacın kendi kendini dengelemesini (self-balancing) sağlayan AVL yapısı üzerine çalıştım. Denge faktörünü korumak için gereken tekli ve çiftli rotasyon (sol-sol, sağ-sağ vb.) mantığını bu dosyalarda görebilirsiniz.

avlnode.c (Ekleme işlemleri)
deletion_AVL.c (Silme ve dengeyi koruma)
4. Graf Yapıları
Graf yapısını komşuluk matrisi (adjacency matrix) mantığıyla kurdum. Kodlar hem yönlü hem de yönsüz grafları destekliyor; ayrıca düğüm derecelerini (degree) hesaplayan fonksiyonları da ekledim.

graf.c dosyası üzerinden matris oluşturma ve derece hesaplama yapılabilir.
