#include <vector>
//#include <TMath.h>
void calibNew(){
  TFile *fp = new TFile("calibE.root","RECREATE");
  std::vector<float> sigma={35.4,43.5,60.5,63.5};
  std::vector<float> energyE={356.,662.,1174.,1332.};
  std::vector<float> energy;
  
  for(unsigned int i = 0 ; i < energyE.size() ; i++){
	energy.push_back(1./sqrt(energyE[i]));
  } 
  TGraph *graph = new TGraph(energy.size(),&energy[0],&sigma[0]);
  TF1 *formula = new TF1("sigmaCalib","pol2",0.025,0.055);
  graph->Fit(formula,"R");
  graph->SetMarkerStyle(8);
  graph->Draw("ap");   

  fp->cd();
  graph->Write();
  formula->Write();
  fp->Close();
  //--------------

//TF1 *fitFunc = new TF1("fitFunc", "[0]/sqrt(x) + [1]", 300, 1400);
/*TF1 *fitFunc = new TF1("fitFunc", "[0]* x + [1]", 300, 1400);
    fitFunc->SetParNames("a", "b");

    // Set initial parameter estimates
    fitFunc->SetParameters(100, 5);

    // Fit the function to the data
    graph->Fit("pol2", "R");
    //graph->Fit(fitFunc, "R");

    // Create a canvas and draw the graph
    TCanvas *c1 = new TCanvas("c1", "Energy Resolution Fit", 800, 600);
    graph->SetTitle("NaI Energy Resolution Fit;Energy (keV);Sigma (keV)");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(1);
    graph->SetMarkerColor(kBlue);
    graph->Draw("AP"); // "A" for axis, "P" for points
    fitFunc->SetLineColor(kRed);
    fitFunc->Draw("same");

    // Add a legend
    TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.85);
    legend->AddEntry(graph, "Data Points", "p");
    legend->AddEntry(fitFunc, "Fit: #sigma(E) = a / #sqrt{E} + b", "l");
    legend->Draw();

    // Show results in console
    std::cout << "Fit Results:" << std::endl;
    std::cout << "a = " << fitFunc->GetParameter(0) << " ± " << fitFunc->GetParError(0) << std::endl;
    std::cout << "b = " << fitFunc->GetParameter(1) << " ± " << fitFunc->GetParError(1) << std::endl;

 */ //-------------

/*  gr->Draw("ap");
  gr->SetMarkerStyle(8);

  TF1 *formula = new TF1("pol3","pol3",0,1500);
  gr->Fit(formula,"R");
  
  fp->cd();
  gr->Write();
  formula->Write();
  fp->Close();*/
}
