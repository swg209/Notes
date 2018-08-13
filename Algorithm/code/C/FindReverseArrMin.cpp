#include<cstdio>
#define N 10000

// int Fibonacci(int n) {
//         int a1 = 0;
//         int a2 = 1;
//         int an;
//         while(n > 1){
//             an = a1 + a2;
//             a1 = a2;
//             a2 = an;
//             n--;
//             printf("%d\n", an);
//         }
//         printf("%d", an);
//     }
//
// int main(){
//     int fuck;
//     Fibonacci(39);
//     scanf("%d", &fuck);
// }

int main(){
    int arr[N] = {3,4,5,1,2};
    int endIdx = 4;
    int frontIdx = 0;
    int minNum = arr[frontIdx];
    for(int i = endIdx; i > frontIdx; i--){
        if(arr[i] > arr[i-1])
            continue;
        else{
            if(arr[i] < minNum){
                minNum = arr[i];
                break;
            }
        }
    }
    printf("%d", minNum);
    scanf("%d", &endIdx);
}
