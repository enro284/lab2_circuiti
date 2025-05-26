#include <fstream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TVirtualFitter.h"
#include "TMatrixD.h"

#include "formule3.cpp" //si lo so, non si fa

void lin(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
{
    const double fit_min = 9.99E3;
    const double fit_max = 11.25E3;
    //
    // Baseline
    //
    auto graph_g_raw = new TGraphErrors(data_g, "%lg %lg");

    for (int i = 0; i < graph_g_raw->GetN(); ++i)
    {
        graph_g_raw->SetPointError(i, 0.186, 0.003);
    }
    /*
    auto c_baseline = new TCanvas();
    c_baseline->cd();
    graph_g_raw->SetMarkerStyle(20);
    graph_g_raw->SetMarkerSize(0.5);
    graph_g_raw->SetMarkerColor(kBlack);
    graph_g_raw->Draw("AP");
    */

    auto func_baseline = new TF1("Fase Generatore", "[0] + [1]*x", fit_min, fit_max);
    func_baseline->SetParameters(0, 0);
    func_baseline->SetLineColor(kRed);
    graph_g_raw->Fit(func_baseline, "RN");

    //
    // Grafici
    //
    auto graph_g = new TGraphErrors(*graph_g_raw);
    auto graph_w = new TGraphErrors(data_w, "%lg %lg");
    auto graph_m = new TGraphErrors(data_m, "%lg %lg");
    auto graph_t = new TGraphErrors(data_t, "%lg %lg");
    std::array<TGraphErrors *, 4> graphs = {graph_g, graph_w, graph_m, graph_t};

    auto mg = new TMultiGraph();

    for (auto graph : graphs)
    {
        for (int i = 0; i < graph->GetN(); ++i)
        {
            graph->SetPointError(i, 0.186, 0.002);
            double x, y;
            graph->GetPoint(i, x, y);
            double baseline = func_baseline->Eval(x);
            graph->SetPoint(i, x, y - baseline);
        }

        graph->SetMarkerStyle(20);
        graph->SetMarkerSize(0.5);
        mg->Add(graph);
    }
    mg->SetTitle("Fasi - fit lineare");
    mg->GetXaxis()->SetLimits(fit_min, fit_max);
    mg->SetMinimum(-95);
    mg->SetMaximum(+95);
    auto c_graphs = new TCanvas();
    c_graphs->cd();
    mg->Draw("AP");

    //
    // Fit
    //
    auto func_g = new TF1("Fase Generatore", "[0] + [1]*x ", fit_min, fit_max);
    func_g->SetLineColor(kRed);

    auto func_w = new TF1("Fase Woofer", "[0] + [1]*x ", fit_min, fit_max);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Fase Mid", "[0] + [1]*x", fit_min, fit_max);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Fase Tweeter", "[0] + [1]*x", fit_min, fit_max);
    func_t->SetLineColor(kPink);

    graph_g->Fit(func_g, "R");
    graph_w->Fit(func_w, "R");
    graph_m->Fit(func_m, "R");
    graph_t->Fit(func_t, "R");

    //
    // Misure
    //
    auto func_sum = new TF1("differenza di fase t-w", [=](double *x, double *par)
                            { return func_t->Eval(*x) + func_w->Eval(*x); }, fit_min, fit_max, 0);
    double cross_freq_phase = func_sum->GetX(0, fit_min, fit_max);

    double res_freq = func_m->GetX(0, fit_min, fit_max);

    double cross_freq_exp = 10686;

    double var_w = pow(func_w->GetParError(0) / func_w->GetParameter(1), 2) + pow(cross_freq_phase * func_w->GetParError(1) / func_w->GetParameter(1), 2);
    double var_m = pow(func_m->GetParError(0) / func_m->GetParameter(1), 2) + pow(cross_freq_phase * func_m->GetParError(1) / func_m->GetParameter(1), 2);
    double var_t = pow(func_t->GetParError(0) / func_t->GetParameter(1), 2) + pow(cross_freq_phase * func_t->GetParError(1) / func_t->GetParameter(1), 2);

    std::cout << "Expected crossover frequency = " << cross_freq_exp << '\n';
    std::cout << "Phase difference at expected crossover frequency = " << func_sum->Eval(cross_freq_exp) << '\n';

    std::cout << "Crossover frequency from phase = " << cross_freq_phase << "    sigma = " << sqrt(var_w + var_t) << '\n';
    std::cout << "Resonance frequency from phase = " << res_freq << "    sigma = " << sqrt(var_m) << '\n';
}

