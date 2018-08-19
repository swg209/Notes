/* leetcode 416 */

#include<cstdio>
#include<cstdlib>
#define N 2000
/*
    解法一： 划分为两个背包问题
        条件： 数组是有序的
    */
bool canPartition(int* nums, int numsSize) {
    int sum = 0;
    int bag;
    int dp[N][N] = {0};
    bool* visited = (bool*)mallloc(sizeof(bool)*numsSize);
    for (int i = 0; i < numsSize; i++)
        sum += nums[i];

    /* 不可整除，即不可能划分为等同的两部分 */
    if (sum & 1)
        return false;

    /* 可整除，设置背包大小为sum/2 */
    bag = sum/2;

    /* 从小到大，即从前往后做 */
    for(int i = 0; i < numsSize; i++){
        for(int j = 0; j < bag; j++){

        }
    }

}

// int bagPromlem(int bagsize, int num, int* weight, int* )
