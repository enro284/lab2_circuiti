// Par indipendenti per ciascun canale (tutti)

#include "TF1.h"
#include "TComplex.h"

double V_g(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    TComplex Hgen = Z_load / (Z_gen + Z_load);

    return V_0 * (TComplex::Abs(Hgen));
}

double V_w(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HW = Z_RW / (Z_W);
    return V_0 * (TComplex::Abs(Hgen * HW));
}

double V_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HM = (Z_RM) / (Z_M);
    return V_0 * (TComplex::Abs(Hgen * HM));
}
double V_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HT = (Z_RT) / (Z_T);
    return V_0 * (TComplex::Abs(Hgen * HT));
}

double deg(double x)
{
    return x * 180. / TMath::Pi();
}

double p_w(double *f, double *par)
{
    
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HW = (Z_RW) / (Z_W);
    return deg((Hgen * HW).Theta());
}

double p_m(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HM = (Z_RM) / (Z_M);
    return deg((Hgen * HM).Theta());
}

double p_t(double *f, double *par)
{
    double W = 2 * TMath::Pi() * *f;
    double V_0 = par[0];
    TComplex Z_RW{par[1], 0};
    TComplex Z_RM{par[2], 0};
    TComplex Z_RT{par[3], 0};
    TComplex Z_RWL{par[4], 0};
    TComplex Z_RML{par[5], 0};
    TComplex Z_gen{par[6], 0.};
    TComplex Z_LW{0, W * par[7]};
    TComplex Z_LM{0, W * par[8]};
    TComplex Z_CM{0, -1 / (W * par[9])};
    TComplex Z_CT{0, -1 / (W * par[10])};

    TComplex Z_W = Z_RW + Z_LW + Z_RWL;
    TComplex Z_M = Z_RM + Z_LM + Z_CM + Z_RML;
    TComplex Z_T = Z_RT + Z_CT;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Hgen = Z_load / (Z_gen + Z_load);
    TComplex HT = (Z_RT) / (Z_T);
    return deg((Hgen * HT).Theta());
}
