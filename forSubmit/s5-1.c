#include <string>
class MyString: public string{
    public:
        MyString(const string &str) : string(str) {};
        MyString(const char *str) : string(str){};
        MyString(MyString &myStr) : string(myStr){};
        MyString() : string(){};
        MyString operator()(int s, int n)
        {
            return this->substr(s, n);
        }
};