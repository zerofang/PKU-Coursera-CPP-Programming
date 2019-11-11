class A{
    protected:
        int age;
        char type;
    public:
        A(int a = 0){
            age = a;
            type = 'A';
        }
        int getAge() const{
            return age;
        }
        char getType() const{
            return type;
        }
};
class B : public A{
    public:
    B(int b = 0){
        age = b;
        type = 'B';
    }
};
class Comp{
    public:
    bool operator()(const A* a, const A* b){
        return a->getAge() < b->getAge();
    }
};

void Print(const A* a){
    cout << a->getType() << " " << a->getAge() << endl;
}