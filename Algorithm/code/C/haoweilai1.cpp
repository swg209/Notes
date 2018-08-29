#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int main() {
        string str;
        cin >> str;
        int i, len = str.length(), m, number, ans = 0, c1, c2;
        for (i = 0, m = 0, c1 = 0, c2 = 0; i < len; i++) {
                number = str[i] - '0';
                //遇到3的情况直接加1
                if (number % 3 == 0) {
                        ans++;
                        m = 0, c1 = 0, c2 = 0;
                        continue;
                }
                m += number;
                if (number % 3 == 1)
                        c1++;
                else
                        c2++;
                //判断能不能有一个组合
                if ((m > 0 && m % 3 == 0) || (c1 > 0 && c2 > 0)) {
                        ans++;
                        m = 0, c1 = 0, c2 = 0;
                }
        }
        cout << ans << endl;
}
