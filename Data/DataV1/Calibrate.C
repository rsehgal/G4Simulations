#include <TF1.h>
#include <TFile.h>
#include <fstream>
#include <TH1F.h>

void Calibrate(std::string filename)
{

  TFile *fcalib = new TFile("energyCalib.root", "r");
  TF1 *ecalib   = (TF1 *)fcalib->Get("ecalib");
  fcalib->Close();

  std::string outfileName = filename + ".calibrated.root";
  TFile *dataFile         = new TFile(outfileName.c_str(), "RECREATE");

  std::ifstream infile(filename);

  double channel = 0, count = 0;

  TH1F *hist = new TH1F("ecalibHist", "ecalibHist", 2048, 0, 2048);

  while (!infile.eof()) {
    infile >> channel >> count;
    double energy = ecalib->Eval(channel);
    hist->SetBinContent(energy,count);
  }
  dataFile->cd();
  hist->Write();
  dataFile->Close();
}
