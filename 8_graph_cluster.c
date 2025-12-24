/* Alper Görünme - 2210205349 */
#include <stdio.h>

int main() {
    // Adjacency Matrix (Komşuluk Matrisi)
    int graph[4][4] = {{0,1,0,0}, {1,0,0,0}, {0,0,0,1}, {0,0,1,0}};
    
    printf("Baglantili Dugumler (Cluster):\n");
    for(int i=0; i<4; i++) {
        for(int j=i; j<4; j++) {
            if(graph[i][j] == 1) printf("%d --- %d\n", i, j);
        }
    }
    return 0;
}
