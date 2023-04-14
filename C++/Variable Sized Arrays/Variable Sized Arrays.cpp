#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int n, q;
    cin >> n >> q;
    
    vector<int> arrays[n];
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            arrays[i].push_back(x);
        }
    }
    
    while (q--) {
        int i, j;
        cin >> i >> j;
        cout << arrays[i].at(j) << endl;
    }
    
    
    return 0;
}
