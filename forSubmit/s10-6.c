class MyString : public string{
    public:
    MyString(const string &str) : string(str){};
    MyString(const char *str) : string(str){};
    MyString(const MyString &str) : string(str){};
    MyString() : string(){};
    MyString operator()(int a, int b){
        return this->substr(a,b);
    }
};