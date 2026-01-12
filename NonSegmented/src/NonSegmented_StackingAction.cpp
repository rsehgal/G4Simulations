/*
**	Filename : NonSegmented_StackingAction.cpp
**	2026-01-12
**	username : rsehgal
*/
#include "G4UserStackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "NonSegmented_StackingAction.h"
#include "G4Track.hh"
NonSegmented_StackingAction::NonSegmented_StackingAction() {}

NonSegmented_StackingAction::~NonSegmented_StackingAction() {}

G4ClassificationOfNewTrack NonSegmented_StackingAction::ClassifyNewTrack(const G4Track *track)
{
  //std::cout << "StackingAction CAlled..........." << std::endl;
  if (track->GetParentID() == 1) {
    G4Track *theTrack = const_cast<G4Track *>(track);
    theTrack->SetGlobalTime(0.0);
  }
  return fUrgent;
}
