#include <cstdio>
using namespace std;

int lower_bound(const int* arr, int r, long long x){
    int res = r + 1, mid, l = 0;
    while (l <= r){
        mid = l + ((r - l) >> 1) ;
        if (arr[mid] >= x){
            r = mid - 1;
            res = mid;
        }else l = mid + 1;
    } return res;
}


// 查找小于x的最大元素
int find_lower_bound(const int* arr, int r, long long x){
    int res = 0, mid, l = 0;
    while (l <= r){
        mid = l + ((r - l) >> 1) ;
        if (arr[mid] >= x){
            r = mid - 1;
        }else{
            res = mid;
            l = mid + 1;
        }
    } return (arr[res] >= x) ? res - 1 : res;
}

// 查找大于x的最小元素
int find_upper_bound(const int* arr, int r, long long x){
    int res = r, mid, l = 0;
    while (l <= r){
        mid = l + ((r - l) >> 1) ;
        if (arr[mid] > x){
            res = mid;
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    } return (arr[res] <= x) ? res + 1 : res;
}

int bFind(const int* arr, int r, int x){
    int res, l = 0;
    while (l <= r){
        res = l + ((r - l) >> 1);
        if (arr[res] == x) return res;
        else if (arr[res] > x) r = res - 1;
        else l = res + 1;
    } return res;
}

void remove_and_add(int* arr, int r, int x, int y){
    int xLoc = bFind(arr, r, x), i;
    if (x < y){
        for (i = xLoc + 1; i <= /* 老子以后再把容器大小和元素下标混用我就是狗 */ r && arr[i] < y; ++i){
            arr[i - 1] = arr[i];
        } arr[i - 1] = y;
    }else{
        for (i = xLoc - 1; i >= 0 && arr[i] > y; --i){
            arr[i + 1] = arr[i];
        } arr[i + 1] = y;
    }
}

// j为要插入的数的位置
void insert_sort(int * arr, int j){
//    if (i == j) return;
    int x = arr[j], r;
    for (r = j - 1; r >= 0 && arr[r] > x; --r){
        arr[r + 1] = arr[r];
    } arr[r + 1] = x;
}

bool check(const int* arr, int size){
    for (int i = 0; i < size - 1; ++i){
        if (arr[i] > arr[i + 1]) return false;
    }return true;
}

int main(){
    int n, len, hei;
    unsigned long long cnt = 0ull;
    scanf("%d %d %d", &n, &len, &hei);

    int *h = new int[n + 10];
    int *k = new int[len + 10];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
    }

    int i = 0, j, r, l;

    for (j = 1; j <= len && j < n; ++j){
        k[j - 1] = h[j - 1];
        insert_sort(k, j - 1);// printf("%d\n", check(k, j - 1));
        l = find_lower_bound(k, j - 1, (long long)h[j] - hei);
        r = find_upper_bound(k, j - 1, (long long)h[j] + hei);

//        for (int ii = 0; ii < j; ++ii){
//            printf("%d ", k[ii]);
//        } printf("\n%d %d\n", l, r);

        cnt += (r - l - 1);
    }

    for ( ; j < n; ++j, ++i){
        remove_and_add(k, len - 1, h[i], h[j - 1]);// printf("%d\n", check(k, len - 1));
        l = find_lower_bound(k, len - 1, (long long)h[j] - hei);
        r = find_upper_bound(k, len - 1, (long long)h[j] + hei);

//        for (int ii = 0; ii < len; ++ii){
//            printf("%d ", k[ii]);
//        } printf("\n%d %d\n", l, r);

        cnt += (r - l - 1);
    }

    delete [] h;
    delete [] k;

    printf("%llu", cnt);
}