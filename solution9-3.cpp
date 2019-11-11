#include <iostream>
#include <set>

using namespace std;

int main(){
    multiset<int> s;
    set<int> record;
    int n;
    cin >> n;
    while(n--){
        char cmd[4];
        int m;
        cin >> cmd >> m;
        string mycmd(cmd);
        if (mycmd == "add"){
            s.insert(m);
            record.insert(m);
            int count = s.count(m);
            cout << count << endl;
        } else if (mycmd == "del"){
            int count = s.count(m);
            cout << count << endl;
            s.erase(m);
        } else if (mycmd == "ask"){
            int r = record.count(m);
            if (r == 0) {
                cout << "0 0" << endl;
            } else {
                int count = s.count(m);
                cout << 1 <<" "<< count << endl;
            }
        }
    }
    return 0;
}

