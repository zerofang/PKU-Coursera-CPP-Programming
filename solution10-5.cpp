#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct CMy_add{
        int& sum;
        CMy_add(int& s) : sum(s){};
        void operator()(int n){
            sum += (n&7);
        }
};
int main(int argc, char* argv[]) {
        int v, my_sum=0;
        vector<int> vec;
        cin>>v;
        while ( v ) {
                vec.push_back(v);
                cin>>v;
        }
        for_each(vec.begin(), vec.end(), CMy_add(my_sum));
        cout<<my_sum<<endl;
        return 0;
}