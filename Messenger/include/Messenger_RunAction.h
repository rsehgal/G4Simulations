#ifndef MESSENGER_RUNACTION_HH
#define MESSENGER_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class Messenger_RunAction : public G4UserRunAction {
public:
    Messenger_RunAction();
    virtual ~Messenger_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
