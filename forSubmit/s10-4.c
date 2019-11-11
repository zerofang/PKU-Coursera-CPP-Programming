class CType {
    int num;
    public:
    void setvalue(int n){
        num = n;
    }
    int operator++(int){
        int temp = num;
        num = num * num;
        return temp;
    }

    friend ostream& operator << (ostream& o, CType& c){
        o << c.num;
        return o;
    }
};