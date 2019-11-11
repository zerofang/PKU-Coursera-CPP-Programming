#include <string.h>
#include <iostream>
using namespace std;

class Stu {
    private:
        char name[50];
        int age;
        char id[30];
        int s1;
        int s2;
        int s3;
        int s4;
        int avg;
    public:

    void setName(const char* a) {
        strcpy(name, a);
    }

    void setId(const char* c) {
        strcpy(id, c);
    }

    void setAge(int b) {
        age = b;
    }

    void setGrades(int d, int e, int f, int g) {
        s1 = d;
        s2 = e;
        s3 = f;
        s4 = g;
    }

    int computeAvg() {
        avg = (s1 + s2 + s3 + s4) / 4;
        return avg;
    }

    void printInfo() {
        cout << name << "," << age << "," << id << "," << avg;
    }
};

int main()
{
    char a[50], c[30];
    int b, d, e, f, g;
    char mark;
    cin.getline(a, 50, ',');
    cin >> b >> mark;
    cin.getline(c, 30, ',');
    cin >> d >> mark >> e >> mark >> f >> mark >> g;
    Stu stu;
    stu.setName(a);
    stu.setAge(b);
    stu.setId(c);
    stu.setGrades(d, e, f, g);
    stu.computeAvg();
    stu.printInfo();
    return 0;
}