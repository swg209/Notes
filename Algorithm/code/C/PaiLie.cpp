/*输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

string SwapTravel(string curstr) {
    if (curstr.size() > 1) {
        cout << curstr[0] << SwapTravel(curstr.substr(1));
    }
    else {
        return curstr;
    }
}

int main() {
    string str = "abc";

}
