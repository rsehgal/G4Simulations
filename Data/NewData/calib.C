#include <vector>

void calib(){
  TFile *fp = new TFile("calib.root","RECREATE");
  std::vector<float> sigma={35.4,43.5,60.5,63.5};
  std::vector<float> energy={356.,662.,1174.,1332.};
  TGraph *gr = new TGraph(energy.size(),&energy[0],&sigma[0]);
  gr->Draw("ap");
  gr->SetMarkerStyle(8);

  TF1 *formula = new TF1("pol3","pol3",0,1500);
  gr->Fit(formula,"R");
  
  fp->cd();
  gr->Write();
  formula->Write();
  fp->Close();
}
