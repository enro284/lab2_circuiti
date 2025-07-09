#include <fstream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TVirtualFitter.h"
#include "TMatrixD.h"
#include "TLegend.h"
#include "TLine.h"

#include "formule3.cpp" //si lo so, non si fa

double cross_freq_phase;
double res_freq;

struct Plot
{
    TMultiGraph *mg;
    std::array<TF1 *, 4> functions;

    void draw(TPad *pad)
    {
        auto legend = new TLegend(0.6, 0.65, .89, .89);
        legend->SetTextSizePixels(20);

        pad->cd();
        pad->SetGridx();
        pad->SetGridy();

        mg->Draw("APE");
        mg->GetYaxis()->SetTitle("Fase (#circ)");
        mg->GetXaxis()->SetTitle("Frequenza (Hz)");
        mg->GetXaxis()->SetMaxDigits(3);
        mg->GetXaxis()->SetNdivisions(520);
        for (auto func : functions)
        {
            func->Draw("same");
            legend->AddEntry(func);
        }
        legend->AddEntry(mg, "Dati sperimentali", "p");
        legend->Draw();
    }
};

Plot lin_fit(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
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
    graph_g_raw->Draw("APE");
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
        graph->SetMarkerSize(1);
        mg->Add(graph);
    }
    auto c_graphs = new TCanvas();
    c_graphs->cd();
    mg->SetTitle("Fasi - fit lineare");
    mg->GetXaxis()->SetLimits(fit_min, fit_max);
    mg->SetMinimum(-55);
    mg->SetMaximum(+55);
    mg->Draw("APE");

    //
    // Fit
    //
    auto func_g = new TF1("Fase Generatore", "[0] + [1]*x ", fit_min, fit_max);
    func_g->SetNameTitle("Fit Generatore", "Fit Generatore");
    func_g->SetLineColor(kOrange);

    auto func_w = new TF1("Fase Woofer", "[0] + [1]*x ", fit_min, fit_max);
    func_w->SetNameTitle("Fit Woofer", "Fit Woofer");
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Fase Mid", "[0] + [1]*x", fit_min, fit_max);
    func_m->SetNameTitle("Fit Midrange", "Fit Midrange");
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Fase Tweeter", "[0] + [1]*x", fit_min, fit_max);
    func_t->SetNameTitle("Fit Tweeter", "Fit Tweeter");
    func_t->SetLineColor(kRed);

    graph_g->Fit(func_g, "R");
    graph_w->Fit(func_w, "R");
    graph_m->Fit(func_m, "R");
    graph_t->Fit(func_t, "R");

    //
    // Misure
    //
    auto func_sum = new TF1("somma fasi t-w", [=](double *x, double *par)
                            { return func_t->Eval(*x) + func_w->Eval(*x); }, fit_min, fit_max, 0);
    double cross_freq_phase = func_sum->GetX(0, fit_min, fit_max);
    double res_freq = func_m->GetX(0, fit_min, fit_max);

    double var_w_x = pow(func_w->GetParError(0) / func_w->GetParameter(1), 2) + pow(cross_freq_phase * func_w->GetParError(1) / func_w->GetParameter(1), 2);
    double var_m_x = pow(func_m->GetParError(0) / func_m->GetParameter(1), 2) + pow(cross_freq_phase * func_m->GetParError(1) / func_m->GetParameter(1), 2);
    double var_t_x = pow(func_t->GetParError(0) / func_t->GetParameter(1), 2) + pow(cross_freq_phase * func_t->GetParError(1) / func_t->GetParameter(1), 2);
    double sigma_cross_freq_phase = sqrt(var_w_x + var_t_x);

    std::cout << "Crossover frequency from phase = " << cross_freq_phase << "    sigma = " << sigma_cross_freq_phase << '\n';
    std::cout << "Resonance frequency from phase = " << res_freq << "    sigma = " << sqrt(var_m_x) << '\n';

    double phase_diff = func_t->Eval(cross_freq_phase) - func_w->Eval(cross_freq_phase);
    double var_t_y = pow(func_t->GetParError(0), 2) + pow(cross_freq_phase * func_t->GetParError(1), 2) + pow(func_t->GetParameter(1) * sigma_cross_freq_phase, 2);
    double var_w_y = pow(func_w->GetParError(0), 2) + pow(cross_freq_phase * func_w->GetParError(1), 2) + pow(func_w->GetParameter(1) * sigma_cross_freq_phase, 2);
    double sigma_phase_diff = sqrt(var_t_y + var_w_y);
    std::cout << "Phase difference at crossover = " << phase_diff << "\t sigma = " << sigma_phase_diff << '\n';

    return {mg, {func_g, func_w, func_m, func_t}};
}

