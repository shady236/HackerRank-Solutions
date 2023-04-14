#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct DisjointSet {
    int* parent;
    int* rank;
    int* size;
} DisjointSet;


void create(DisjointSet* set, int n) {
    set->parent = malloc(n * sizeof(int));
    set->rank   = malloc(n * sizeof(int));
    set->size   = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        set->parent[i] = i;
        set->rank[i]   = 0;
        set->size[i]   = 1;
    }
}


int find(DisjointSet* set, int i) {
    if (set->parent[i] != i) {
        set->parent[i] = find(set, set->parent[i]);
    }
    return set->parent[i];
}


void merge(DisjointSet* set, int i, int j) {
    int p1 = find(set, i);
    int p2 = find(set, j);
    
    if (p1 == p2) {
        return;
    }
    
    if (set->rank[p1] < set->rank[p2]) {
        set->parent[p1] = p2;
        set->size[p2] += set->size[p1];
    }
    else {
        set->parent[p2] = p1;
        set->size[p1] += set->size[p2];
        
        if (set->rank[p1] == set->rank[p2]) {
            set->rank[p1]++;
        }
    }
}


int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    int n;
    scanf("%d", &n);
    
    DisjointSet blackSubtrees;
    create(&blackSubtrees, n);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        u--;
        v--;
        
        char color;
        do {
            scanf("%c", &color);
        } while (color != 'b' && color != 'r');
        
        if (color == 'b') {
            merge(&blackSubtrees, u, v);
        }
    }
    
    int sizes[100000];
    int sizesCnt = 0;
    for (int i = 0; i < n; i++) {
        if (blackSubtrees.parent[i] == i) {
            sizes[sizesCnt++] = blackSubtrees.size[i];
        }
    }
    
    long totSizesSqr = 0;
    for (int i = 0; i < sizesCnt; i++) {
        totSizesSqr += sizes[i] * (long) sizes[i];
    }
     
    long cnt = 0;
    
    for (int i = 0; i < sizesCnt; i++) {
        long sizei = sizes[i];
        long comb = sizei * (
            (n - sizei) * (n - sizei) -
            (totSizesSqr - sizei * sizei)
        );
        
        cnt += comb;
    }
    
    cnt /= 6;
    cnt %= 1000000007;
    
    printf("%d", cnt);
    
    return 0;
}
