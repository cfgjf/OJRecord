#include <cstdio>
#include <bitset>
/*
 * 参考异或运算
 * 异或为两次运算归零，构造一三次运算归零运算
 * “模拟”三进制，用两个bit存储两位
 * 改进：用int数组，空间可观且更直观
 */
using namespace std;
typedef bitset<31> bit;

int res[31] = {0};

void processBit(int x){
    bit tmp(x);
    for (int i = 0; i <= 30; ++i)
        res[i] = (res[i] + tmp[i]) % 3;
}

int main(){
    int n, k;
    scanf("%d", &n);
    for (int i = 0; i < 3 * n - 1; ++i){
        scanf("%d", &k);
        processBit(k);
    }
    int tmp = 1, resInt = 0;
    for (int i = 0; i <= 30; ++i){
        resInt += tmp * (res[i] >> 1);
        tmp <<= 1;
    }
    printf("%d", resInt);
}