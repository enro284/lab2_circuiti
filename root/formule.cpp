#include "TF1.h"

double V_g()
{
    double V_0 = 5.;

    // ricava

    return V_0;
}

double V_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double L = par[1];

    return V_g() * R / sqrt(R * R + W * W * L * L);
}

double V_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double L = par[1];
    double C = par[2];

    return V_g() * R / sqrt(R * R + (W * L - 1 / (W * C)) * (W * L - 1 / (W * C)));
}

double V_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double C = par[1];

    return V_g() * R / sqrt(R * R + 1 / (W * W * C * C));
}

/*
// DA FARE!!!
*/
double deg(double x){
    return x * 180. / TMath::Pi();
}
double p_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double L = par[1];

    return deg(-atan2(L * W, R));
}

double p_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double L = par[1];
    double C = par[2];

    return deg(-atan2(W * L - 1 / (W * C), R));
}

double p_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double C = par[1];

    return deg(atan2(1, C * W * R));
}