#ifndef MESSENGER_SENSITIVEDETECTOR_HH
#define MESSENGER_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class Messenger_SensitiveDetector : public G4VSensitiveDetector {
public:
    Messenger_SensitiveDetector(const G4String& name);
    virtual ~Messenger_SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
