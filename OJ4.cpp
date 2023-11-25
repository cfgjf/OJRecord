#include <cstdio>
#include <vector>
typedef long long uint;
using namespace std;

int countRange(vector<uint>& v, uint l, uint r){
    int left = 0, right = static_cast<int>(v.size());
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (v[mid] < l) left = mid + 1;
        else right = mid;
    } int leftBound = left;

    left = 0, right = static_cast<int>(v.size());
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (v[mid] <= r) left = mid + 1;
        else right = mid;
    } int rightBound = left;
    return rightBound - leftBound;
}

int main(){
    int n, m;
    vector<uint> target, shatter;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i){
        uint x; scanf("%lld", &x);
        shatter.push_back(x);
    }
    for (int i = 0; i < m; ++i){
        uint x; scanf("%lld", &x);
        target.push_back(x);
    }

    vector<uint> fNum, lNum;
    uint first = 1, count = 1, cur = 0;
    fNum.push_back(1); lNum.push_back(1);
    do{
        int minus = 0;
        while(cur < n && shatter[cur] <= first + count - 1){
            ++minus; ++cur;
        }
        first += count; count *= 2;
        count -= 2 * minus;
        fNum.push_back(first); lNum.push_back(count);
    }while (count && first + count - 1 <= target.back());

    vector<uint> path;
    for (auto tar : target){
        if (tar == 1){
            printf("1\n"); continue;
        }
        bool flag = false; int index = 0;
        for (; index < fNum.size(); ++index){
            if (fNum[index] + lNum[index] - 1 >= tar){
                flag = true;
                break;
            }
        }
        if (flag){
            path.push_back(tar);
            while (index != 1){
                uint seg = (tar - fNum[index]) >> 1;
                --index; uint r = fNum[index] + seg, l = fNum[index];
                int sCnt = countRange(shatter, l, r);
                while (sCnt){
                    l = r + 1; r += sCnt;
                    sCnt = countRange(shatter, l, r);
                } path.push_back(r); tar = r;
            } printf("1 ");
            for (int i = static_cast<int>(path.size() - 1); i; --i)
                printf("%lld ", path[i]);
            printf("%lld\n", path[0]);
            path.clear();
        }else printf("0\n");
    }
}