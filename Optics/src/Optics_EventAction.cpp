/*
**	Filename : Optics_EventAction.cpp
**	2025-01-15
**	username : rsehgal
*/

#include "Optics_EventAction.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "Optics_Hit.h"
#include "HitCollections.h"
#include "G4EventManager.hh"
#include "G4AnalysisManager.hh"
#include "CLHEP/Random/RandGauss.h"
Optics_EventAction::Optics_EventAction() {}
Optics_EventAction::~Optics_EventAction() {}

void Optics_EventAction::BeginOfEventAction(const G4Event *event)
{
  // std::cout << "@@@@@@@@@@@ EVENT BEGUN..... @@@@@@@@" << std::endl;
}

void Optics_EventAction::EndOfEventAction(const G4Event *event)
{
  //  return;

  G4HCofThisEvent *hce               = event->GetHCofThisEvent();
  G4int pmtHCID                      = G4SDManager::GetSDMpointer()->GetCollectionID("pmtCollection");
  G4int naiHCID                      = G4SDManager::GetSDMpointer()->GetCollectionID("NaiHits");
  NaiHitCollection *naiHitCollection = static_cast<NaiHitCollection *>(hce->GetHC(naiHCID));
  PmtHitCollection *pmtHitCollection = static_cast<PmtHitCollection *>(hce->GetHC(pmtHCID));

  G4int eventId              = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();

  double totalEnergyDeposited = 0;
  for (unsigned int i = 0; i < naiHitCollection->entries(); i++) {
    totalEnergyDeposited += (*naiHitCollection)[i]->GetEnergy();
  }

  double sigma = 0.040;
  //if (pmtHitCollection->entries() > 1 && totalEnergyDeposited > 0.) 
  {
    analMan->FillNtupleDColumn(0, 0, eventId);
    analMan->FillNtupleDColumn(0, 1, totalEnergyDeposited);
    analMan->FillNtupleDColumn(0, 2, CLHEP::RandGauss::shoot(totalEnergyDeposited,sigma));
    analMan->FillNtupleDColumn(0, 3, pmtHitCollection->entries());
    analMan->AddNtupleRow(0);
  }

  //if (pmtHitCollection->entries() > 1 && totalEnergyDeposited > 0.) 
    {
    for (unsigned int i = 0; i < pmtHitCollection->entries(); i++) {
      analMan->FillNtupleDColumn(1, 0, eventId);
      analMan->FillNtupleDColumn(1, 1, (*pmtHitCollection)[i]->GetTime());
      analMan->AddNtupleRow(1);
    }
    if(!(eventId % 1000) && eventId>0)
    std::cout << "FROM EVENTACTION : Event No : "<< eventId << " : Number of photons detected : " << pmtHitCollection->entries() << std::endl;
  }
}
