#include <fstream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TStyle.h"

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
