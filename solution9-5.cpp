#include <iostream>
#include <map>

using namespace std;
typedef map<int, int> MEM;
int main(){
    MEM member;
    member.insert(MEM::value_type(1000000000, 1));
    int n;
    cin >> n;
    while (n--) {
        int atk, id;
        cin >> id >> atk;
        MEM::iterator it = member.upper_bound(atk);
        if (it == member.begin()) {
            cout << id <<" "<< it->second << endl;
        } else {
            MEM::iterator upIt = it;
            MEM::iterator lowIt = --it;
            if (upIt->first - atk < atk - lowIt->first) {
                cout << id << " " << upIt->second << endl;
            } else {
                cout << id << " " << lowIt->second << endl;
            }
        }
        member.insert(MEM::value_type(atk, id));
    }
    return 0;
}