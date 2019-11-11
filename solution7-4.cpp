#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<string> strs;
queue<string> args;

string numToString(int num) {
    char s[500];
    sprintf(s, "%d", num);
    return string(s);
}

int stringToNum(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num = num * 10 + s[i] - '0';
    }
    return num;
}

void clearQueue(queue<string> q) {
    queue<string> empty;
    swap(empty, q);
}

string myCopy(int n, int x, int l) {
    string str = strs.at(n - 1);
    return str.substr(x, l);
}

string myAdd(string s1, string s2) {
    if (s1.length() > 5 || s2.length() > 5) {
        return s1+s2;
    }
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] < '0' || s1[i] > '9') {
            return s1+s2;
        }
    }
    for (int i = 0; i < s2.length(); i++) {
        if (s2[i] < '0' || s2[i] > '9') {
            return s1+s2;
        }
    }
    return numToString(stringToNum(s1.c_str()) + stringToNum(s2.c_str()));
}

int myFind(string s, int n) {
    string str = strs.at(n - 1);
    int l = str.find(s);
    return l >= str.length() ? str.length() : l;
}

int myRfind(string s, int n) {
    string str = strs.at(n - 1);
    int l = str.rfind(s);
    return l >= str.length() ? str.length() : l;
}

void myInsert(string s, int n, int x) {
    strs.at(n - 1).insert(x, s);
}

void myReset(string s, int n) {
    strs.at(n - 1) = s;
}

void myPrint(int n) {
    cout << strs.at(n - 1) << endl;
}

void myPrintAll() {
    for (int i = 0; i < strs.size(); i++) {
        cout << strs.at(i) << endl;
    }
}

string operateRec() {
    string str = args.front();
    args.pop();
    if (str == "copy") {
        int n = stringToNum(operateRec().c_str());
        int x = stringToNum(operateRec().c_str());
        int l = stringToNum(operateRec().c_str());
        return myCopy(n, x, l);
    } else if (str == "add") {
        string s1 = operateRec();
        string s2 = operateRec();
        return myAdd(s1, s2);
    } else if (str == "find") {
        string s = operateRec();
        int n = stringToNum(operateRec().c_str());
        return numToString(myFind(s, n));
    } else if (str == "rfind") {
        string s = operateRec();
        int n = stringToNum(operateRec().c_str());
        return numToString(myRfind(s, n));
    } else {
        return str;
    }
}

bool processCMD() {
    string str = args.front();
    args.pop();
    if (str == "insert") {
        string s = operateRec();
        int n = stringToNum(operateRec().c_str());
        int x = stringToNum(operateRec().c_str());
        myInsert(s, n, x);
    } else if (str == "reset") {
        string s = operateRec();
        int n = stringToNum(operateRec().c_str());
        myReset(s, n);
    } else if (str == "print") {
        int n = stringToNum(operateRec().c_str());
        myPrint(n);
    } else if (str == "printall") {
        myPrintAll();
    } else if (str == "over") {
        return false;
    }
    return true;
}

void parseCMD(char* s) {
    clearQueue(args);
    string temp;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] != ' '){
            temp.push_back(s[i]);
        }
        else {
            args.push(temp);
            temp.clear();
        }
    }
    args.push(temp);
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        strs.push_back(s);
    }
    cin.get();
    char str[501];
    bool flag;
    cin.getline(str, 500, '\n');
    parseCMD(str);
    flag = processCMD();
    while (flag) {
        cin.getline(str, 500);
        parseCMD(str);
        flag = processCMD();
    }
    return 0;
}