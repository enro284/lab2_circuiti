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

double V_g(double *f, double *par);
double V_w(double *f, double *par);
double V_m(double *f, double *par);
double V_t(double *f, double *par);

double p_w(double *f, double *par);
double p_m(double *f, double *par);
double p_t(double *f, double *par);

void amplitude(const char *data_g = "data/amp_g.txt", const char *data_w = "data/amp_w.txt", const char *data_m = "data/amp_m.txt", const char *data_t = "data/amp_t.txt")
{

    auto canvas = new TCanvas("canvas", "Amplitude", 2000, 1000);

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

    mg->Draw("AP");

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

    auto leg = new TLegend(0.6, 0.7, .89, .89);
    leg->AddEntry(func_g, "Fit Generatore", "l");
    leg->AddEntry(func_w, "Fit Woofer", "l");
    leg->AddEntry(func_m, "Fit Midrange", "l");
    leg->AddEntry(func_t, "Fit Tweeter", "l");
    leg->Draw();

    auto diff_func = new TF1("diff_func", [&](double *x, double *)
                             { return func_w->Eval(x[0]) - func_t->Eval(x[0]); }, f_min, f_max, 0);
    double cross_freq = diff_func->GetX(0, f_min, f_max);
    std::cout << "Crossover frequency = " << cross_freq << std::endl;

    double res_freq = func_m->GetMaximumX(f_min, f_max);
    std::cout << "Resonance frequency = " << res_freq << std::endl;

    double q = sqrt(46.8E-3 / 4.76E-9) / 3287;
    double sigma_q = q * ((2 / 3287) + (0.25 / 46.8) + (0.025 / 4.76));
    std::cout << "Midrange Q factor expected = " << q << "\t sigma = " << sigma_q << '\n';

    double mid_half_power = func_m->Eval(res_freq) / sqrt(2);
    double w_1 = func_m->GetX(mid_half_power, 5E3, 10E3);
    double w_2 = func_m->GetX(mid_half_power, 15E3, 20E3);
    double bandwidth = w_2 - w_1;
    q = res_freq / bandwidth;

    double rel_err_res_freq = 160 / res_freq;
    double rel_err_bandwidth = 0.05 + 0.09; // sigma_R/R + sigma_L/L
    sigma_q = q * sqrt(pow(rel_err_bandwidth, 2) + pow(rel_err_res_freq, 2));
    std::cout << "Midrange Q factor measured from bandwidth = " << q << "\t sigma = " << sigma_q << '\n';
}

