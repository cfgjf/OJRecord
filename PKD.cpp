#include <iostream>
#include <queue>
#include <deque>
#include <cstring>

using namespace std;

struct edge{
    int x, y;
    double n;
    edge(int ix = 0, int iy = 0, double in = 0){
        x = ix; y = iy; n = in;
    }
};

struct compare {
    bool operator()(const edge& e1, const edge& e2) const {
        return e1.n > e2.n;
    }
};

double map[6][6]{0};
int UFSet[6];

int find(int p){
    while (UFSet[p] > -1) p = UFSet[p];
    return p;
}

void merge(int u, int v){
    UFSet[u] += UFSet[v];
    UFSet[v] = u;
}

void init(){
    memset(UFSet, -1, sizeof(UFSet));
    map[0][1] = 2.236; map[0][3] = 2.236; map[0][4] = 4.472;
    map[1][0] = 2.236; map[1][5] = 4;
    map[2][5] = 2.236; map[2][4] = 3.606; map[2][3] = 3.162;
    map[3][5] = 2.236; map[3][4] = 3; map[3][0] = 2.236; map[3][2] = 3.162;
    map[4][3] = 3; map[4][0] = 4.472; map[4][2] = 3.606;
    map[5][3] = 2.236; map[5][2] = 2.236; map[5][1] = 4;
}

void Prim(){
    cout << "Prim start!" << endl;
    bool inTree[6]{false};
    priority_queue<edge, deque<edge>, compare> heap;

    inTree[0] = true;
    int cnt = 1, cur = 0;
    do{
        for (int i = 0; i < 6; ++i){
            if (!inTree[i] && map[cur][i])
                heap.emplace(cur, i, map[cur][i]);
        }
        while (!heap.empty()){
            edge e = heap.top(); heap.pop();
            if (!inTree[e.y]){
                inTree[e.y] = true; cur = e.y;
                cout << "Now adding: " << e.x << " -> " << e.y << ", weight: " << e.n << endl;
                ++cnt; break;
            }
        }
    }while (cnt < 6);
    cout << "----------------------------------" << endl;
}

void Kruskal(){
    cout << "Kruskal start!" << endl;
    priority_queue<edge, deque<edge>, compare> heap;
    for (int i = 0; i < 6; ++i){
        for (int j = 0; j < 6; ++j){
            if (map[i][j]) heap.emplace(i, j, map[i][j]);
        }
    }
    int cnt = 1;
    while (cnt < 6){
        edge e = heap.top(); heap.pop();
        int i = find(e.x), j = find(e.y);
        if (i != j){
            merge(i, j); ++cnt;
            cout << "Now adding: " << e.x << " -> " << e.y << ", weight: " << e.n << endl;
        }
    } cout << "----------------------------------" << endl;
}

void Dijkstra(){
    cout << "Dijkstra start!" << endl;
    double dist[6]{0};
    bool s[6]{false};
    priority_queue<pair<double, int>, deque<pair<double, int>>, greater<>> heap;

    for (int i = 0; i < 6; ++i){
        if (map[0][i] == 0) continue;
        dist[i] = map[0][i];
        heap.emplace(map[0][i], i);
    } s[0] = true;

    while (!heap.empty()){
        auto cur = heap.top(); heap.pop();
        if (dist[cur.second] < cur.first) continue;
        auto i = cur.second; s[i] = true;
        for (int j = 0; j < 6; ++j){
            if (map[i][j] == 0) continue;
            if (dist[j] == 0){
                dist[j] = dist[i] + map[i][j];
                heap.emplace(dist[j], j);
            }else if (!s[j] && dist[i] + map[i][j] < dist[j]){
                dist[j] = dist[i] + map[i][j];
                heap.emplace(dist[j], j);
            }
        }
    }

    cout << "The shortest path from node 0: " << endl;
    for (int i = 1; i < 6; ++i){
        cout << "0 -> " << i << ": " << dist[i] << endl;
    } cout << "----------------------------------" << endl;
}

int main(){
    init();
    Prim();
    Kruskal();
    Dijkstra();
}