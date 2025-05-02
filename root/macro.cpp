#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "formule.cpp" //si lo so, non si fa

const double f_min = 0.;
const double f_max = 50E3;

void amplitude(const char *data_w, const char *data_m, const char *data_t)
{
    auto canvas = new TCanvas();

    auto graph_w = new TGraph(data_w, "%lg %lg");
    auto graph_m = new TGraph(data_m, "%lg %lg");
    auto graph_t = new TGraph(data_t, "%lg %lg");

    auto mg = new TMultiGraph();
    mg->Add(graph_w);
    mg->Add(graph_m);
    mg->Add(graph_t);

    mg->GetXaxis()->SetLimits(f_min, f_max);
    mg->SetMinimum(0.);
    mg->SetMaximum(5.5);

    mg->Draw("AP");

    auto func_w = new TF1("Tensione Woofer", V_w, f_min, f_max, 2);
    func_w->SetParameters(3E3, 47E-3);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Tensione Mid", V_m, f_min, f_max, 3);
    func_m->SetParameters(3E3, 47E-3, 4.7E-9);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Tensione Tweeter", V_t, f_min, f_max, 2);
    func_t->SetParameters(3E3, 4.7E-9);
    func_t->SetLineColor(kRed);

    func_w->Draw("same");
    func_m->Draw("same");
    func_t->Draw("same");
}

void phase(const char *data_w, const char *data_m, const char *data_t)
{
    auto canvas = new TCanvas();

    auto graph_w = new TGraph(data_w, "%lg %lg");
    auto graph_m = new TGraph(data_m, "%lg %lg");
    auto graph_t = new TGraph(data_t, "%lg %lg");

    auto mg = new TMultiGraph();
    mg->Add(graph_w);
    mg->Add(graph_m);
    mg->Add(graph_t);

    mg->Draw("AP");
    
    auto func_w = new TF1("Fase Woofer", p_w, f_min, f_max, 2);
    func_w->SetParameters(3E3, 47E-3);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Fase Mid", p_m, f_min, f_max, 3);
    func_m->SetParameters(3E3, 47E-3, 4.7E-9);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Fase Tweeter", p_t, f_min, f_max, 2);
    func_t->SetParameters(3E3, 4.7E-9);
    func_t->SetLineColor(kRed);

    func_w->Draw("same");
    func_m->Draw("same");
    func_t->Draw("same");
}