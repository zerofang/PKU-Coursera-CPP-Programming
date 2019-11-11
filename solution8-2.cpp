#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

list<int> l[10001];

void myAdd(int id, int num) {
    l[id].push_back(num);
}

void myMerge (int id1, int id2) {
    l[id1].merge(l[id2]);
}

void myUnique(int id) {
    l[id].sort();
    l[id].unique();
}

void myOut(int id) {
    l[id].sort();
    ostream_iterator<int> o(cout, " ");
    copy(l[id].begin(), l[id].end(), o);
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        char str[10];
        cin >> str;
        string s(str);
        if (s == "new"){
            int id;
            cin >> id;
        } else if (s == "add") {
            int id, num;
            cin >> id >> num;
            myAdd(id, num);
        } else if (s == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            myMerge(id1, id2);
        } else if (s == "unique") {
            int id;
            cin >> id;
            myUnique(id);
        } else if (s == "out") {
            int id;
            cin >> id;
            myOut(id);
        }
    }
    return 0;
}

