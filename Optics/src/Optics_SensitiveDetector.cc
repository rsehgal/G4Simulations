#include "Optics_SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"
#include "CLHEP/Random/RandGauss.h"
Optics_SensitiveDetector::Optics_SensitiveDetector(const G4String &name, const G4String &collName)
    : G4VSensitiveDetector(name), fHitCollection(nullptr)
{
  collectionName.insert(collName);
}

Optics_SensitiveDetector::~Optics_SensitiveDetector() {}

void Optics_SensitiveDetector::Initialize(G4HCofThisEvent *hce)
{
  //  hce->clear();
  fHitCollection = new NaiHitCollection(SensitiveDetectorName, collectionName[0]);
  // G4int hcID     = G4SDManager::GetSDMpointer()->GetCollectionID(fHitCollection);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitCollection);
}

G4bool Optics_SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  Optics_Hit *newHit = new Optics_Hit;
  G4Track *track     = step->GetTrack();
  G4double energy    = track->GetKineticEnergy();
  G4double energyDep = step->GetTotalEnergyDeposit();
  // G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
  // G4cout << "Deposited energy: " << energyDep / MeV << " MeV" << G4endl;
  newHit->Fill(energyDep);
  fHitCollection->insert(newHit);
  return true;
}

void Optics_SensitiveDetector::EndOfEvent(G4HCofThisEvent *hce) {}
