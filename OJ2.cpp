#include <cstdio>

int prev[100000]{0}, next[100000]{0};
int head = 1;

void add(){
    int previous, now; scanf("%d %d",&previous, &now);
    if (!previous){
        if (!head){
            head = now; return;
        }
        next[now] = head;
        prev[head] = now;
        head = now;
    }else{
        next[now] = next[previous];
        prev[now] = previous;
        next[previous] = now;
        if (next[now]) prev[next[now]] = now;
    }
}

void find(){
    int x; scanf("%d", &x);
    if (!x) printf("%d\n", head);
    else printf("%d\n", next[x]);
}

void remove(){
    int x; scanf("%d", &x);
    if (x == head){
        head = next[head];
        next[x] = 0; prev[head] = 0;
    }else{
        next[prev[x]] = next[x];
        if (next[x]) prev[next[x]] = prev[x];
        next[x] = prev[x] = 0;
    }
}

int main(){
    int orders; scanf("%d", &orders);//cin >> orders;
    for (int i = 0; i < orders; ++i){
        int type; scanf("%d", &type);//cin >> type;
        if (type == 1) add();
        else if (type == 2) find();
        else remove();
    }
    for (int i = head; i; i = next[i])
        printf("%d\n", i);
}