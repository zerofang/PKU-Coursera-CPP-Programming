class A{
    private:
        int num;
    public:
        static int count;
        A(int n = 0){
            num = n;
            count++;
        }
        virtual ~A(){
            cout << "A::destructor" << endl;
        }

        void operator delete(void *A){
            count--;
        }
};

class B : public A{
    public:
    B(int n = 0) : A(n){};
    ~B(){
        cout << "B::destructor" << endl;
    }
};