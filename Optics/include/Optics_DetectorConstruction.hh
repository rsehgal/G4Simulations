#ifndef OPTICS_DETECTORCONSTRUCTION_HH
#define OPTICS_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

class Optics_DetectorConstruction : public G4VUserDetectorConstruction {
public:
  Optics_DetectorConstruction();
  virtual ~Optics_DetectorConstruction();

  virtual G4VPhysicalVolume *Construct();

  G4VPhysicalVolume *ConstructNaIDetector();

private:
  void AddOpticalProperties();
  G4VPhysicalVolume* GetPhysicalVolumeByName(const G4String& name);
};

#endif
