#include <stdio.h>
//NOLINTBEGIN
void linspace(double v[], double start, double stop, int n);

void add(double v1[], const double v2[], int n);

double dot_product(const double v1[], const double v2[], int n);

void multiply_by_scalar(double v[], int n, double s);

void range(double v[], int n, double start, double step);

void read_vector(double v[], int n);

int main(void) {
    int choice;
    scanf("%d",&choice);
    int n;
    scanf("%d",&n);
    switch (choice) {
        case 1: {
            double wektor1[n];
            double start;
            double stop;
            scanf("%lf",&start);
            scanf("%lf",&stop);
            linspace(wektor1,start,stop,n);
            for (int i = 0; i < n; i++) {
                printf("%.2f ", wektor1[i]);
            }
            break;
        }
        case 2: {
            double wektor2[n];
            double wektor3[n];
            read_vector(wektor2,n);
            read_vector(wektor3,n);
            add(wektor2,wektor3,n);
            for (int i = 0; i < n; i++) {
                printf("%.2f ", wektor2[i]);
            }
            break;
        }
        case 3: {
            double wektor4[n];
            double wektor5[n];
            read_vector(wektor4,n);
            read_vector(wektor5,n);
            double wynik = dot_product(wektor4,wektor5,n);
            printf("%.2f", wynik);
            break;
        }
        case 4: {
            double wektor6[n];
            double scalar;
            scanf("%lf", &scalar);
            read_vector(wektor6,n);
            multiply_by_scalar(wektor6,n,scalar);
            for (int i = 0; i < n; i++) {
                printf("%.2f ", wektor6[i]);
            }
            break;
        }
        case 5: {
            double wektor7[100];
            double start;
            double step;
            scanf("%lf", &start);
            scanf("%lf", &step);
            range(wektor7,n,start,step);
            for (int i = 0; i < n; i++) {
                printf("%.2f ", wektor7[i]);
            }
            break;
        }
        default: {

            break;
        }
    }
    return 0;
}
void read_vector(double v[], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf",&v[i]);
    }
}
void add(double v1[], const double v2[], int n) {
    for (int i = 0; i < n; i++) {
        v1[i] = v1[i] + v2[i];
    }
}
void multiply_by_scalar(double v[], int n, double s) {
    for (int i = 0; i < n; i++) {
        v[i] = v[i] * s;
    }
}
double dot_product(const double v1[], const double v2[], int n) {
    double res = 0;
    for (int i = 0; i < n; i++) {
        res += (v1[i] * v2[i]);
    }
    return res;
}
void range(double v[], int n, double start, double step) {
    for (int i = 0; i < n; i++) {
        v[i] = start + (step * i);
    }
}
void linspace(double v[], double start, double stop, int n) {
    if (n <= 0) {
        return;
    }
    if (n == 1) {
        v[0] = start;
        return;
    }
    double krok = (stop - start) / (n - 1);
    for (int i = 0; i < n; i++) {
        v[i] = start + (krok * i);
    }
}
//NOLINTEND