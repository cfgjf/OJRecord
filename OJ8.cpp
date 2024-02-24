#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

typedef long double ld;
ld dd[100]{0};
pair<ld, ld> p[100];

inline ld myAbs (const ld& input) { return (input > 0) ? input : -input;}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ld iX, iY; set<ld> data;
    for (int i = 0; i < n; ++i){
        auto loc = data.size();
        scanf("%Lf %Lf", &iX, &iY);
        auto check = data.insert(iX);
        if (!check.second) continue;
        p[loc] = {iX, iY};
    } n = static_cast<int>(data.size());// 此时n为非重复数据对个数
    sort(p, p + n, [](const pair<ld, ld>& A, const pair<ld, ld>& B){
        return A.first <= B.first;
    });

//    另一种算法，差商表
//    for (int i = 0; i < n; ++i) dd[i][0] = p[i].second;
//    for (int i = 1; i < n; ++i){
//        for (int j = i; j < n; ++j)
//            dd[j][i] = (dd[j][i - 1] - dd[j - 1][i - 1]) / (p[j].first - p[j - i].first);
//    }

    dd[0] = p[0].second;
    for (int i = 1; i < n; ++i){
        ld temp = 1, res = p[i].second;
        for (int j = 0; j < i; ++j){
            res -= temp * dd[j];
            temp *= (p[i].first - p[j].first);
        } dd[i] = res / temp;
    }

    // 没办法，这误差只能分治了
    int maxP = 0;
    if (n >= 50) while (myAbs(dd[maxP + 1]) > 1e-4) ++maxP;
    else{
        maxP = n - 1;
        while (maxP && myAbs(dd[maxP]) <= 5e-3) --maxP;
    } printf("%d\n", maxP);

//    for (int i = 0; i <= maxP; ++i){
//        printf("%lf\n", dd[i][i]);
//    }

    ld input, res, tmp;
    for (int i = 0; i < m; ++i){
        scanf("%Lf", &input);
        res = p[0].second; tmp = 1;
        for (int j = 0; j < maxP; ++j){
            tmp *= input - p[j].first;
            res += tmp * dd[j + 1];
        } printf("%.6Lf\n", res);
    }
}