#include "NonSegmented_PMT_Hit.h"

NonSegmented_PMT_Hit::NonSegmented_PMT_Hit() {}

NonSegmented_PMT_Hit::~NonSegmented_PMT_Hit() {}

unsigned int NonSegmented_PMT_Hit::GetPmtID() const
{
  return pmtID;
}

double NonSegmented_PMT_Hit::GetPhotonArrivalTime() const
{
  return photonArrivalTime;
}

void NonSegmented_PMT_Hit::Set(unsigned int pmtid, double pat)
{
  pmtID                  = pmtid;
  photonArrivalTime = pat;
}

void NonSegmented_PMT_Hit::Print(){
std::cout << "(" << pmtID <<" , "<< photonArrivalTime << ")" << std::endl;
}
