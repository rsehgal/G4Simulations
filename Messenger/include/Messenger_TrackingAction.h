#ifndef MESSENGER_TRACKINGACTION_HH
#define MESSENGER_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class Messenger_TrackingAction : public G4UserTrackingAction {
public:
    Messenger_TrackingAction();
    virtual ~Messenger_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
