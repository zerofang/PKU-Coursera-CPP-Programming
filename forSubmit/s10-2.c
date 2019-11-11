    int& value(){
        return num;
    }
    void operator+(Number b){
        num += b.num;
    }