void phase(const char *data_g = "data/phase_g.txt", const char *data_w = "data/phase_w.txt", const char *data_m = "data/phase_m.txt", const char *data_t = "data/phase_t.txt")
{
    gStyle->SetOptFit(1111);
    auto c1 = new TCanvas();
    c1->cd();
    auto graph_g = new TGraphErrors(data_g, "%lg %lg");
    auto graph_w = new TGraphErrors(data_w, "%lg %lg");
    auto graph_m = new TGraphErrors(data_m, "%lg %lg");
    auto graph_t = new TGraphErrors(data_t, "%lg %lg");
    auto graph_gFlat = new TGraphErrors(graph_g->GetN()); // si può fare meglio?

    for (int i = 0; i < graph_g->GetN(); ++i)
    {
        double x, y;
        graph_g->GetPoint(i, x, y);
        graph_gFlat->SetPoint(i, x, y);
        graph_g->SetPointError(i, 0.186, 0.003);
        graph_gFlat->GetPoint(i, x, y);
        graph_gFlat->SetPointError(i, 0., 0.003);
    }

    for (int i = 0; i < graph_w->GetN(); ++i)
    {
        double x, y;
        graph_w->GetPoint(i, x, y);
        graph_w->SetPointError(i, 0., 0.003);
    }

    for (int i = 0; i < graph_m->GetN(); ++i)
    {
        double x, y;
        graph_m->GetPoint(i, x, y);
        graph_m->SetPointError(i, 0., 0.003);
    }
    for (int i = 0; i < graph_t->GetN(); ++i)
    {
        double x, y;
        graph_t->GetPoint(i, x, y);
        graph_t->SetPointError(i, 0., 0.003);
    }

    graph_g->SetMarkerStyle(20);
    graph_g->SetMarkerSize(0.5);
    graph_g->SetMarkerColor(kBlack);
    graph_g->Draw("AP");

    auto func_g = new TF1("Fase Generatore", "[0] + [1]*x", f_min, f_max);
    func_g->SetParameters(0, 0);
    func_g->SetLineColor(kRed);
    graph_g->Fit(func_g, "R");

    auto c2 = new TCanvas();
    c2->cd();

    // Subtract the baseline (func_g) from each point in the graphs
    auto subtractBaseline = [&](TGraphErrors *graph)
    {
        for (int i = 0; i < graph->GetN(); ++i)
        {
            double x, y;
            graph->GetPoint(i, x, y);
            double baseline = func_g->Eval(x);
            graph->SetPoint(i, x, y - baseline);
        }
    };

    subtractBaseline(graph_w);
    subtractBaseline(graph_m);
    subtractBaseline(graph_t);
    subtractBaseline(graph_gFlat);

    auto mg = new TMultiGraph();
    mg->Add(graph_gFlat);
    mg->Add(graph_w);
    mg->Add(graph_m);
    mg->Add(graph_t);

    mg->GetXaxis()->SetLimits(f_min, f_max);
    mg->SetMinimum(-95);
    mg->SetMaximum(+95);
    graph_gFlat->SetMarkerSize(0.5);
    graph_gFlat->SetMarkerStyle(20);
    graph_w->SetMarkerStyle(20);
    graph_w->SetMarkerSize(0.5);
    graph_m->SetMarkerStyle(20);
    graph_m->SetMarkerSize(0.5);
    graph_t->SetMarkerStyle(20);
    graph_t->SetMarkerSize(0.5);

    mg->GetXaxis()->SetTitle("Frequenza (Hz)");
    mg->GetYaxis()->SetTitle("Ampiezza (V)");
    mg->SetTitle("Porcodio");
    mg->Draw("AP");
    gPad->SetGrid(1, 1);
    gPad->SetGridx(20);
    gPad->SetGridy(20);

    auto func_w = new TF1("Fase Woofer", p_w, f_min, f_max, 11);
    func_w->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_w->SetParLimits(0, 4.5, 5.5);
    func_w->SetParLimits(1, 3E3, 3.4E3);
    func_w->SetParLimits(2, 3E3, 3.4E3);
    func_w->SetParLimits(3, 3E3, 3.4E3);
    func_w->SetParLimits(4, 110, 130);
    func_w->SetParLimits(5, 110, 130);
    func_w->SetParLimits(6, 45, 55);
    func_w->SetParLimits(7, 0.043, 0.05);
    func_w->SetParLimits(8, 0.043, 0.05);
    func_w->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_w->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_w->SetLineColor(kBlue);

    auto func_m = new TF1("Fase Mid", p_m, f_min, f_max, 11);
    func_m->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_m->SetParLimits(0, 4.5, 5.5);
    func_m->SetParLimits(1, 3E3, 3.4E3);
    func_m->SetParLimits(2, 3E3, 3.4E3);
    func_m->SetParLimits(3, 3E3, 3.4E3);
    func_m->SetParLimits(4, 110, 130);
    func_m->SetParLimits(5, 110, 130);
    func_m->SetParLimits(6, 45, 55);
    func_m->SetParLimits(7, 0.043, 0.05);
    func_m->SetParLimits(8, 0.043, 0.05);
    func_m->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_m->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_m->SetLineColor(kGreen);

    auto func_t = new TF1("Fase Tweeter", p_t, f_min, f_max, 11);
    func_t->SetParameters(5., 3.3E3, 3.3E3, 3.3E3, 120, 120, 50, 47E-3, 47E-3, 4.7E-9, 4.7E-9);
    func_t->SetParLimits(0, 4.5, 5.5);
    func_t->SetParLimits(1, 3E3, 3.4E3);
    func_t->SetParLimits(2, 3E3, 3.4E3);
    func_t->SetParLimits(3, 3E3, 3.4E3);
    func_t->SetParLimits(4, 110, 130);
    func_t->SetParLimits(5, 110, 130);
    func_t->SetParLimits(6, 45, 55);
    func_t->SetParLimits(7, 0.043, 0.05);
    func_t->SetParLimits(8, 0.043, 0.05);
    func_t->SetParLimits(9, 4.3E-9, 5.2E-9);
    func_t->SetParLimits(10, 4.3E-9, 5.2E-9);
    func_t->SetLineColor(kMagenta);

    graph_gFlat->Fit(func_g); // posso fittare con la stessa o devo cambiare func?
    graph_w->Fit(func_w);
    graph_m->Fit(func_m);
    graph_t->Fit(func_t);

    double cross_freq = 10686;
    double res_freq = func_m->GetX(0, f_min, f_max);

    double phase_diff = func_t->Eval(cross_freq) - func_w->Eval(cross_freq);

    std::cout << "Phase difference = " << phase_diff << std::endl;
    std::cout << "Crossover frequency = " << cross_freq << std::endl;
    std::cout << "Resonance frequency = " << res_freq << std::endl;
}
void tempi()
{
    auto canvas = new TCanvas();

    auto g_g = new TGraph("tempi_1.txt", "%lg %lg");
    auto g_w = new TGraph("tempi_2.txt", "%lg %lg");
    auto g_m = new TGraph("tempi_3.txt", "%lg %lg");
    auto g_t = new TGraph("tempi_4.txt", "%lg %lg");

    auto mg = new TMultiGraph();
    mg->Add(g_g);
    mg->Add(g_w);
    mg->Add(g_m);
    mg->Add(g_t);

    mg->Draw("AP");
}

