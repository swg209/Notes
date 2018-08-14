#include<cstdio>
#define N 99999
int main(){
    int nums[] = {-2,1,-3,4,-1,2,1,-5,4};
    int numsSize = 9;
    int dpSum[N] = {0};
    int dpfront[N] = {0};
    int maxsum = nums[0];
    dpSum[0] = nums[0];
    /* 计算第i个位置的最大连续子序列和及其上下标
     * 则在第i+1个位置上
     *  1. 若 endIdx_i+1=i+1
     *      sum[i]+nums[i+1]>sum[i]?
     *          Y   sum[i+1] = sum[i]+num[i+1], endIdx_i+1=i+1
     *          N   求以nums[i+1]结尾的子数组的最大和
     *              1) 若最大和>=sum[i], sum[i+1]=该最大和
     *              2) 若最大和<sum[i], 沿用上一个最大和
     *  2. 若 endIdx_i+1!=i+1
     *
     */

    /* 上面的思路太复杂了，可以换个角度
     * 求以nums[i]结尾的最大连续子序列和，就可以避免上面如此多的情况判断 */
    for(int i = 1; i < numsSize; i++){
        if(dpSum[i-1]+nums[i] >= nums[i]){
            dpfront[i] = dpfront[i-1];
            dpSum[i] = dpSum[i-1]+nums[i];
        }
        else{
            dpfront[i] = i;
            dpSum[i] = nums[i];
        }
        if(dpSum[i] > maxsum)
            maxsum = dpSum[i];
    }
    return maxsum;
}
