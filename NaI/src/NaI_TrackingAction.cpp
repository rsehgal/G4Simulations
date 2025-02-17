#include "NaI_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrackingManager.hh"

NaI_TrackingAction::NaI_TrackingAction()  {
}

NaI_TrackingAction::~NaI_TrackingAction() {}

void NaI_TrackingAction::PreUserTrackingAction(const G4Track *track){
//std::cout <<"Tracking Action begin....." << std::endl;
//fpTrackingManager->SetStoreTrajectory(1);
if(fpTrackingManager->GetStoreTrajectory()){
std::cout << "SHACHI : Trajectory store flag set...."<<std::endl;
}

if(fpTrackingManager->GimmeTrajectory()){
std::cout << "SEHGAL : Trajectory found from PreAction..." << std::endl; 
}
}

void NaI_TrackingAction::PostUserTrackingAction(const G4Track *track){
if(fpTrackingManager->GimmeTrajectory()){
std::cout << "SEHGAL : Trajectory found from PostAction..." << std::endl; 
}

//std::cout <<"Tracking Action ends....." << std::endl;
}

