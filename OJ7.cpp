#include <cstdio>
using namespace std;


// http://nhqks.cnjournals.com/zr/ch/reader/create_pdf.aspx?file_no=20080101&year_id=2008&quarter_id=1&falg=1
int main(){
    int n, m, p, i, j;
    scanf("%d %d %d", &p, &n, &m);
    if (p == 3){
        auto *a = new int[n + 1]; auto *b = new double[n + 1]; auto *c = new double[n]; auto *z = new double[n + 1];
        auto *alpha = new double[n + 1]; auto *beta = new double[n]; auto *y = new double[n + 1]; auto *res = new double[n + 1];
        double x;
        for (i = 1; i < n; ++i){
            scanf("%lf", &x);
            c[i] = x;
        }
        for (i = 1; i <= n; ++i){
            scanf("%lf", &x);
            b[i] = x;
        }
        for (i = 2; i <= n; ++i) scanf("%d", &a[i]);
        // LU分解
        alpha[1] = b[1];
        for (i = 1; i < n; ++i){
            beta[i] = c[i] / alpha[i];
            alpha[i + 1] = b[i + 1] - beta[i] * (double)a[i + 1];
        }

        for (j = 0; j < m; ++j){
            for (i = 1; i <= n; ++i){
                scanf("%lf", &x);
                z[i] = x;
            }
            y[1] = z[1] / alpha[1];
            for (i = 2; i <= n; ++i)
                y[i] = (z[i] - (double)a[i] * y[i - 1]) / alpha[i];
            res[n] = y[n];
            for (i = n - 1; i; --i)
                res[i] = y[i] - beta[i] * res[i + 1];

            for (i = 1; i < n; ++i)
                printf("%.4f ", res[i]);
            printf("%.4f\n", res[i]);
        }
    }else{
        auto *a = new int[n + 1]; auto *b = new double[n + 1]; auto *c = new double[n + 1]; auto *d = new int[n]; auto *e = new int[n - 1]; auto *z = new double[n + 1];
        for (i = 1; i < n - 1; ++i) scanf("%d", &e[i]);
        for (i = 1; i < n; ++i) scanf("%d", &d[i]);
        for (i = 1; i < n + 1; ++i) scanf("%lf", &c[i]);
        for (i = 2; i < n + 1; ++i) scanf("%lf", &b[i]);
        for (i = 3; i < n + 1; ++i) scanf("%d", &a[i]);

        auto *alpha = new double[n + 1]; auto *beta = new double[n]; auto *q = new double[n - 1]; auto *u = new double[n + 1];
        // LU
        alpha[1] = c[1]; u[2] = b[2]; beta[1] = d[1] / alpha[1];
        alpha[2] = c[2] - u[2] * beta[1]; q[1] = e[1] / alpha[1];
        for (i = 2; i <= n - 2; ++i){
            q[i] = e[i] / alpha[i];
            beta[i] = (d[i] - u[i] * q[i - 1]) / alpha[i];
            u[i + 1] = b[i + 1] - a[i + 1] * beta[i - 1];
            alpha[i + 1] = c[i + 1] - a[i + 1] * q[i - 1] - u[i + 1] * beta[i];
        } // n - 1
        beta[i] = (d[i] - u[i] * q[i - 1]) / alpha[i];
        u[i + 1] = b[i + 1] - a[i + 1] * beta[i - 1];
        alpha[i + 1] = c[i + 1] - a[i + 1] * q[i - 1] - u[i + 1] * beta[i];

        for (j = 0; j < m; ++j){
            for (i = 1; i <= n; ++i) scanf("%lf", &z[i]);

            b[1] = z[1] / alpha[1]; b[2] = (z[2] - u[2] * b[1]) / alpha[2];
            for (i = 3; i <= n; ++i) b[i] = (z[i] - a[i] * b[i - 2] - u[i] * b[i - 1]) / alpha[i];

            c[n] = b[n]; c[n - 1] = b[n - 1] - beta[n - 1] * c[n];
            for (i = n - 2; i; --i) c[i] = b[i] - q[i] * c[i + 2] - beta[i] * c[i + 1];

            for (i = 1; i < n; ++i)
                printf("%.4f ", c[i]);
            printf("%.4f\n", c[i]);
        }

    }
}
