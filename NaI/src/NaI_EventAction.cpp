#include "NaI_EventAction.h"
#include "G4EventManager.hh"

NaI_EventAction::NaI_EventAction()  {
}

NaI_EventAction::~NaI_EventAction() {}

void NaI_EventAction::BeginOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the start
    //       of each event
    G4Track *track = G4EventManager::GetEventManager()->GetTrackingManager()->GetTrack();
    if(track){
	//std::cout << "RAMAN : Track exist in BeginOfEventAction ....." << std::endl;
   }
}

void NaI_EventAction::EndOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the end
    //       of each event
    G4Track *track = G4EventManager::GetEventManager()->GetTrackingManager()->GetTrack();
    if(track){
	//std::cout << "SEHGAL : Track exist in EndOfEventAction ....." << std::endl;
   }

}

