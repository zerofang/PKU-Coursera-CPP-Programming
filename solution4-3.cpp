#include <iostream>
#include <cstring>
using namespace std;
class Array2{
    int x;
    int y;
    int **ptr;
    public:
    Array2(const int row = 0, const int col = 0){
        x = row;
        y = col;
        if (x*y==0){
            ptr = NULL;
        }
        else{
            ptr = new int*[x];
            for (int i = 0; i < x; i++) {
                ptr[i] = new int[y];
            }
        }
    }
    Array2 & operator=(const Array2 &a){
        if(a.ptr == ptr){
            return *this;
        }
        if(ptr != NULL){
            delete[] ptr;
        }
        ptr = a.ptr;
        return *this;
    }
    int * operator[](int i){
        return ptr[i];
    }
    int operator()(const int i, const int j){
        return ptr[i][j];
    }
};


// 在此处补充你的代码
int main() {
    Array2 a(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b; b = a;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}