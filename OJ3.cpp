#include <cstdio>

int data[500000]{0};
int stack[20000][2]{0};

int main(){
    int n, sTop = 0; long long cnt = 0ll;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &data[i]);
    stack[sTop][0] = data[0]; stack[sTop++][1] = 1;
    for (int i = 1; i < n; ++i){
        if (data[i] < stack[sTop - 1][0]){
            stack[sTop][0] = data[i]; stack[sTop++][1] = 1;
            ++cnt;
            continue;
        }
        if (data[i] == stack[sTop - 1][0]){
            cnt += stack[sTop - 1][1];
            if (sTop > 1) ++cnt;
            ++stack[sTop - 1][1];
            continue;
        }
        while (sTop && data[i] > stack[sTop - 1][0]){
            --sTop; cnt += stack[sTop][1];
        }
        if (sTop){
            if (stack[sTop - 1][0] > data[i]) ++cnt;
            else{
                cnt += stack[sTop - 1][1];
                if (sTop > 1) ++cnt;
                ++stack[sTop - 1][1];
                continue;
            }
        }
        stack[sTop][0] = data[i]; stack[sTop++][1] = 1;
    } printf("%lld", cnt);
}