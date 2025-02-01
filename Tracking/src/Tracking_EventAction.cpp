#include "Tracking_EventAction.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "HitsCollections.h"
#include "Tracking_SensitiveDetector_Hit.h"
#include "G4AnalysisManager.hh"
#include "G4EventManager.hh"

Tracking_EventAction::Tracking_EventAction()  {
}

Tracking_EventAction::~Tracking_EventAction() {}

void Tracking_EventAction::BeginOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the start
    //       of each event
}

void Tracking_EventAction::EndOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the end
    //       of each event
    std::cout <<"====== Info from EndOfEventAction =====" << std::endl;
    G4HCofThisEvent *hce = event->GetHCofThisEvent();
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID("LayersHitsCollection");
    LayersHitsCollection *layersHitsCollection = static_cast<LayersHitsCollection*>(hce->GetHC(hcID));

    G4int collSize = layersHitsCollection->entries();

    G4AnalysisManager *analMan = G4AnalysisManager::Instance();    
    
    G4int eventNo = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID(); 
    for(unsigned int i = 0 ; i < collSize ; i++){
        Tracking_SensitiveDetector_Hit *hit = (*layersHitsCollection)[i];
	hit->Print();
	analMan->FillNtupleDColumn(0,0,hit->GetPosition().x());
	analMan->FillNtupleDColumn(0,1,hit->GetPosition().y());
	analMan->FillNtupleDColumn(0,2,hit->GetPosition().z());
 
        analMan->FillNtupleDColumn(0,3,hit->GetMomentumDirection().x());
	analMan->FillNtupleDColumn(0,4,hit->GetMomentumDirection().y());
	analMan->FillNtupleDColumn(0,5,hit->GetMomentumDirection().z());

	analMan->FillNtupleDColumn(0,6,eventNo);
        analMan->AddNtupleRow(0);
    } 
    std::cout <<"=======================================" << std::endl;
}

