#include "NaI_SensitiveDetector.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4AnalysisManager.hh"
#include "G4RandomTools.hh"
#include "G4EventManager.hh"
NaI_SensitiveDetector::NaI_SensitiveDetector(const G4String &name) : G4VSensitiveDetector(name), fEDep(0) {}

NaI_SensitiveDetector::~NaI_SensitiveDetector() {}

void NaI_SensitiveDetector::Initialize(G4HCofThisEvent *hce)
{
  fEDep = 0;
}

G4bool NaI_SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  G4Track *track  = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  // G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
  fEDep += step->GetTotalEnergyDeposit();
  // TODO :  Add Whatall information you want to get from steps
  return true;
}

void NaI_SensitiveDetector::EndOfEvent(G4HCofThisEvent *hce)
{
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  if(!(eventID % 100000) && eventID !=0)
	std::cout << eventID << " events processed....." << std::endl;
  if (fEDep > 0.) {
    analMan->FillNtupleDColumn(0,0, fEDep*1000.);
    analMan->FillNtupleDColumn(0,1, G4RandGauss::shoot(fEDep,0.04385)*1000.);
    analMan->AddNtupleRow(0);
  }
}
