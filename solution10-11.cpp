#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
using namespace std;
// 在此处补充你的代码
struct Student
{
    string name;
    int score;
};
template <class T>
void Print(T first,T last) {
    for(;first!= last; ++ first)
            cout << * first << ",";
    cout << endl;
}
template <class T>
struct myGreater{
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};
template <class T1, class T2>
ostream & operator<<(ostream & o, pair<T1, T2> const & p){
    o << "(" << p.first << "," << p.second << ")";
    return o;
}
template<class T1, class T2, class Pref = myGreater<T1> >
class MyMultimap : public multimap<T1, T2>{
    typedef multimap<T1, T2, Pref> MP;
    private:
        MP mp;

    public:
    MyMultimap & insert(pair<T1, T2> const & p){
        mp.insert(p);
        return *this;
    }
    void Set(T1 t1, T2 t2){
        int n = mp.erase(t1);
        for (int i = 0; i < n; i++){
            mp.insert(make_pair(t1, t2));
        }
    }
    void clear(){
        mp.clear();
    }
    typename MP::iterator find(T1 t1) {
        return mp.find(t1);
    }
    typename MP::iterator begin() {
        return mp.begin();
    }
    typename MP::iterator end() {
        return mp.end();
    }
};
int main()
{

        Student s[] = { {"Tom",80},{"Jack",70},
                                        {"Jone",90},{"Tom",70},{"Alice",100} };
        MyMultimap<string,int> mp;
        for(int i = 0; i<5; ++ i)
                mp.insert(make_pair(s[i].name,s[i].score));
        Print(mp.begin(),mp.end()); //按姓名从大到小输出

        mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
        Print(mp.begin(),mp.end());


        MyMultimap<int,string,less<int> > mp2;
        for(int i = 0; i<5; ++ i)
                mp2.insert(make_pair(s[i].score,s[i].name));

        Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
        mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
        Print(mp2.begin(),mp2.end());
        cout << "******" << endl;

        mp.clear();
        
        string name;
        string cmd;
        int score;
        while(cin >> cmd ) {
                if( cmd == "A") {
                        cin >> name >> score;
                        if(mp.find(name) != mp.end() ) {
                                cout << "erroe" << endl;
                        }
                        mp.insert(make_pair(name,score));
                }
                else if(cmd == "Q") {
                        cin >> name;
                        MyMultimap<string,int>::iterator p = mp.find(name);
                        if( p!= mp.end()) {
                                cout << p->second << endl;
                        }
                        else {
                                cout << "Not Found" << endl;
                        }
                }
        }
        return 0;
}