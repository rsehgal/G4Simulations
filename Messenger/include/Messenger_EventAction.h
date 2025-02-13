#ifndef MESSENGER_EVENTACTION_HH
#define MESSENGER_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class Messenger_EventAction : public G4UserEventAction {
public:
    Messenger_EventAction();
    virtual ~Messenger_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
