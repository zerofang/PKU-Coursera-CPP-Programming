bool operator < (const A& a1, const A& a2)
{
    return a1.get_size() < a2.get_size();
}

template<class Iterator, class Function>
void Show(Iterator myBegin, Iterator myEnd, Function print){
    for (Iterator i = myBegin; i != myEnd; i++) {
        print(*i);
    }
}

class Print{
    public:
    void operator()(const A & a){
        cout << a.get_name() << " ";
    }
};

template<class A> 
struct MyLarge{
    inline bool operator()(const A& a, const A& b){
        return a.get_name() < b.get_name();
    }
};