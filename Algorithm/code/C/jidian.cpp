#include<iostream>
using namespace std;
int main(){
    int xuefen[] = {2,1,2,2,2,2,3,2,4,2,2,2,2};
    //float jidian[] = {3.0,2.3,3.0,3.7,2.0,2.3,2.7,3.3,3.7,3.7,3.7,3.7,3.0};
    float jidian[] = {3.7,3.3,3.3,3.7,3.7,3.7,4.0,3.7,3.7,4.0,3.7,3.7,3.7};
    int len = 13;
    int sumxuefen = 0;
    float jiaquan = 0.0;
    for(int i = 0; i<len; i++){
        jiaquan += xuefen[i]*jidian[i];
        sumxuefen += xuefen[i];
    }
    cout << jiaquan/sumxuefen << endl;
    cin >> len;
}
