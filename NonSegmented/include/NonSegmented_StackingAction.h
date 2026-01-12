/*
**	Filename : NonSegmented_StackingAction.h
**	2026-01-12
**	username : rsehgal
*/
#ifndef NonSegmented_StackingAction_h
#define NonSegmented_StackingAction_h

#include "G4ClassificationOfNewTrack.hh"

class G4UserStackingAction;

class NonSegmented_StackingAction:public G4UserStackingAction
{

public:
  NonSegmented_StackingAction();
  ~NonSegmented_StackingAction();
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *track);
};

#endif
