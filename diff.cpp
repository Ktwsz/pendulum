#include <math.h>
#include <utility>
#define PR pair <double, double>

double calc_th(double th, double th_dt, double C) {
    double th_2h = 2*th_dt;
    th_2h -= sin(th)*C;
    th_2h -= th;

    return th_2h;
}

double get_C(double dt, double l, double g) {
    double res = g; 
    res *= dt;
    res *= dt;
    res /= l;

    return res;
}

double theta_to_rad(double theta) {
    double rad = theta/360;
    rad *= 2*M_PI;
    return rad;
}

PR get_r(double theta, double l) {
    return {l*sin(theta), l*cos(theta)};
}
