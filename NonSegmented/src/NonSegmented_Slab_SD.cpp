#include "NonSegmented_Slab_SD.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"
#include "NonSegmented_Slab_Hit.h"
NonSegmented_Slab_SD::NonSegmented_Slab_SD(const G4String &name, const G4String &collName) : G4VSensitiveDetector(name)
{
  collectionName.insert(collName);
}

NonSegmented_Slab_SD::~NonSegmented_Slab_SD() {}

void NonSegmented_Slab_SD::Initialize(G4HCofThisEvent *hce)
{
  fSlabHitCollection = new Slab_HitCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcId         = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcId, fSlabHitCollection);
}

G4bool NonSegmented_Slab_SD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  G4StepPoint *postStepPoint = step->GetPostStepPoint();
  G4Track *track             = step->GetTrack();
  G4double energy            = track->GetKineticEnergy();
  // G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
  NonSegmented_Slab_Hit *hit = new NonSegmented_Slab_Hit;

  if (track->GetTrackID() == 1) {
    if (postStepPoint->GetStepStatus() == fGeomBoundary) {
      // std::cout << postStepPoint->GetPosition() << std::endl;
      hit->Set(postStepPoint->GetPosition().x(), postStepPoint->GetPosition().z());
      fSlabHitCollection->insert(hit);
    }
  }

  return true;
}

void NonSegmented_Slab_SD::EndOfEvent(G4HCofThisEvent *hce)
{
  /*unsigned int entries = fSlabHitCollection->entries();

  for (unsigned int i = 0; i < entries; i++) {
    (*fSlabHitCollection)[i]->Print();
  }*/
}
