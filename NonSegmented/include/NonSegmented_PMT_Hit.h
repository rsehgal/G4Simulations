#ifndef NONSEGMENTED_PMT_HIT_HH
#define NONSEGMENTED_PMT_HIT_HH

#include "G4VHit.hh"
#include "vector"

class NonSegmented_PMT_Hit : public G4VHit {
    unsigned int pmtID;
    double photonArrivalTime;
public:
    NonSegmented_PMT_Hit();
    virtual ~NonSegmented_PMT_Hit();
    unsigned int GetPmtID() const;
    double GetPhotonArrivalTime() const;
    void Set(unsigned int pmtid,double pat);
    void Print();
};

#endif
