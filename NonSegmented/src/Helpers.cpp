#include "Helpers.h"
#include "TH1F.h"
double GetTiming(std::vector<double> photonArrivalTimeVec)
{

  TH1F *hist = new TH1F("hist", "hist", 1000, 0, 50);
  for (unsigned int i = 0; i < photonArrivalTimeVec.size(); i++) {
    hist->Fill(photonArrivalTimeVec[i]);
  }

  double quantile = 0.10; // 10% quantile
  double qvalue   = 0.0;
  hist->GetQuantiles(1, &qvalue, &quantile);
  delete hist;
  return qvalue;
}
