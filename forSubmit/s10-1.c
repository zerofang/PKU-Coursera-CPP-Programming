    Number& operator*(const Number n) {
        return *(new Number(num*n.num));
    }
    operator int(){
        return num;
    }