#ifndef OPTICS_TRACKINGACTION_HH
#define OPTICS_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class Optics_TrackingAction : public G4UserTrackingAction {
public:
    Optics_TrackingAction();
    virtual ~Optics_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
