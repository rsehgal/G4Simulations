#include "NonSegmented_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

NonSegmented_TrackingAction::NonSegmented_TrackingAction()  {
}

NonSegmented_TrackingAction::~NonSegmented_TrackingAction() {}

void NonSegmented_TrackingAction::PreUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action begin....." << std::endl;
}

void NonSegmented_TrackingAction::PostUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action ends....." << std::endl;
}

