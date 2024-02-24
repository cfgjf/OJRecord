#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

inline int max(const int a, const int b){ return (a > b) ? a : b;}
int findFirstGreaterOrEqualElem(const vector<int>& data, int x);
//int tensor[2048][32];
//int dp[2048][2048];

int main() {
    int N, K; vector<vector<int>> dkList;
    scanf("%d %d", &N, &K); dkList.resize(K);

    auto dp = (int **)malloc(sizeof(int*) * (N + 1));
    auto tensor = (int **)malloc(sizeof(int*) * (N + 1));
    auto dim = (int *)malloc(sizeof(int*) * (N + 1));
    auto DK = (int **)malloc(sizeof(int*) * (N + 1));

    DK[0] = (int*)malloc(sizeof(int) * K);
    for (int i = 1; i <= K - 2; ++i) DK[0][i] = 0;

    for (int i = 1; i <= N; ++i) {
        dp[i] = (int *)malloc(sizeof(int) * (N + 1)); dp[i][i] = 0;
        tensor[i] = (int *)malloc(sizeof(int) * (K + 1));
        dim[i] = 1;
        DK[i] = (int *)malloc(sizeof(int) * K);
        for (int j = 1; j <= K - 2; ++j){
            scanf("%d", &tensor[i][j]); dim[i] *= tensor[i][j];
            if (tensor[i][j] > 1){
                dkList[j].push_back(i);
                DK[i][j] = DK[i - 1][j] + 1;
            }else DK[i][j] = DK[i - 1][j];
        } for (int j = K - 1; j <= K; ++j) scanf("%d", &tensor[i][j]);
    }
/*
    for (int i = 1; i < N; ++i){
        int cnt = 1;
        for (int j = 1; j <= K - 2; ++j)
            cnt *= max(tensor[i][j], tensor[i + 1][j]);
        dp[i][i + 1] = cnt * tensor[i][K - 1] * tensor[i][K] * tensor[i + 1][K];
    }
*/
    for (int itl = 1; itl < N; ++itl){
        for (int st = 1; st + itl <= N; ++st){
            int ed = st + itl;
            int res = 0x7fffffff, temp, cnt = dim[st];
            for (int d = 1; d <= K - 2; ++d){
                if (tensor[st][d] > 1) continue;
                if (DK[ed][d] - DK[st][d]) cnt *= tensor[dkList[d].front()][d];
                // auto y = findFirstGreaterOrEqualElem(dkList[d], st);
                // if (y <= ed) cnt *= tensor[y][d];
            }
            /*for (int d = 1; d <= K - 2; ++d){
                if (tensor[st][d] > 1) continue;
                for (int i = st; i <= ed; ++i){
                    if (tensor[i][d] > 1){
                        cnt *= tensor[i][d]; break;
                    }
                }
            }*/ cnt *= tensor[st][K - 1] * tensor[ed][K];
            for (int k = st; k < ed; ++k){
                temp = cnt * tensor[k][K] + dp[st][k] + dp[k + 1][ed];
                res = (res < temp) ? res : temp;
            } dp[st][ed] = res;
        }
    } printf("%d", dp[1][N]);
}

int findFirstGreaterOrEqualElem(const vector<int>& data, int x) {
    int l = 0, r = static_cast<int>(data.size() - 1);
    int res = -1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (data[mid] >= x) {
            res = mid; r = mid - 1;
        } else l = mid + 1;
    } return (res == -1) ? 3000 : data[res];
}