#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int n;
    cin >> n;
    
    vector<int> arr;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    
    int idx;
    cin >> idx;
    idx--;
    arr.erase(arr.begin() + idx);
    
    int strt, end;
    cin >> strt >> end;
    strt--;
    end--;
    arr.erase(arr.begin() + strt, arr.begin() + end);
    
    
    cout << arr.size() << endl;
    for(int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    
    
    return 0;
}
