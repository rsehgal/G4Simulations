#ifndef NONSEGMENTED_RUNACTION_HH
#define NONSEGMENTED_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class NonSegmented_RunAction : public G4UserRunAction {
public:
    NonSegmented_RunAction();
    virtual ~NonSegmented_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