void phase(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
{
    double plot_min{1E3};
    double plot_max{30E3};
    double fit_min{8E3};
    double fit_max{16E3};

    //
    // Baseline
    //
    auto graph_g_raw = new TGraphErrors(data_g, "%lg %lg");

    for (int i = 0; i < graph_g_raw->GetN(); ++i)
    {
        graph_g_raw->SetPointError(i, 0.186, 0.003);
    }

    /*
    auto c_baseline = new TCanvas();
    c_baseline->cd();
    graph_g_raw->SetMarkerStyle(20);
    graph_g_raw->SetMarkerSize(0.5);
    graph_g_raw->SetMarkerColor(kBlack);
    graph_g_raw->Draw("AP");
    */

    auto func_baseline = new TF1("Fase Generatore", "[0] + [1]*x", plot_min, plot_max);
    func_baseline->SetParameters(0, 0);
    func_baseline->SetLineColor(kRed);
    graph_g_raw->Fit(func_baseline, "RNQ");

    //
    // Grafici
    //
    auto graph_g = new TGraphErrors(*graph_g_raw);
    auto graph_w = new TGraphErrors(data_w, "%lg %lg");
    auto graph_m = new TGraphErrors(data_m, "%lg %lg");
    auto graph_t = new TGraphErrors(data_t, "%lg %lg");
    std::array<TGraphErrors *, 4> graphs = {graph_g, graph_w, graph_m, graph_t};

    auto mg = new TMultiGraph();

    for (auto graph : graphs)
    {
        for (int i = 0; i < graph->GetN(); ++i)
        {
            graph->SetPointError(i, 0.186, 0.002);
            double x, y;
            graph->GetPoint(i, x, y);
            double baseline = func_baseline->Eval(x);
            graph->SetPoint(i, x, y - baseline);
        }

        graph->SetMarkerStyle(20);
        graph->SetMarkerSize(0.5);
        mg->Add(graph);
    }
    mg->SetTitle("Fasi - sweep completo");
    mg->GetXaxis()->SetLimits(plot_min, plot_max);
    mg->SetMinimum(-95);
    mg->SetMaximum(+95);
    auto c_graphs = new TCanvas();
    c_graphs->SetGrid();
    c_graphs->cd();
    mg->Draw("AP");

    //
    // Fit
    //
    auto func_g = new TF1("Fase Generatore", p_g, fit_min, fit_max, 5);
    func_g->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0);
    func_g->SetParLimits(0, 2E3, 4E3);
    func_g->SetParLimits(1, 50, 200);
    func_g->SetParLimits(2, 30, 70);
    func_g->SetParLimits(3, 0.02, 0.06);
    func_g->SetParLimits(4, 3E-9, 7E-9);

    auto func_w = new TF1("Fase Woofer", p_w, fit_min, fit_max, 6);
    func_w->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0);
    func_w->SetParLimits(0, 2E3, 4E3);
    func_w->SetParLimits(1, 50, 200);
    func_w->SetParLimits(2, 30, 70);
    func_w->SetParLimits(3, 0.02, 0.06);
    func_w->SetParLimits(4, 3E-9, 7E-9);

    auto func_m = new TF1("Fase Mid", p_m, fit_min, fit_max, 6);
    func_m->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0);
    func_m->SetParLimits(0, 2E3, 4E3);
    func_m->SetParLimits(1, 50, 200);
    func_m->SetParLimits(2, 30, 70);
    func_m->SetParLimits(3, 0.02, 0.06);
    func_m->SetParLimits(4, 3E-9, 7E-9);

    auto func_t = new TF1("Fase Tweeter", p_t, fit_min, fit_max, 6);
    func_t->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0);
    func_t->SetParLimits(0, 2E3, 4E3);
    func_t->SetParLimits(1, 50, 200);
    func_t->SetParLimits(2, 30, 70);
    func_t->SetParLimits(3, 0.02, 0.06);
    func_t->SetParLimits(4, 3E-9, 7E-9);

    graph_g->Fit(func_g, "RN");
    graph_w->Fit(func_w, "RN");
    graph_m->Fit(func_m, "RN");
    graph_t->Fit(func_t, "RN");

    auto func_sum = new TF1("differenza di fase t-w", [=](double *x, double *par)
                            { return func_t->Eval(*x) + func_w->Eval(*x); }, fit_min, fit_max, 0);
    double cross_freq_phase = func_sum->GetX(0, fit_min, fit_max);

    double res_freq = func_m->GetX(0, fit_min, fit_max);

    double cross_freq_exp = 10686;

    std::cout << "Expected crossover frequency = " << cross_freq_exp << '\n';
    std::cout << "Phase difference at expected crossover frequency = " << func_sum->Eval(cross_freq_exp) << '\n';
    std::cout << "Crossover frequency from phase = " << cross_freq_phase << '\n';
    std::cout << "Resonance frequency from phase = " << res_freq << '\n';

    //
    // Drawing
    //
    func_g->SetLineColor(kRed);
    func_w->SetLineColor(kBlue);
    func_m->SetLineColor(kGreen);
    func_t->SetLineColor(kPink);
    std::array<TF1 *, 4> functions = {func_g, func_w, func_m, func_t};
    for (auto function : functions)
    {
        function->SetRange(plot_min, plot_max);
        function->Draw("same");
    }
}