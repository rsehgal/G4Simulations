#include "PMT_SD.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "PMT_Hit.h"
#include "G4OpticalPhoton.hh"
#include "G4EventManager.hh"
#include "G4AnalysisManager.hh"
PMT_SD::PMT_SD(const G4String &name, const G4String &collName) : G4VSensitiveDetector(name), fPmtHitCollection(nullptr)
{
  collectionName.insert(collName);
}

PMT_SD::~PMT_SD() {}

void PMT_SD::Initialize(G4HCofThisEvent *hce)
{
  // std::cout << "Initialize of PMT_SD called..." << std::endl;
  fPmtHitCollection = new PmtHitCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID        = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fPmtHitCollection);
}

G4bool PMT_SD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  G4Track *track = step->GetTrack();
  // G4double energy = track->GetKineticEnergy();
  // G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;

  // std::cout << "Entered Process Hits of PMT_SD....." << std::endl;
  PMT_Hit *newHit = new PMT_Hit;
  // G4String particle = track->GetParticleDefinition()->GetParticleName();

  if (track->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
    // std::cout << "RAMAN Optical Photon detected in PMT...." << std::endl;
    newHit->FillTime(track->GetGlobalTime());
    track->SetTrackStatus(fStopAndKill);
  }
  fPmtHitCollection->insert(newHit);
  return true;
}

void PMT_SD::EndOfEvent(G4HCofThisEvent *hce)
{
  /*
    //Commented code kept for reference

    G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    G4AnalysisManager *analMan = G4AnalysisManager::Instance();
    if(fPmtHitCollection->entries() > 1){
      std::cout << "RAMAN : Event : " << eventID <<" has : " << fPmtHitCollection->entries() << " hits..." << std::endl;

      for(unsigned int i = 0 ; i < fPmtHitCollection->entries() ; i++){
        analMan->FillNtupleDColumn(1, 0, eventID);
      //std::cout << (*fPmtHitCollection)[i]->GetTime() << std::endl;
      analMan->FillNtupleDColumn(1, 1, (*fPmtHitCollection)[i]->GetTime());
          analMan->AddNtupleRow(1);
      }

    }
  */
}
