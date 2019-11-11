template<class T>
class CMyistream_iterator{
    private:
        T a;
        istream & is;

    public:
        CMyistream_iterator(istream &input) : is(input){
            is >> a;
        }
        T operator*(){
            return a;
        }
        void operator++(int){
            is >> a;
        }
};