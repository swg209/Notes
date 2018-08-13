/*
 * 给定一个double类型的浮点数base和int类型的整数exponent。
 * 求base的exponent次方。
 */
#include<cstdio>
#include<algorithm>

/*
 * 常规方法
 */
double Power(double base, int exponent) {
    double result = base;
    if(base == 0){
        return 0.0;
    }
    if(base == 1){
        return 1;
    }
    if(exponent > 0 or exponent < 0){
        for(int i = 1; i < abs(exponent); i++){
            result *= base;
        }
        if(exponent<0)
            return 1/result;
        else
            return result;
    }
    else{
        return 1;
    }
}

/*
 * 快速指数求幂：
 *  核心思想 将幂化为二进制数形式
 *  例如
 *      10 = (1010)b
 *      5^10 = 5^8 * 5^2
 *
 */
double PowerQuick(double base, int exponent){
    if(base == 0)   return 0;
    if(base == 1 or exponent == 0)   return 1;

    int abs_exp = abs(exponent);
    double result = 1;
    while(abs_exp){
        if(abs_exp & 1) result *= base;
        base *= base;
    }
    return exponent > 0? result:1/result;
}

int main(){

}
