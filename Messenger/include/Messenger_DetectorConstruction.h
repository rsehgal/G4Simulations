#ifndef MESSENGER_DETECTORCONSTRUCTION_HH
#define MESSENGER_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Color.hh"

class G4GenericMessenger;

class Messenger_DetectorConstruction : public G4VUserDetectorConstruction {

    G4GenericMessenger *fMessenger;
    G4String fMessengerTarget;
    G4String fMessengerTargetColor;
    G4bool fOverlapCheck;
    double fWorldSize;

public:
    Messenger_DetectorConstruction();
    virtual ~Messenger_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    //Messenger functions
    void SetCommands();
    void SetXHalfLength(double size);
    void SetYHalfLength(double size);
    void SetZHalfLength(double size);
    void EnableOverlapCheck(G4bool overlapCheck);
    void SetColor();
};

#endif
