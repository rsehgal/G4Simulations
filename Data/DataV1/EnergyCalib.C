#include <vector>

void EnergyCalib(){
  TFile *fp = new TFile("energyCalib.root","RECREATE");
  std::vector<float> energy={356., 662., 1174., 1332.};
  std::vector<float> channel={255., 511., 758., 853.};
  TGraph *gr = new TGraph(channel.size(),&channel[0],&energy[0]);
  gr->Draw("ap");
  gr->SetMarkerStyle(8);

  TF1 *formula = new TF1("ecalib","pol1",0,1500);
  gr->Fit(formula,"R");
  
  fp->cd();
  gr->Write();
  formula->Write();
  fp->Close();
}
