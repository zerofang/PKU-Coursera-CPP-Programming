class Array2{
    int x;
    int y;
    int **ptr;
    public:
    Array2(const int row = 0, const int col = 0){
        x = row;
        y = col;
        if (x*y==0){
            ptr = NULL;
        }
        else{
            ptr = new int*[x];
            for (int i = 0; i < x; i++) {
                ptr[i] = new int[y];
            }
        }
    }
    Array2 & operator=(const Array2 &a){
        if(a.ptr == ptr){
            return *this;
        }
        if(ptr != NULL){
            delete[] ptr;
        }
        ptr = a.ptr;
        return *this;
    }
    int * operator[](int i){
        return ptr[i];
    }
    int operator()(const int i, const int j){
        return ptr[i][j];
    }
};