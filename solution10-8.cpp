#include <iostream>
#include <bitset>

using namespace std;

int main(){
    int t, n, i, j;
    cin >> t;
    while (--t >= 0) {
        cin >> n >> i >> j;
        bitset<32> b(n);
        for (int l = 0; l < i; l++) {
            b.reset(l);
        }
        for (int l = i + 1; l < j; l++) {
            b.set(l);
        }
        b.flip(j);
        for (int l = j + 1; l < 32; l++){
            b.reset(l);
        }
        cout << hex << b.to_ullong() << endl;
    }
    return 0;
}