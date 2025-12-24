# 2210205349_Alper_Gorunme_Veri_Yapilari
# 🚀 Veri Yapıları Dersi Çalışmalarım

Bu depo, **Veri Yapıları** dersi kapsamında laboratuvar uygulamalarında ve ödev projelerinde yazdığım kodları içermektedir. Projeler genel olarak **C dili** kullanılarak temel veri yapılarının ve algoritmaların sıfırdan uygulanmasını konu alır.

---

## 🛠️ Neler Var?

### 1. Öncelikli Kuyruklar (Priority Queues)
Öncelikli kuyruk mantığını iki farklı veri yapısı kullanarak uyguladım:
* **Bağlı Liste (Linked List):** Temel ekleme ve öncelik sıralama mantığı.
* **Heap (Yığın):** Daha yüksek performanslı ekleme ve çekme operasyonları.

**Dosyalar:**
- `01-Priority-Queues/priority_queue_linked_list.c`
- `01-Priority-Queues/priority_queue_heap.c`

---

### 2. İkili Arama Ağaçları (BST)
Standart İkili Arama Ağacı operasyonlarını içerir:
* **Temel İşlemler:** Düğüm ekleme ve silme.
* **Ayna Görüntüsü:** Ağacın simetriğini alan `mirror` fonksiyonu.
* **Gezinme (Traversal):** Üç temel yöntem de kodlanmıştır:
    * `Preorder`
    * `Inorder`
    * `Postorder`

---

### 3. AVL Ağaçları
Kendi kendini dengeleyen (**self-balancing**) AVL ağaç yapısı üzerine çalışmalar:
* **Denge Faktörü:** Dengeyi korumak için gerekli hesaplamalar.
* **Rotasyonlar:** Tekli ve çiftli rotasyon (LL, RR, LR, RL) mantığı.

**Dosyalar:**
- `avlnode.c` (Ekleme işlemleri)
- `deletion_AVL.c` (Silme ve dengeyi koruma)

---

### 4. Graf Yapıları
Graf yapısını **Komşuluk Matrisi (Adjacency Matrix)** mantığıyla kurguladım:
* **Esneklik:** Hem yönlü hem de yönsüz grafları destekler.
* **Analiz:** Düğüm derecelerini (`degree`) hesaplayan fonksiyonlar.

**Dosya:**
- `graf.c` (Matris oluşturma ve derece hesaplama)

---

## 💻 Kullanılan Teknolojiler
* **Dil:** C
* **Konseptler:** Bellek Yönetimi (malloc/free), İşaretçiler (Pointers), Özyineleme (Recursion)
