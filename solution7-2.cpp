#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    double n;
    cin >> n;
    cout << fixed <<setprecision(5)<< n << endl;
    cout << scientific <<setprecision(7)<< n << endl;
    return 0;
}