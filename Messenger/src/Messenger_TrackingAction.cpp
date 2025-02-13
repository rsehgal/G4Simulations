#include "Messenger_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

Messenger_TrackingAction::Messenger_TrackingAction()  {
}

Messenger_TrackingAction::~Messenger_TrackingAction() {}

void Messenger_TrackingAction::PreUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action begin....." << std::endl;
}

void Messenger_TrackingAction::PostUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action ends....." << std::endl;
}

