#ifndef MESSENGER_STEPPINGACTION_HH
#define MESSENGER_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class Messenger_SteppingAction : public G4UserSteppingAction {
public:
    Messenger_SteppingAction();
    virtual ~Messenger_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
