#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include <TFile.h>

void fitCs137() {
    // Load Histogram (Replace with your actual file)
    TFile *f = new TFile("cs137.org.root");
    TH1F *hist_exp = (TH1F*)f->Get("Data");
    hist_exp->Scale(1./hist_exp->Integral());

    // Define Improved Crystal Ball function with background
    TF1 *cbFit = new TF1("cbFit",
        "[0] * ( (([4]/fabs([3]))^([4])) * exp(-0.5 * ([3] * [3])) / (([4]/fabs([3])) - fabs([3]) - (x-[1])/[2])^([4]) * (x < [1] - [3] * [2]) + exp(-0.5 * ((x - [1])/[2])^2) * (x >= [1] - [3] * [2]) ) + [5] + [6]*x",
        500, 1150);

    // Set initial parameters
    cbFit->SetParameters(100, 631.8, 42.8, 1.5, 2.5, 10, -0.02);

    // Fit histogram
    //hist_exp->Fit(cbFit, "R");

    // Draw results
    TCanvas *c1 = new TCanvas("c1", "Improved Crystal Ball Fit", 800, 600);
    hist_exp->Draw();
    //cbFit->Draw("same");
}

