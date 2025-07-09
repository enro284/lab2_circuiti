#include "TComplex.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

Double_t phase(Double_t *f, Double_t *par)
{
    Double_t w{*f * 2 * TMath::Pi()};
    TComplex r{3300, 0};
    TComplex c{0, -1 / (w * 4.7E-9)};
    TComplex r_c{par[0], 0};

    TComplex z = 1. / (1. / r_c + 1. / c) + r;

    return -z.Theta() * 180. / TMath::Pi();
}

void prova()
{
    auto c = new TCanvas("c", "name", 1000, 500);
    c->Divide(2, 1);

    auto f = new TF1("phase", phase, 1000, 50E3, 1);
    auto f1 = new TF1("phase1", phase, 1000, 50E3, 1);
    
    c->cd(1);
    f->SetParameter(0, 10E20);
    f->Draw();
    
    c->cd(2);
    f1->SetParameter(0, 4E4);
    f1->Draw();
}