/*
5. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
*/

/*
思考：
方法一，加字符
方法二，先找出所有的回文种子，再计算回文种子的长度
*/
#include<cstdio>
#include<cstdlib>
#define N 1000

char* longestPalindrome1(char* s) {
    char* p = s;
    char prestr[N];
    int maxLen;
    int endIdx;
    int frontIdx;

    /* 给字符串加字符 */
    for(int i = 0; *p != '\0'; i+=2, p++){
        prestr[i] = *p;
        prestr[i+1] = '#';
    }

    /* 遍历字符串prestr，求以prestr[i]为中心的字符串的最大回文串长度 */
    p = prestr;
    for(int i = 0; *p != '\0'; i++, p++){
        /* init */
        int front = i-1;
        int end = i+1;
        int count;
        if(prestr[i] == '#')
            count = 0;
        else
            count = 1;

        while(front >= 0 && end < N*2 && prestr[front] == prestr[end]){
            if(prestr[front] != '#')
                count += 2;
            front--;
            end++;
        }
        if(count > maxLen){
            maxLen = count;
            endIdx = end;
            frontIdx = front;
        }
    }
    prestr[endIdx+1] = '\0';
    return s+frontIdx;
}

char* longestPalindromeDP(char* s){
    char* p = s;
    int len = 0;
    while(*p != '\0'){
        len++;
    }
    bool* dp = (bool*)malloc(sizeof(bool)*len);
    /* init dp */
    for(int i = 0; i<N; i++){
        dp[i][i] = true;
        if(i+1 == N-1) break;
        dp[i][i+1] = *(s+i) == *(s+i+1);
    }
    for(int i = 0; i<N-1; i++){
        for(int j = i+2; j<N; j++){
            dp[i][j] = *(s+i)==*(s+j) && dp[i+1][j-1];
        }
    }
    for(int i = 0; i<N; i++){
        int j = i;
        while(i<N&&j<N){
            if(dp[i][j]){
                if(j)
                return
            }

        }
    }


}

int main(){
    char* s = "1331";
    longestPalindromeDP(s);
    scanf("%s", s);
    scanf("%s", s);
}
