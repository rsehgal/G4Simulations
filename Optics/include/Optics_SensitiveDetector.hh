#ifndef OPTICS_SENSITIVEDETECTOR_HH
#define OPTICS_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "Optics_Hit.h"
#include "G4THitsCollection.hh"
#include "HitCollections.h"

class G4HCofThisEvent;

class Optics_SensitiveDetector : public G4VSensitiveDetector {

public:
  NaiHitCollection *fHitCollection;

public:
  Optics_SensitiveDetector(const G4String &name, const G4String &collName);
  virtual ~Optics_SensitiveDetector();
  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hce);
};

#endif
