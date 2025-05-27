// Par indipendenti per ciascun canale (ridotti)
// ossia R_w=R_m=R_t, ...

#include "TF1.h"
#include "TComplex.h"

double V_g(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_R{par[1], 0};
    TComplex Z_RL{par[2], 0};
    TComplex Z_gen{par[3], 0.};
    TComplex Z_L{0, W * par[4]};
    TComplex Z_C{0, -1 / (W * par[5])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    TComplex Hgen = Z_load / (Z_tot);

    return V_0 * (TComplex::Abs(Hgen));
}

double V_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_R{par[1], 0};
    TComplex Z_RL{par[2], 0};
    TComplex Z_gen{par[3], 0.};
    TComplex Z_L{0, W * par[4]};
    TComplex Z_C{0, -1 / (W * par[5])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    TComplex Hgen = Z_load / (Z_tot);
    TComplex HW = Z_R / (Z_W);
    return V_0 * (TComplex::Abs(Hgen * HW));
}

double V_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_R{par[1], 0};
    TComplex Z_RL{par[2], 0};
    TComplex Z_gen{par[3], 0.};
    TComplex Z_L{0, W * par[4]};
    TComplex Z_C{0, -1 / (W * par[5])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HM = (Z_R) / (Z_M);
    return V_0 * (TComplex::Abs(Hgen * HM));
}
double V_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_R{par[1], 0};
    TComplex Z_RL{par[2], 0};
    TComplex Z_gen{par[3], 0.};
    TComplex Z_L{0, W * par[4]};
    TComplex Z_C{0, -1 / (W * par[5])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HT = (Z_R) / (Z_T);
    return V_0 * (TComplex::Abs(Hgen * HT));
}

double deg(double x)
{
    return x * 180. / TMath::Pi();
}

double p_g(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    TComplex Z_R{par[0], 0};
    TComplex Z_RL{par[1], 0};
    TComplex Z_gen{par[2], 0.};
    TComplex Z_L{0, W * par[3]};
    TComplex Z_C{0, -1 / (W * par[4])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);

    return deg(Hgen.Theta());
}
double p_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    TComplex Z_R{par[0], 0};
    TComplex Z_RL{par[1], 0};
    TComplex Z_gen{par[2], 0.};
    TComplex Z_L{0, W * par[3]};
    TComplex Z_C{0, -1 / (W * par[4])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    TComplex Hgen = Z_load / (Z_tot);
    TComplex HW = Z_R / (Z_W);

    return deg((Hgen * HW).Theta());
}

double p_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    TComplex Z_R{par[0], 0};
    TComplex Z_RL{par[1], 0};
    TComplex Z_gen{par[2], 0.};
    TComplex Z_L{0, W * par[3]};
    TComplex Z_C{0, -1 / (W * par[4])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HM = (Z_R) / (Z_M);

    return deg((Hgen * HM).Theta() + par[5]);
}

double p_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    TComplex Z_R{par[0], 0};
    TComplex Z_RL{par[1], 0};
    TComplex Z_gen{par[2], 0.};
    TComplex Z_L{0, W * par[3]};
    TComplex Z_C{0, -1 / (W * par[4])};

    TComplex Z_W = Z_R + Z_L + Z_RL;
    TComplex Z_M = Z_R + Z_L + Z_C + Z_RL;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HT = (Z_R) / (Z_T);

    return deg((Hgen * HT).Theta() + par[5]);
}
