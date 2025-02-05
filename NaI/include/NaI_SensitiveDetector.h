#ifndef NAI_SENSITIVEDETECTOR_HH
#define NAI_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class G4HCofThisEvent;

class NaI_SensitiveDetector : public G4VSensitiveDetector {

  double fEDep;

public:
  NaI_SensitiveDetector(const G4String &name);
  virtual ~NaI_SensitiveDetector();

  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hce);
};

#endif
