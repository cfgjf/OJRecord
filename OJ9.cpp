// 一遍过！！（
#include <cstdio>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

struct edge{
    int x, y;
    int cost;
    int time;
    edge(int ix = 0, int iy = 0, int ic = 0, int it = 0){
        x = ix; y = iy; cost = ic; time = it;
    }
};

struct compare {
    bool operator()(const edge& e1, const edge& e2) const {
        return e1.cost > e2.cost;
    }
};

int cost[65536]{0}, time[65536]{0};

int main(){
    vector<vector<edge>> g;
    int N, M; scanf("%d %d", &N, &M); g.resize(N);
    int i, j, k, l;
    for (int p = 0; p < M; ++p){
        scanf("%d %d %d %d", &i, &j, &k, &l);
        g[i].emplace_back(i, j, l, k);
    }
    int st, ed, MAX_TIME;
    scanf("%d %d %d", &st, &ed, &MAX_TIME);
    priority_queue<edge, deque<edge>, compare> heap;

    for (i = 0; i < g[st].size(); ++i){
        const auto& e = g[st][i];
        cost[e.y] = e.cost; time[e.y] = e.time;
        heap.push(e);
    }

    while (!heap.empty()){
        auto cur = heap.top(); heap.pop();
        i = cur.y; // i为出发
        // 此处不加判断是因为要保留虽然路径长，但是时间短的情况
        // if (cost[i] < cur.cost) continue;
        for (k = 0; k < g[i].size(); ++k){
            j = g[i][k].y; // j为到达
            auto t = cur.time + g[i][k].time;
            if (t <= MAX_TIME){
                if (cost[j] == 0 || (cur.cost + g[i][k].cost < cost[j])){
                    cost[j] = cur.cost + g[i][k].cost; time[j] = t;
                    heap.emplace(i, j, cost[j], t);
                }else if(t <= time[j]) // 时间短就不更新表格，只在堆里存储这个情况
                    heap.emplace(i, j, cur.cost + g[i][k].cost, t);
            }
        }
    } printf("%d", (cost[ed] == 0 ? -1 : cost[ed]));
}