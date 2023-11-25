#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned short uint16;

uint16 inNum[65536]{0};
bool vis[65536]{false};
uint16 s[90000]; int sTop = 0;

int main(){
    vector<vector<uint16>> adj;
    int n, m; scanf("%d %d", &n, &m);
    adj.resize(n);
    for (int i = 0;i < n; ++i){
        uint16 x, y; scanf("%hu", &x);
        while (x--){
            scanf("%hu", &y);
            adj[i].push_back(y);
        }
    }

    // DFS
    s[sTop++] = 0;
    while (sTop){
        uint16 cur = s[sTop - 1]; --sTop;
        vis[cur] = true;
        for (uint16 nei : adj[cur]){
            ++inNum[nei];
            if (!vis[nei]) s[sTop++] = nei;
        }
    }

    bool flag = true;
    for (int i = 0; i < n; ++i){
        if (!vis[i]){
            flag = false;
            break;
        }
    }

    if (flag){
        printf("1\n");
        int x, y;
        while (m--){
            scanf("%d %d", &x, &y);
            if (inNum[y] == 1) printf("0\n");
            else{
                sTop = 0;
                fill(vis, vis + 65536, false);
                s[sTop++] = 0; bool dFlag = false;
                while (sTop){
                    uint16 cur = s[sTop - 1]; --sTop;
                    vis[cur] = true;
                    if (cur == x){
                        for (uint16 nei : adj[cur]){
                            if (!vis[nei] && nei != y) s[sTop++] = nei;
                        }
                    }else{
                        for (uint16 nei : adj[cur]){
                            if (nei == y){
                                dFlag = true; break;
                            }else if (!vis[nei]){
                                s[sTop++] = nei;
                            }
                        }
                        if (dFlag) break;
                    }
                }
                if (dFlag) printf("1\n");
                else printf("0\n");
            } // printf("1\n");
        }
    }else{
        for (int i = 0; i < m + 1; ++i){
            printf("0\n");
        }
    }
}
