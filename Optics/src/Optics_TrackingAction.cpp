#include "Optics_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrackVector.hh"
#include "G4TrackingManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4AnalysisManager.hh"
Optics_TrackingAction::Optics_TrackingAction() {}

Optics_TrackingAction::~Optics_TrackingAction() {}

void Optics_TrackingAction::PreUserTrackingAction(const G4Track *track)
{
  if (track->GetTrackID() == 1) {
    // std::cout << "RAMAN : Tracking Action begin....." << std::endl;
  }
}

void Optics_TrackingAction::PostUserTrackingAction(const G4Track *track)
{
  if (track->GetTrackID() == 1) {
    // std::cout << "SEHGAL : Tracking Action ends....." << std::endl;
    // G4TrackVector *vecOfTrack
    const auto *secondaries = fpTrackingManager->GimmeSecondaries();
    int photonCount         = 0;
    if (secondaries) {

    for (unsigned int i = 0; i < secondaries->size(); i++) {
        if ((*secondaries)[i]->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
          photonCount++;
        }
      }
      // std::cout << "No of Photons Generated : " << secondaries->size() << std::endl;
      std::cout << "No of Photons Generated : " << photonCount << std::endl;
    }
    G4AnalysisManager::Instance()->FillNtupleDColumn(0,4,photonCount);
  }
}
