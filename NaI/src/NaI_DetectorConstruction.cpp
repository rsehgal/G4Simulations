#include "NaI_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "NaI_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

NaI_DetectorConstruction::NaI_DetectorConstruction() {}

NaI_DetectorConstruction::~NaI_DetectorConstruction() {}

G4VPhysicalVolume *NaI_DetectorConstruction::Construct()
{
  G4NistManager *nist  = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // Modify the world volume dimension as required
  G4Box *solidWorld            = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld  = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  // TODO : Create your desired detectors here
  double crystalDia = 5.7 * cm;
  double crystalHeight = 5.3 * cm;
  G4Material *naiMaterial = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4Tubs *naiCrystal   = new G4Tubs("NaiCrystal", 0., crystalDia/2., crystalHeight / 2., 0, 2 * M_PI);
  G4LogicalVolume *logicalNaiCrystal = new G4LogicalVolume(naiCrystal,naiMaterial,"LogicalNaiCrystal");
  new G4PVPlacement(nullptr,G4ThreeVector(),logicalNaiCrystal,"PhysicalNaiCrystal",logicWorld,false,true);

  // Logic to Attach sensitive detector to a logical volume
  // NaI_SensitiveDetector* detector = new NaI_SensitiveDetector("SensitiveDetector");
  // G4SDManager::GetSDMpointer()->AddNewDetector(detector);
  // logicWorld->SetSensitiveDetector(detector);

  NaI_SensitiveDetector *naiSD = new NaI_SensitiveDetector("SodiumIodide");
  G4SDManager::GetSDMpointer()->AddNewDetector(naiSD);
  logicalNaiCrystal->SetSensitiveDetector(naiSD);
  
  return physWorld;
}
