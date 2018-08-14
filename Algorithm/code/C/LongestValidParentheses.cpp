/*https://leetcode.com/problems/longest-valid-parentheses/description/*/

#include<cstdlib>
#include<cstdio>
#define N 99999
// int longestValidParentheses(char* s) {
//     /* 异常判断 */
//     if(*s == '\0' || s == NULL)
//         return 0;
//
//     int frontIdx[N] = {0};
//     int endIdx[N] = {0};
//     int dp[N] = {0};        /* 以s[i]为结尾的字符串的最大有效串长度 */
//     int maxLen;
//     int maxIdx;
//     char *p;
//     int i;
//
//     /* init */
//     /* 只有一个字符的情况 */
//     if(*(s+1) == '\0')
//         return 0;
//     /* 只有两个字符并且第一个是')' */
//     else if(*(s+2) == '\0' && *s==')')
//         return 0;
//     /* 必须要()才算，)()是2不是3 */
//     else if(*s == ')'){
//         dp[0]=0;
//         maxLen=0;
//         maxIdx=0;
//     }
//     /* 正常情况 */
//     else{
//         dp[0] = 1;
//         maxLen = 1;
//         maxIdx = 0;
//     }
//     p = s+1;
//     i = 1;
//
//     /* 思路
//      *  当前字符两种情况
//      *  1. '('
//      *      if s[i-1]==')'
//      *          dp[i]=dp[i-1]+1
//      *          frontIdx[i]=frontIdx[i-1]
//      *          endIdx[i]=i
//      *      if s[i-1]=='('
//      *          dp[i]=1
//      *          frontIdx[i]=i
//      *          endIdx[i]=i
//      *  2.  ')'
//      *      跟上面一样
//      */
//
//     while(*p != '\0'){
//         if(*p != *(p-1)){
//             dp[i]=dp[i-1]+1;
//             frontIdx[i]=frontIdx[i-1];
//             endIdx[i]=i;
//         }
//         else{
//             dp[i]=1;
//             frontIdx[i]=i;
//             endIdx[i]=i;
//         }
//         if(maxLen < dp[i]){
//             maxLen=dp[i];
//             maxIdx=i;
//         }
//         p++;
//         i++;
//     }
//     return maxLen;
// }
int longestValidParentheses(char* s) {
    int dp[N] = {0};
    char *p = s+1;
    int j = 0;
    int maxLen = 0;

    if(s == NULL)
        return 0;

    /* dp[i]存储的是以s[i]结尾的字符串里的最长有效子字符串 */
    for (int i = 1; *p != '\0'; p++, i++) {
        if (*p == ')') {
            j = i - dp[i-1] - 1;
            if (j > 0 && *(s+j) == '(') {
                dp[i] = dp[i-1] + 2;
                if (j-1 >= 0)
                    dp[i] += dp[j-1];
            }
        }
        else {
            dp[i] = 0;
        }
        if (maxLen < dp[i])
            maxLen = dp[i];
    }

    return maxLen;
}


int main(){
    char *inputstr = (char *)malloc(sizeof(char)*N);
    scanf("%s", inputstr);
    printf("%d", longestValidParentheses(inputstr));
    scanf("%s", inputstr);
}
