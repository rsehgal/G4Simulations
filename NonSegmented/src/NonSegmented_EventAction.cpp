#include "NonSegmented_EventAction.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "NonSegmented_HitCollections.h"
#include "NonSegmented_PMT_Hit.h"
#include "NonSegmented_Slab_Hit.h"
#include "G4AnalysisManager.hh"
#include "Helpers.h"

NonSegmented_EventAction::NonSegmented_EventAction() {}

NonSegmented_EventAction::~NonSegmented_EventAction() {}

void NonSegmented_EventAction::BeginOfEventAction(const G4Event *event)
{
  // TODO : All the required logic you want to do at the start
  //        of each event
}

void NonSegmented_EventAction::EndOfEventAction(const G4Event *event)
{
  // TODO : All the required logic you want to do at the end
  //        of each event

  std::cout << "======================================" << std::endl;
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();

  G4HCofThisEvent *hce = event->GetHCofThisEvent();
  G4int hcID_PMT       = G4SDManager::GetSDMpointer()->GetCollectionID("PMT");
  G4int hcID_Slab      = G4SDManager::GetSDMpointer()->GetCollectionID("Slab");
  // std::cout << hcID_PMT <<" : " << hcID_Slab << std::endl;

  PMT_HitCollection *pmtHitCollection   = static_cast<PMT_HitCollection *>(hce->GetHC(hcID_PMT));
  Slab_HitCollection *slabHitCollection = static_cast<Slab_HitCollection *>(hce->GetHC(hcID_Slab));

  if (pmtHitCollection && slabHitCollection) {
    // std::cout << "Genuine hit collection found...." << std::endl;

    std::vector<std::vector<double>> vecOfPhotonArrivalTime(4);
    unsigned int entries = pmtHitCollection->entries();
    // std::cout << "Entries : " << entries << std::endl;
    for (unsigned int i = 0; i < entries; i++) {
      NonSegmented_PMT_Hit *hit = (*pmtHitCollection)[i];
      //hit->Print();
      vecOfPhotonArrivalTime[hit->GetPmtID() - 1].push_back(hit->GetPhotonArrivalTime());
    }

    bool detectedByAll = true;
    for (unsigned int i = 0; i < vecOfPhotonArrivalTime.size(); i++) {
      detectedByAll &= vecOfPhotonArrivalTime[i].size() > 0;
    }
    if (detectedByAll) {
      double timing0 = GetTiming(vecOfPhotonArrivalTime[0]);
      for (unsigned int i = 1; i < vecOfPhotonArrivalTime.size(); i++) {
        analMan->FillNtupleDColumn(1, i - 1, timing0 - GetTiming(vecOfPhotonArrivalTime[i]));
      }

      // Get Hit point on Slab, currently taking the hit point on top surface
      NonSegmented_Slab_Hit *slabHit = (*slabHitCollection)[0];
      slabHit->Print();
      analMan->FillNtupleDColumn(1, 3, slabHit->GetX());
      analMan->FillNtupleDColumn(1, 4, slabHit->GetZ());
      analMan->AddNtupleRow(1);
    }
  } else {
    // std::cout << "Required Hit Collection NOT found...." << std::endl;
  }
}
