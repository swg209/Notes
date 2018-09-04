#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/*
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
 */

/*
   给定 x, k ，求满足 x + y = x | y 的第 k 小的正整数 y 。 | 是二进制的或(or)运算，例如 3 | 5 = 7。比如当 x=5，k=1时返回 2，因为5+1=6 不等于 5|1=5，而 5+2=7 等于 5 | 2 = 7。


int main(){
    long long x, y, k;
    cin >> x >> k;
    long long xbit = 1;
    long long ans = 0;
    while (k) {
        if ((x & xbit) == 0) {
            ans += xbit * (k & 1);
            k >>= 1;
        }
        xbit <<= 1;
    }
    printf("%d\n", ans);

    char* tmp;
    scanf("%c\n", &tmp);
}
 */

 /*
 最大上升子序列和
 题目描述：
一个数的序列bi，当b1 < b2 < ... < bS的时候，我们称这个序列是上升的。对于给定的一个序列(a1, a2, ...,aN)，我们可以得到一些上升的子序列(ai1, ai2, ..., aiK)，这里1 <= i1 < i2 < ... < iK <= N。比如，对于序列(1, 7, 3, 5, 9, 4, 8)，有它的一些上升子序列，如(1, 7), (3, 4, 8)等等。这些子序列中序列和最大为18，为子序列(1, 3, 5, 9)的和.

你的任务，就是对于给定的序列，求出最大上升子序列和。注意，最长的上升子序列的和不一定是最大的，比如序列(100, 1, 2, 3)的最大上升子序列和为100，而最长上升子序列为(1, 2, 3)。

输入：
输入包含多组测试数据。
每组测试数据由两行组成。第一行是序列的长度N (1 <= N <= 1000)。第二行给出序列中的N个整数，这些整数的取值范围都在0到10000（可能重复）。

输出：
对于每组测试数据，输出其最大上升子序列和。

样例输入：
7
1 7 3 5 9 4 8
样例输出：
18

int main(){
    const int LEN = 8;
    // int arr[LEN] = {1, 7, 3, 5, 9, 4, 8};
    int arr[LEN] = {5,1,3,4,9,7,6,8};
    int dp[LEN] = {0};
    int max = 0;
    dp[0] = arr[0];
    for(int i = 1; i < LEN; i++){
        if (arr[i] >= arr[i-1]) {
            dp[i] = dp[i-1] + arr[i];
            printf("%d\n", dp[i]);
        }
        else {
            int curmax = 0;
            for (int j = i-1; j >= 0 ; j--) {
                if (arr[j] <= arr[i]) {
                    if (dp[j] > curmax)
                        curmax = dp[j];
                }
            }

            dp[i] = arr[i] + curmax;
            printf("%d\n", dp[i]);
        }
        if (max < dp[i])
            max = dp[i];
    }
    printf("%d\n", max);

    char* tmp;
    scanf("%c\n", &tmp);
}
*/

/*
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
{0, 1, 1, 1, 0, 1, 1, 1, 1, 0}

*/
int bfs (int *arr, )
int main () {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bool b_arr[10] = {0, 1, 1, 1, 0, 1, 1, 1, 1, 0};
    
}
