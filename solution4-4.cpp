#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
using namespace std;

int cmp(string a, string b) {
    if (a==b) {
        return 0;
    }
    if (a.length() > b.length()) {
        return 1;
    } 
    else if (a.length() < b.length()) {
        return -1;
    }
    else {
        return a > b ? 1 : -1;
    }
}

class BigInt{
    string value;
    public:
    BigInt(const string i = "0") {
        value = i;
    }
    BigInt operator+(const BigInt &n) {
        int mlen = value.length();
        int nlen = n.value.length();
        int len = mlen > nlen ? mlen : nlen;
        char ans[len+1];
        ans[len] = '\0';
        int c=0;
        while (mlen>0 || nlen>0) {
            int temp;
            if (nlen <= 0){
                temp = (value[mlen - 1] - '0') + c;
            }
            else if (mlen <= 0) {
                temp = (n.value[nlen - 1] - '0') + c;
            }
            else {
                temp = (value[mlen - 1] - '0') + (n.value[nlen - 1] - '0') + c;
            }
            ans[len-1] = temp % 10 + '0';
            c = temp / 10;
            len--;
            mlen--;
            nlen--;
        }
        if (c > 0) {
            return BigInt(to_string(c) + ans);
        }
        return BigInt(ans);
    }
    BigInt operator-(const BigInt &n) {
        if (value == n.value){
            return BigInt("0");
        }
        string bigger;
        string smaller;
        if (cmp(value, n.value) > 0){
            bigger = value;
            smaller = n.value;
        } else {
            bigger = n.value;
            smaller = value;
        }
        int mlen = bigger.length();
        int nlen = smaller.length();
        int len = mlen+1;
        char ans[len];
        ans[len] = '\0';
        int c=0;
        while (mlen > 0 || nlen > 0) {
            int temp;
            if (nlen <= 0){
                temp = (bigger[mlen - 1] - '0') + c;
            } else {
                temp = (bigger[mlen - 1] - '0') - (smaller[nlen - 1] - '0') + c;
            }
            if (temp > 0){
                ans[len - 1] = temp + '0';
                c = 0;
            } else if(temp < 0){
                ans[len - 1] = temp + 10 + '0';
                c = -1;
            } else {
                if (len - 1 == 0 || (mlen <= 1 && nlen <= 1)){
                    if (cmp(value, n.value) < 0) {
                        ans[len - 1] = '-';
                    }
                    return BigInt(ans+len);
                }
                else {
                    ans[len - 1] = temp + '0';
                    c = 0;
                }
            }
            len--;
            mlen--;
            nlen--;
        }
        if (cmp(value, n.value) > 0) {
            return BigInt(ans+len);
        }
        return BigInt("-" + string(ans+len));
    }
    BigInt operator*(const BigInt &n) {
        int mlen = value.length();
        int nlen = n.value.length();
        BigInt ans;
        for (int i = mlen-1; i >= 0; i--) {
            int len = nlen;
            char t[len+1];
            t[len] = '\0';
            int c = 0;
            for (int j = nlen - 1; j >= 0; j--) {
                int temp;
                temp = (value[i] - '0') * (n.value[j] - '0') + c;
                t[len-1] = temp % 10 + '0';
                c = temp / 10;
                len--;
            }
            if (i == mlen - 1) {
                ans = BigInt(t + len);
                if (c > 0) {
                    ans.value = to_string(c) + ans.value;
                }
            }
            else {
                BigInt tt(t);
                if (c > 0) {
                    tt.value = to_string(c) + tt.value;
                }
                tt.value = tt.value + string(mlen - 1 - i, '0');
                ans = ans + tt;
            }
        }
        return ans;
    }
    BigInt operator/(const BigInt &n){
        if (cmp(value, n.value) < 0) {
            return BigInt("0");
        }
        if (value == n.value) {
            return BigInt("1");
        }
        if (n.value == "1"){
            return *this;
        }
        int mlen = value.length();
        int nlen = n.value.length();
        int len = mlen - nlen;
        BigInt m(value);
        BigInt ans;
        while (cmp(m.value, n.value) > 0) {
            int tempLen = m.value.length() - n.value.length();
            len = len < tempLen ? len : tempLen;
            string temp(len, '0');
            BigInt tempInt;
            BigInt tempInt2;
            int i;
            for (i = 1; i <= 10; i++) {
                tempInt.value = to_string(i) + temp;
                tempInt2 = tempInt * n;
                if (cmp(tempInt2.value, m.value) > 0) {
                    break;
                }
            }
            if (i == 1){
                len--;
                continue;
            }
            tempInt.value = to_string(i-1) + temp;
            tempInt2 = tempInt * n;
            m = m - tempInt2;
            ans = ans + tempInt;
            len--;
        }
        return ans;
    }
    string getValue() {
        return value;
    }
};
int main() {
    string a, b;
    char o;
    cin >> a >> o >> b;
    BigInt A(a);
    BigInt B(b);
    BigInt ans;
    if (o == '+') {
        ans = A + B;
    } else if (o == '-') {
        ans = A - B;
    }
    else if (o == '*') {
        ans = A * B;
    } else {
        ans = A / B;
    }
    cout << ans.getValue() << endl;
    return 0;
}