void voltage_sigma()
{

    // Parametri istogramma
    const int nBins = 80;
    const double xMin = 4.995;
    const double xMax = 5.02;

    // Istogrammi
    auto h1 = new TH1F("h1", "100kHz; V; Conteggi", nBins, xMin, xMax);
    auto h2 = new TH1F("h2", "250kHz; V; Conteggi", nBins, xMin, xMax);

    // Leggi primo file
    std::ifstream file1("voltage_100kHz.txt");

    double x;
    while (file1 >> x)
    {
        h1->Fill(x);
    }
    file1.close();

    // Leggi secondo file
    std::ifstream file2("voltage_250kHz.txt");
    while (file2 >> x)
    {
        h2->Fill(x);
    }
    file2.close();

    // Crea canvas diviso in due
    TCanvas *c = new TCanvas("c", "c", 1200, 600);
    c->Divide(2, 1);

    // Primo istogramma con fit
    c->cd(1);
    gStyle->SetOptFit(1111); // Mostra box statistiche completo
    h1->SetLineColor(kBlue);
    h1->Draw();
    h1->Fit("gaus"); // Mostra info fit
    TF1 *f1 = h1->GetFunction("gaus");
    double sigma1 = f1->GetParameter(2);
    std::cout << "100kHz sigma: " << sigma1 << std::endl;

    // Secondo istogramma con fit
    c->cd(2);
    gStyle->SetOptFit(1111);
    h2->SetLineColor(kRed);
    h2->Draw();
    h2->Fit("gaus");
    TF1 *f2 = h2->GetFunction("gaus");
    double sigma2 = f2->GetParameter(2);
    std::cout << "250kHz sigma: " << sigma2 << std::endl;
}

void amplitude_sigma()
{

    const int nBins = 30;
    const double xMin = 4.989;
    const double xMax = 4.992;

    // Istogrammi
    auto h1 = new TH1F("h1", "20kHz; V; Conteggi", nBins, xMin, xMax);
    auto h2 = new TH1F("h2", "50kHz; V; Conteggi", nBins, xMin, xMax);

    // Leggi primo file
    std::ifstream file1("amplitude_20kHz.txt");

    double x;
    while (file1 >> x)
    {
        h1->Fill(x);
    }
    file1.close();

    // Leggi secondo file
    std::ifstream file2("amplitude_50kHz.txt");
    while (file2 >> x)
    {
        h2->Fill(x);
    }
    file2.close();

    // Crea canvas diviso in due
    TCanvas *c = new TCanvas("c", "c", 1200, 600);
    c->Divide(2, 1);

    // Primo istogramma con fit
    c->cd(1);
    gStyle->SetOptFit(1111); // Mostra box statistiche completo
    h1->SetLineColor(kBlue);
    h1->Draw();
    h1->Fit("gaus"); // Mostra info fit
    TF1 *f1 = h1->GetFunction("gaus");
    double sigma1 = f1->GetParameter(2);
    std::cout << "20kHz sigma: " << sigma1 << std::endl;

    // Secondo istogramma con fit
    c->cd(2);
    gStyle->SetOptFit(1111);
    h2->SetLineColor(kRed);
    h2->Draw();
    h2->Fit("gaus");
    TF1 *f2 = h2->GetFunction("gaus");
    double sigma2 = f2->GetParameter(2);
    std::cout << "50kHz sigma: " << sigma2 << std::endl;
}

