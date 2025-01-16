#ifndef OPTICS_STEPPINGACTION_HH
#define OPTICS_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class Optics_SteppingAction : public G4UserSteppingAction {
public:
    Optics_SteppingAction();
    virtual ~Optics_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
