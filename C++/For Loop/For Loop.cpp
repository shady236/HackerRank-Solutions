#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    // Complete the code.
    
    string nums[10] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };
    
    int a, b;
    cin >> a >> b;
    
    for(int i = a; i <= b; i++)
    {
        if(i <= 9)
            cout << nums[i];
        else if(i & 1)
            cout << "odd";
        else  
            cout << "even";
        
        cout << endl;
    }
    
    return 0;
}
