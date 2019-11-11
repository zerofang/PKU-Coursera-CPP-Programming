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