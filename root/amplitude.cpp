#include <fstream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TLegend.h"

#include "formule2.cpp" //si lo so, non si fa
// DEFINITIVO NON TOCCARE RANGE O PARAMETRI, FAI SOLO ESTETICA
const double f_min = 1E3;
const double f_max = 50E3;
const double fit_min = 7E3;
const double fit_max = 14E3;

void amplitude(const char *data_g = "data/amp_g.txt", const char *data_w = "data/amp_w.txt", const char *data_m = "data/amp_m.txt", const char *data_t = "data/amp_t.txt")
{

    auto canvas = new TCanvas("canvas", "Amplitude", 2400, 1000);

    auto graph_w = new TGraphErrors(data_w, "%lg %lg");
    auto graph_m = new TGraphErrors(data_m, "%lg %lg");
    auto graph_t = new TGraphErrors(data_t, "%lg %lg");
    auto graph_g = new TGraphErrors(data_g, "%lg %lg");

    for (int i = 0; i < graph_g->GetN(); ++i)
    {
        double x, y;
        graph_g->GetPoint(i, x, y);
        graph_g->SetPointError(i, 0.186, 0.002);
    }
    for (int i = 0; i < graph_w->GetN(); ++i)
    {
        double x, y;
        graph_w->GetPoint(i, x, y);
        graph_w->SetPointError(i, 0.186, 0.002);
    }
    for (int i = 0; i < graph_m->GetN(); ++i)
    {
        double x, y;
        graph_m->GetPoint(i, x, y);
        graph_m->SetPointError(i, 0.186, 0.002);
    }
    for (int i = 0; i < graph_t->GetN(); ++i)
    {
        double x, y;
        graph_t->GetPoint(i, x, y);
        graph_t->SetPointError(i, 0.186, 0.002);
    }

    auto mg = new TMultiGraph();
    mg->SetTitle("Ampiezze - sweep completo;Frequenza (Hz);Ampiezza (V)");
    mg->Add(graph_w);
    mg->Add(graph_m);
    mg->Add(graph_t);
    mg->Add(graph_g);

    graph_g->SetMarkerStyle(20);
    graph_g->SetMarkerSize(0.6);
    graph_w->SetMarkerStyle(20);
    graph_w->SetMarkerSize(0.6);
    graph_m->SetMarkerStyle(20);
    graph_m->SetMarkerSize(0.6);
    graph_t->SetMarkerStyle(20);
    graph_t->SetMarkerSize(0.6);

    mg->GetXaxis()->SetLimits(f_min, f_max);
    mg->SetMinimum(0.);
    mg->GetXaxis()->SetMaxDigits(3);
    mg->GetXaxis()->SetNdivisions(520);
    mg->GetXaxis()->SetLabelSize(0.04);
    mg->GetXaxis()->SetTitleSize(0.04);
    mg->GetYaxis()->SetLabelSize(0.04);
    mg->GetYaxis()->SetTitleSize(0.04);
    mg->Draw("APE");

    gPad->SetGrid(1, 1);

    auto func_g = new TF1("Tensione Generatore", V_g, f_min, f_max, 11);
    func_g->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_g->SetParLimits(0, 4.5, 5.5);
    func_g->SetParLimits(1, 3.2E3, 3.4E3);
    func_g->SetParLimits(2, 3.2E3, 3.4E3);
    func_g->SetParLimits(3, 3.2E3, 3.4E3);
    func_g->SetParLimits(4, 110, 130);
    func_g->SetParLimits(5, 110, 130);
    func_g->SetParLimits(6, 45, 55);
    func_g->SetParLimits(7, 0.043, 0.05);
    func_g->SetParLimits(8, 0.043, 0.05);
    func_g->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_g->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_g->SetLineColor(kOrange);

    auto func_w = new TF1("Tensione Woofer", V_w, f_min, f_max, 11);
    func_w->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_w->SetParLimits(0, 4.5, 5.5);
    func_w->SetParLimits(1, 3.2E3, 3.4E3);
    func_w->SetParLimits(2, 3.2E3, 3.4E3);
    func_w->SetParLimits(3, 3.2E3, 3.4E3);
    func_w->SetParLimits(4, 110, 130);
    func_w->SetParLimits(5, 110, 130);
    func_w->SetParLimits(6, 45, 55);
    func_w->SetParLimits(7, 0.043, 0.05);
    func_w->SetParLimits(8, 0.043, 0.05);
    func_w->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_w->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Tensione Mid", V_m, f_min, f_max, 11);
    func_m->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_m->SetParLimits(0, 4.5, 5.5);
    func_m->SetParLimits(1, 3.2E3, 3.4E3);
    func_m->SetParLimits(2, 3.2E3, 3.4E3);
    func_m->SetParLimits(3, 3.2E3, 3.4E3);
    func_m->SetParLimits(4, 110, 130);
    func_m->SetParLimits(5, 110, 130);
    func_m->SetParLimits(6, 45, 55);
    func_m->SetParLimits(7, 0.043, 0.05);
    func_m->SetParLimits(8, 0.043, 0.05);
    func_m->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_m->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Tensione Tweeter", V_t, f_min, f_max, 11);
    func_t->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_t->SetParLimits(0, 4.5, 5.5);
    func_t->SetParLimits(1, 3.2E3, 3.4E3);
    func_t->SetParLimits(2, 3.2E3, 3.4E3);
    func_t->SetParLimits(3, 3.2E3, 3.4E3);
    func_t->SetParLimits(4, 110, 130);
    func_t->SetParLimits(5, 110, 130);
    func_t->SetParLimits(6, 45, 55);
    func_t->SetParLimits(7, 0.043, 0.05);
    func_t->SetParLimits(8, 0.043, 0.05);
    func_t->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_t->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_t->SetLineColor(kRed);

    graph_g->Fit(func_g, "N", "", fit_min, fit_max);
    graph_w->Fit(func_w, "N", "", fit_min, fit_max);
    graph_m->Fit(func_m, "N", "", fit_min, fit_max);
    graph_t->Fit(func_t, "N", "", fit_min, fit_max);

    func_g->Draw("SAME");
    func_w->Draw("SAME");
    func_m->Draw("SAME");
    func_t->Draw("SAME");

    auto leg = new TLegend(0.7, 0.5, .89, .7);
    leg->SetTextSizePixels(40);
    leg->AddEntry(func_g, "Fit Generatore", "l");
    leg->AddEntry(func_w, "Fit Woofer", "l");
    leg->AddEntry(func_m, "Fit Midrange", "l");
    leg->AddEntry(func_t, "Fit Tweeter", "l");
    leg->Draw();
    canvas->SaveAs("fig_amp.png");

    auto diff_func = new TF1("diff_func", [&](double *x, double *)
                             { return func_w->Eval(x[0]) - func_t->Eval(x[0]); }, f_min, f_max, 0);
    double cross_freq = diff_func->GetX(0, f_min, f_max);
    std::cout << "Crossover frequency = " << cross_freq << std::endl;

    double res_freq = func_m->GetMaximumX(f_min, f_max);
    std::cout << "Resonance frequency = " << res_freq << std::endl;

}