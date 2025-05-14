#include <fstream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
#include <array>

#include "formule.cpp" //si lo so, non si fa

const double f_min = 5E3;
const double f_max = 20E3;

double V_g(double *f, double *par);
double V_w(double *f, double *par);
double V_m(double *f, double *par);
double V_t(double *f, double *par);

double p_w(double *f, double *par);
double p_m(double *f, double *par);
double p_t(double *f, double *par);

void amplitude(const char *data_g = "data/amp_g.txt", const char *data_w = "data/amp_w.txt", const char *data_m = "data/amp_m.txt", const char *data_t = "data/amp_t.txt")
{
    // gStyle->SetOptFit(1111);
    auto canvas = new TCanvas();

    auto graph_w = new TGraphErrors(data_w, "%lg %lg");
    auto graph_m = new TGraphErrors(data_m, "%lg %lg");
    auto graph_t = new TGraphErrors(data_t, "%lg %lg");
    auto graph_g = new TGraphErrors(data_g, "%lg %lg");

    std::array<TGraphErrors *, 4> graphs = {graph_g, graph_w, graph_m, graph_t};

    auto mg = new TMultiGraph();

    for (auto graph : graphs)
    {
        for (int i = 0; i < graph->GetN(); ++i)
        {
            graph->SetPointError(i, 0.186, 0.002);
        }
        graph->SetMarkerStyle(20);
        graph->SetMarkerSize(0.5);
        mg->Add(graph);
    }

    mg->GetXaxis()->SetLimits(f_min, f_max);
    mg->Draw("AP");

    auto func_g = new TF1("Tensione Generatore", V_g, f_min, f_max, 6);
    func_g->SetParameters(3.3E3, 47E-3, 4.7E-9, 5., 50, 120);
    func_g->SetParLimits(0, 3.25E3, 3.35E3);
    func_g->SetParLimits(1, 0.045, 0.049);
    func_g->SetParLimits(2, 4.3E-9, 5.2E-9);
    func_g->SetParLimits(3, 4.95, 5.05);
    func_g->SetParLimits(4, 47, 53);
    func_g->SetParLimits(5, 115, 125);
    func_g->SetLineColor(kRed);
    graph_g->Fit(func_g);

    auto func_w = new TF1("Tensione Woofer", [&, func_g](double *f, double *par)
                          { return func_g->Eval(f[0]) * V_w(f, par); }, f_min, f_max, 3);
    func_w->SetParameters(3.3E3, 120, 47E-3);
    func_w->SetParLimits(0, 3E3, 3.4E3);
    func_w->SetParLimits(1, 110, 130);
    func_w->SetParLimits(2, 0.043, 0.05);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Tensione Mid", [&, func_g](double *f, double *par)
                          { return func_g->Eval(f[0]) * V_m(f, par); }, f_min, f_max, 4);
    func_m->SetParameters(3.3E3, 120, 47E-3, 4.7E-9);
    func_m->SetParLimits(0, 3E3, 3.4E3);
    func_m->SetParLimits(1, 110, 130);
    func_m->SetParLimits(2, 0.043, 0.05);
    func_m->SetParLimits(3, 4.3E-9, 5.2E-9);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Tensione Tweeter", [&, func_g](double *f, double *par)
                          { return func_g->Eval(f[0]) * V_t(f, par); }, f_min, f_max, 2);
    func_t->SetParameters(3.3E3, 4.7E-9);
    func_t->SetParLimits(0, 3E3, 3.4E3);
    func_t->SetParLimits(1, 4.3E-9, 5.2E-9);
    func_t->SetLineColor(kRed);

    graph_w->Fit(func_w);
    graph_m->Fit(func_m);
    graph_t->Fit(func_t);

    auto diff_func = new TF1("diff_func", [&](double *x, double *)
                             { return func_w->Eval(x[0]) - func_t->Eval(x[0]); }, f_min, f_max, 0);
    double cross_freq = diff_func->GetX(0, f_min, f_max);
    std::cout << "Crossover frequency = " << cross_freq << std::endl;

    
    double res_freq = func_m->GetMaximumX(f_min, f_max);
    std::cout << "Resonance frequency = " << res_freq << std::endl;
}