void phase_sigma(const char *phase1, const char *phase2, const char *phase3, const char *phase4, const char *phase5, const char *phase6)
{
    gStyle->SetOptFit(1111);

    // Parametri istogramma
    const int nBins = 30;
    const double xMin = 0;
    const double xMax = 20;

    // Crea un array di istogrammi
    TH1F *histograms[6];
    histograms[0] = new TH1F("h1", "1kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[1] = new TH1F("h2", "10kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[2] = new TH1F("h3", "20kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[3] = new TH1F("h4", "30kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[4] = new TH1F("h5", "40kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[5] = new TH1F("h6", "50kHz; V; Conteggi", nBins, xMin, xMax);

    // Leggi tutti i file e riempi gli istogrammi in un ciclo
    const char *fileNames[] = {phase1, phase2, phase3, phase4, phase5, phase6};
    auto fillHistogram = [](TH1F *hist, const char *fileName)
    {
        std::ifstream file(fileName);
        double x;
        while (file >> x)
        {
            hist->Fill(x);
        }
        file.close();
    };

    for (int i = 0; i < 6; ++i)
    {
        fillHistogram(histograms[i], fileNames[i]);
    }

    TCanvas *c = new TCanvas("c", "c", 1200, 600);
    c->Divide(3, 2);

    for (int i = 0; i < 6; i++)
    {
        c->cd(i + 1); // I pad iniziano da 1
        histograms[i]->SetLineColor(kBlue);
        histograms[i]->Draw();
        histograms[i]->Fit("gaus");
    }
    // Array con i valori sull'asse x
    double xValues[6] = {1E3, 10E3, 20E3, 30E3, 40E3};

    // Calcola le deviazioni standard e crea il grafico
    double yValues[5];
    double yErrors[5];
    double errorMean = 0;
    for (int i = 0; i < 5; ++i)
    {
        yValues[i] = histograms[i]->GetStdDev();
        yErrors[i] = histograms[i]->GetStdDevError();
        errorMean += yValues[i];
    }
    errorMean /= 6;

    auto graph = new TGraphErrors(5, xValues, yValues, nullptr, yErrors);
    auto f = new TF1("f", "[0] + [1]*x", xMin, xMax);
    graph->SetTitle("Standard Deviation vs Frequency;Frequency (Hz);Standard Deviation");
    graph->SetMarkerStyle(21);
    graph->SetMarkerSize(1);
    graph->SetMarkerColor(kRed);

    // Disegna il grafico
    TCanvas *c2 = new TCanvas("c2", "Standard Deviation Graph", 800, 600);
    c2->cd();
    graph->Draw("AP");
    f->SetParameters(0, 0);
    graph->Fit(f);

    std::cout << "Mean of Std: " << errorMean << std::endl;
}

void amplitude_sigma(const char *amp1, const char *amp2, const char *amp3, const char *amp4, const char *amp5, const char *amp6)
{
    gStyle->SetOptFit(1111);

    // Parametri istogramma
    const int nBins = 30;
    const double xMin = 0;
    const double xMax = 20;

    // Crea un array di istogrammi
    TH1F *histograms[6];
    histograms[0] = new TH1F("h1", "1kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[1] = new TH1F("h2", "10kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[2] = new TH1F("h3", "20kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[3] = new TH1F("h4", "30kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[4] = new TH1F("h5", "40kHz; V; Conteggi", nBins, xMin, xMax);
    histograms[5] = new TH1F("h6", "50kHz; V; Conteggi", nBins, xMin, xMax);

    // Leggi tutti i file e riempi gli istogrammi in un ciclo
    const char *fileNames[] = {amp1, amp2, amp3, amp4, amp5, amp6};
    auto fillHistogram = [](TH1F *hist, const char *fileName)
    {
        std::ifstream file(fileName);
        double x;
        while (file >> x)
        {
            hist->Fill(x);
        }
        file.close();
    };

    for (int i = 0; i < 6; ++i)
    {
        fillHistogram(histograms[i], fileNames[i]);
    }

    TCanvas *c = new TCanvas("c", "c", 1200, 600);
    c->Divide(3, 2);

    for (int i = 0; i < 6; i++)
    {
        c->cd(i + 1); // I pad iniziano da 1
        histograms[i]->SetLineColor(kBlue);
        histograms[i]->Draw();
        histograms[i]->Fit("gaus");
    }
    // Array con i valori sull'asse x
    double xValues[6] = {1E3, 10E3, 20E3, 30E3, 40E3, 50E3};

    // Calcola le deviazioni standard e crea il grafico
    double yValues[6];
    double yErrors[6];
    double errorMean = 0;
    for (int i = 0; i < 6; ++i)
    {
        yValues[i] = histograms[i]->GetStdDev();
        yErrors[i] = histograms[i]->GetStdDevError();
        errorMean += yValues[i];
    }
    errorMean /= 6;

    auto graph = new TGraphErrors(6, xValues, yValues, nullptr, yErrors);
    auto f = new TF1("f", "[0] + [1]*x", xMin, xMax);
    graph->SetTitle("Standard Deviation vs Frequency;Frequency (Hz);Standard Deviation");
    graph->SetMarkerStyle(21);
    graph->SetMarkerSize(1);
    graph->SetMarkerColor(kRed);

    // Disegna il grafico
    TCanvas *c2 = new TCanvas("c2", "Standard Deviation Graph", 800, 600);
    c2->cd();
    graph->Draw("AP");
    f->SetParameters(0, 0);
    graph->Fit(f);

    std::cout << "Mean of Std: " << errorMean << std::endl;
}
