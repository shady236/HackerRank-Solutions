#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct DisjointSet {
    int* parent;
    int* rank;
    int* size;
} DisjointSet;


void createDisjointSet(DisjointSet* set, int n) {
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
    
    if (set->rank[p1] > set->rank[p2]) {
        set->parent[p2] = p1;
        set->size[p1] += set->size[p2];
    }
    else {
        set->parent[p1] = p2;
        set->size[p2] += set->size[p1];
        
        if (set->rank[p1] == set->rank[p2]) {
            set->rank[p2]++;
        }
    }
}


int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    int n;
    scanf("%d", &n);
    
    DisjointSet set;
    createDisjointSet(&set, n);
    
    int q;
    scanf("%d", &q);
    
    int i, j;
    while (q--) {
        char op;
        do {
            scanf("%c", &op);
        } while (op != 'M' && op != 'Q');
        
        switch (op) {
            case 'M':
                scanf("%d %d", &i, &j);
                merge(&set, i, j);
            break;
            
            case 'Q':
                scanf("%d", &i);
                printf("%d\n", set.size[find(&set, i)]);
            break;
        }
    }
    
    return 0;
}
