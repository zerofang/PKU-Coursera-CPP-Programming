#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

bool isPrime(int n){
    for (int i = 2; i <= sqrt(float(n)); i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

int getFactor(int n){
    int count = 0;
    for (int i = 2; i <= sqrt(float(n)); i++){
        if (n % i == 0){
            int k = n / i;
            if (k != i && isPrime(k))
            {
                count++;
            }
            if(isPrime(i)) {
                count++;
            }
        }
    }
    return count;
}

class myGreater{
    public:
    bool operator()(const int &a, const int &b){
        int ac = getFactor(a);
        int bc = getFactor(b);
        if (ac == bc) {
            return a < b ? true : false;
        } else {
            return ac < bc ? true : false;
        }
    }
};

class myLess{
    public:
    bool operator()(const int &a, const int &b){
        int ac = getFactor(a);
        int bc = getFactor(b);
        if (ac == bc) {
            return a > b ? true : false;
        } else {
            return ac > bc ? true : false;
        }
    }
};

int main(){
    priority_queue <int,vector<int>, myGreater> hpq;
    priority_queue <int,vector<int>, myLess> lpq;
    int n = 0;
    cin >> n;
    while(n--){
        for (int i = 0; i < 10; i++){
            int m;
            cin >> m;
            hpq.push(m);
            lpq.push(m);
        }
        int a = hpq.top();
        int b = lpq.top();
        hpq.pop();
        lpq.pop();
        cout << a << " " << b << endl;
    }
    return 0;
}