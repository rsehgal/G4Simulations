#ifndef MESSENGER_SENSITIVEDETECTOR_HIT_HH
#define MESSENGER_SENSITIVEDETECTOR_HIT_HH

#include "G4VHit.hh"

class Messenger_SensitiveDetector_Hit : public G4VHit {
public:
    Messenger_SensitiveDetector_Hit();
    virtual ~Messenger_SensitiveDetector_Hit();
};

#endif