void phase(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
{
    // gStyle->SetOptFit(1111);

    /*
    //  CALCOLO BASELINE
    */
    auto c_baseline = new TCanvas();
    c_baseline->cd();

    auto graph_g = new TGraphErrors(data_g, "%lg %lg");

    for (int i = 0; i < graph_g->GetN(); ++i)
    {
        graph_g->SetPointError(i, 0.186, 0.003);
    }

    graph_g->SetMarkerStyle(20);
    graph_g->SetMarkerSize(0.5);
    graph_g->SetMarkerColor(kBlack);
    graph_g->Draw("AP");

    auto func_g = new TF1("Fase Generatore", "[0] + [1]*x", f_min, f_max);
    func_g->SetParameters(0, 0);
    func_g->SetLineColor(kRed);
    graph_g->Fit(func_g, "R");

    /*
    //  GRAFICI FASE
    */
    auto c_phase = new TCanvas();
    c_phase->cd();

    auto graph_g_flat = new TGraphErrors(*graph_g);
    auto graph_w = new TGraphErrors(data_w, "%lg %lg");
    auto graph_m = new TGraphErrors(data_m, "%lg %lg");
    auto graph_t = new TGraphErrors(data_t, "%lg %lg");

    std::array<TGraphErrors *, 4> graphs = {graph_g_flat, graph_w, graph_m, graph_t};

    auto mg = new TMultiGraph();

    for (auto graph : graphs)
    {
        for (int i = 0; i < graph->GetN(); ++i)
        {
            graph->SetPointError(i, 0., 0.003);

            // subtract baseline
            double x, y;
            graph->GetPoint(i, x, y);
            double baseline = func_g->Eval(x);
            graph->SetPoint(i, x, y - baseline);
        }
        graph->SetMarkerStyle(20);
        graph->SetMarkerSize(0.5);
        mg->Add(graph);
    }

    mg->GetXaxis()->SetLimits(f_min, f_max);
    mg->SetMinimum(-95);
    mg->SetMaximum(+95);

    mg->Draw("AP");

    auto func_w = new TF1("Fase Woofer", p_w, f_min, f_max, 3);
    func_w->SetParameters(3.3E3, 47E-3);
    func_w->SetParLimits(0, 3.3E3, 3.4E3);
    func_w->SetParLimits(1, 110, 130);
    func_w->SetParLimits(2, 0.043, 0.05);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Fase Mid", p_m, f_min, f_max, 4);
    func_m->SetParameters(3.3E3, 47E-3, 4.7E-9);
    func_m->SetParLimits(0, 3.3E3, 3.4E3);
    func_m->SetParLimits(1, 110, 130);
    func_m->SetParLimits(2, 0.04, 0.05);
    func_m->SetParLimits(3, 4.3E-9, 5.2E-9);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Fase Tweeter", p_t, f_min, f_max, 2);
    func_t->SetParameters(3.3E3, 4.7E-9);
    func_t->SetParLimits(0, 3.3E3, 3.4E3);
    func_t->SetParLimits(1, 4.3E-9, 5.2E-9);
    func_t->SetLineColor(kPink);

    graph_g_flat->Fit(func_g); // posso fittare con la stessa o devo cambiare func?
    graph_w->Fit(func_w);
    graph_m->Fit(func_m);
    graph_t->Fit(func_t);

    double cross_freqW = func_w->GetX(-45, f_min, f_max);
    double cross_freqT = func_t->GetX(45, f_min, f_max);
    double res_freq = func_m->GetX(0, f_min, f_max);

    std::cout << "Crossover frequency (Woofer) = " << cross_freqW << std::endl;
    std::cout << "Crossover frequency (Tweeter) = " << cross_freqT << std::endl;
    std::cout << "Resonance frequency = " << res_freq << std::endl;
}