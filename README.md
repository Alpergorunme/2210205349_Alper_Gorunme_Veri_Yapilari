# 📚 CS1102: Veri Yapıları ve Algoritmalar Dersi Ödevleri

Bu depo, 2024-2025 Güz dönemi **CS1102: Data Structures and Algorithms** dersi kapsamında hazırlanan laboratuvar ve ödev çalışmalarını içermektedir.

---

## 👤 Öğrenci Bilgileri
* **Ad Soyad:** Alper Görünme
* **Öğrenci Numarası:** 2210205349
* **Ders:** CS1102 - Veri Yapıları 

---

## 🛠️ Ödev İçeriği ve Uygulamalar

Aşağıdaki listede hocamız tarafından istenen 10 temel veri yapısı ve algoritma uygulaması yer almaktadır:

### 1. Seyrek Matris (Sparse Matrix) Dönüşümü
* **Açıklama:** Bellek tasarrufu sağlamak amacıyla çoğu elemanı sıfır olan matrislerin sadece anlamlı verilerini tutan yapıya dönüştürülmesi.
* **Dosya:** `01_sparse_matrix.c`

### 2. Hanoi Kuleleri (Hanoi Towers)
* **Açıklama:** Özyinelemeli (recursive) mantık kullanılarak disklerin kurallara uygun şekilde taşınması algoritması.
* **Dosya:** `02_hanoi.c`

### 3. Shunting Yard Algoritması
* **Açıklama:** Infix ifadeleri (A+B) bilgisayarın daha kolay işleyebildiği Postfix (AB+) formatına çevirme işlemi.
* **Dosya:** `03_shunting_yard.c`

### 4. Max & Min Heap
* **Açıklama:** Yığın veri yapısında en büyük veya en küçük elemanın her zaman kökte bulunmasını sağlayan algoritma.
* **Dosya:** `04_heap_ops.c`

### 5. Çift Bağlı Liste (Double Linked List)
* **Açıklama:** İleri ve geri yönde hareket edebilen bağlı liste üzerinde ekleme, silme ve gezinme (traversal) işlemleri.
* **Dosya:** `05_double_linked_list.c`

### 6. Çembersel Bağlı Liste (Circular Linked List)
* **Açıklama:** Son düğümün ilk düğüme bağlı olduğu listede araya ekleme, silme ve gezinme işlemleri.
* **Dosya:** `06_circular_linked_list.c`

### 7. Dizilerde Temel İşlemler (Array Ops)
* **Açıklama:** Statik veya dinamik diziler üzerinde veri ekleme ve veri silme algoritmaları.
* **Dosya:** `07_array_operations.c`

### 8. Graf Kümeleme (Graph Cluster)
* **Açıklama:** Matris formunda temsil edilen bir graf yapısı üzerinden cluster (küme) tespiti ve çıkarımı.
* **Dosya:** `08_graph_clustering.c`

### 9. DFS & BFS Uygulaması
* **Açıklama:** Graflarda Derinlik Öncelikli Arama (DFS) ve Genişlik Öncelikli Arama (BFS) algoritmaları.
* **Dosya:** `09_dfs_bfs.c`

### 10. Diziden Ağaç Oluşturma (Tree Creation via Array)
* **Açıklama:** Bir dizi (array) içerisinde verilen verilerin hiyerarşik bir ağaç yapısına dönüştürülmesi.
* **Dosya:** `10_tree_from_array.c`

---

## 🚀 Çalıştırma Notları
Kodlar **C dili** ile yazılmıştır. Herhangi bir standart C derleyicisi (GCC, Clang vb.) ile derlenip çalıştırılabilir.

```bash
# Örnek derleme (Linux/Terminal):
gcc 01_sparse_matrix.c -o sparse_matrix
./sparse_matrix
