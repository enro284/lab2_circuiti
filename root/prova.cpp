#include <fstream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TComplex.h"

const double f_min = 0.;
const double f_max = 50E3;

double V_g(double *f, double *par)
{
    double V_0 = par[3];
    // V_0 1- R/Z (in modulo)

    double W = 2 * TMath::Pi() * *f;
    TComplex Z_R{par[0], 0};
    TComplex Z_L{0, W * par[1]};
    TComplex Z_C{0, -1 / (W * par[2])};
    TComplex Z_gen{50., 0.};

    TComplex Z_W = Z_R + Z_L;
    TComplex Z_M = Z_R + Z_L + Z_C;
    TComplex Z_T = Z_R + Z_C;

    TComplex Z_load = 1. / (1. / Z_W + 1. / Z_M + 1. / Z_T);

    TComplex Z_tot = Z_load + Z_gen;

    return V_0 * (TComplex::Abs(1 - Z_gen / Z_tot));
}

void macro(const char *data)
{
    auto canvas = new TCanvas();

    auto graph = new TGraphErrors(data, "%lg %lg %lg");
    auto func = new TF1("Tensione Generatore", V_g, f_min, f_max, 4);
    func->SetParameters(3E3, 47E-3, 4.7E-9, 5.09);
    func->SetParLimits(0, 2800, 3200);
    func->SetParLimits(1, 40E-3, 55E-3);
    func->SetParLimits(2, 4.0E-9, 5.5E-9);
    
    graph->SetMarkerSize(2);
    graph->Draw("AP");
    func->Draw("same");

    //graph->Fit(func);
    func->Draw("same");
}