Plot func_fit(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
{
    double plot_min{1E3};
    double plot_max{50E3};
    double fit_min{1E3};
    double fit_max{30E3};

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
        graph->SetMarkerSize(1);
        mg->Add(graph);
    }

    auto c_graphs = new TCanvas();
    c_graphs->SetGrid();
    c_graphs->cd();

    mg->SetTitle("Fasi - sweep completo");
    mg->GetXaxis()->SetLimits(plot_min, plot_max);
    mg->SetMinimum(-95);
    mg->SetMaximum(+95);
    mg->Draw("AP");

    //
    // Fit
    //
    auto func_g = new TF1("Fase Generatore", "[0]", fit_min, fit_max);
    func_g->SetNameTitle("Fit Generatore", "Fit Generatore");

    auto func_w = new TF1("Fase Woofer", p_w, fit_min, fit_max, 7);
    func_w->SetNameTitle("Fit Woofer", "Fit Woofer");
    func_w->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0, 4E4);
    func_w->SetParLimits(0, 2E3, 4E3);
    func_w->SetParLimits(1, 50, 200);
    func_w->SetParLimits(2, 30, 70);
    func_w->SetParLimits(3, 0.02, 0.06);
    func_w->SetParLimits(4, 3E-9, 7E-9);
    func_w->FixParameter(6, 4E4);

    auto func_m = new TF1("Fase Mid", p_m, fit_min, fit_max, 7);
    func_m->SetNameTitle("Fit Midrange", "Fit Midrange");

    func_m->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0, 4E4);
    func_m->SetParLimits(0, 2E3, 4E3);
    func_m->SetParLimits(1, 50, 200);
    func_m->SetParLimits(2, 30, 70);
    func_m->SetParLimits(3, 0.02, 0.06);
    func_m->SetParLimits(4, 3E-9, 7E-9);

    auto func_t = new TF1("Fase Tweeter", p_t, fit_min, fit_max, 7);
    func_t->SetNameTitle("Fit Tweeter", "Fit Tweeter");
    func_t->SetParameters(3.3E3, 120, 50, 47E-3, 4.7E-9, 0, 4E4);
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
    cross_freq_phase = func_sum->GetX(0, fit_min, fit_max);

    res_freq = func_m->GetX(0, fit_min, fit_max);

    double cross_freq_exp = 10686;

    std::cout << "Expected crossover frequency = " << cross_freq_exp << '\n';
    std::cout << "Phase difference at expected crossover frequency = " << func_sum->Eval(cross_freq_exp) << '\n';
    std::cout << "Crossover frequency from phase = " << cross_freq_phase << '\n';
    std::cout << "Resonance frequency from phase = " << res_freq << '\n';

    //
    // Drawing
    //
    func_g->SetLineColor(kOrange);
    func_w->SetLineColor(kBlue);
    func_m->SetLineColor(kGreen);
    func_t->SetLineColor(kRed);
    std::array<TF1 *, 4> functions = {func_g, func_w, func_m, func_t};
    for (auto function : functions)
    {
        function->SetRange(plot_min, plot_max);
        function->Draw("same");
    }

    return {mg, {func_g, func_w, func_m, func_t}};
}

void phase(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
{
    auto c = new TCanvas("Grafici fase", "Grafici fase", 2400, 1000);
    c->Draw();

    TPad *p1 = new TPad("p1", "p1", 0, 0, 0.58, 1);
    TPad *p2 = new TPad("p2", "p2", 0.58, 0, 1, 1);
    p1->Draw();
    p2->Draw();
    func_fit().draw(p1);
    auto line_c = new TLine(cross_freq_phase, 41, cross_freq_phase, -95);
    auto line_r = new TLine(res_freq, 0, res_freq, -95);
    line_c->Draw();
    line_r->Draw();

    lin_fit().draw(p2);

    c->SaveAs("fig_fase.png");
}