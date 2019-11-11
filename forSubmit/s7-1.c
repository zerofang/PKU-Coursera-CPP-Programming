template<class T>
class CArray3D{
    template<class T1>
    class CArray2D{
        int i;
        int j;
        T1 **ptr;
        public:
        CArray2D<T1>() {

        }
        CArray2D<T1>(int i_, int j_) {
            i = i_;
            j = j_;
            if (i_*j_==0){
                ptr = NULL;
            }
            else{
                ptr = new int*[i];
                for (int n = 0; n < i; n++) {
                    ptr[n] = new int[j];
                }
            }
        }
        CArray2D<T1> & operator=(const CArray2D<T1> &a){
            if(a.ptr == ptr){
                return *this;
            }
            if(ptr != NULL){
                delete[] ptr;
            }
            ptr = a.ptr;
            return *this;
        }
        T1 * operator[](int i){
            return ptr[i];
        }
    };
    private:
    int k;
    CArray2D<T> *p;
    public:
    CArray3D<T>(int i_, int j_, int k_) {
        k = k_;
        p = new CArray2D<T>[i_];
        for (int m = 0; m < i_; m++) {
            p[m] = *new CArray2D<T>(j_, k_);
        }
    }

    CArray2D<T> operator[](int i_){
        return p[i_];
    }
};