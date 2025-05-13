#include "TF1.h"

double V_g(double *f, double *par)
{
    double V_0 = par[3];
    // V_0 1- R/Z (in modulo)

    double W = 2 * TMath::Pi() * *f;
    TComplex Z_R{par[0], 0};
    TComplex Z_L{0, W * par[1]};
    TComplex Z_C{0, -1 / (W * par[2])};
    TComplex Z_gen{par[4], 0.};
    TComplex Z_LR{par[5], 0.};

    TComplex Z_W = Z_R + Z_L + Z_LR;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_LR;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    return V_0 * (TComplex::Abs(Z_load / (Z_gen + Z_load)));
}

double V_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double RL = par[1];
    double L = par[2];

    return R / sqrt((R + RL) * (R + RL) + W * W * L * L);
}

double V_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double RL = par[1];
    double L = par[2];
    double C = par[3];

    return R / sqrt((R + RL) * (R + RL) + (W * L - 1 / (W * C)) * (W * L - 1 / (W * C)));
}

double V_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double C = par[1];

    return R / sqrt(R * R + 1 / (W * W * C * C));
}

double deg(double x)
{
    return x * 180. / TMath::Pi();
}

double p_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double RL = par[1];
    double L = par[2];

    return deg(-atan2(L * W, R + RL));
}

double p_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double RL = par[1];
    double L = par[2];
    double C = par[3];

    return deg(-atan2(W * L - 1 / (W * C), R + RL));
}

double p_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double R = par[0];
    double C = par[1];

    return deg(atan2(1, C * W * R));
}