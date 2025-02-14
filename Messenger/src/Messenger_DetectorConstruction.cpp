#include "Messenger_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "Messenger_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"
#include "G4VisAttributes.hh"
#include "sstream"
Messenger_DetectorConstruction::Messenger_DetectorConstruction(): fOverlapCheck(false),fWorldSize(1.*m)
{
  SetCommands();
}

Messenger_DetectorConstruction::~Messenger_DetectorConstruction() {}

G4VPhysicalVolume *Messenger_DetectorConstruction::Construct()
{
  std::cout <<"CONSTRUCT recalled as expected...." << std::endl;

  G4NistManager *nist  = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // Modify the world volume dimension as required
  G4Box *solidWorld            = new G4Box("World", 0.5 * fWorldSize, 0.5 * fWorldSize, 0.5 * fWorldSize);
  G4LogicalVolume *logicWorld  = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0,fOverlapCheck);

  G4Box *solidDetector            = new G4Box("Detector", 10*cm, 10*cm, 10*cm);
  G4LogicalVolume *logicDetector  = new G4LogicalVolume(solidDetector, worldMat, "LogicalDetector");
  G4VPhysicalVolume *physDetector = new G4PVPlacement(nullptr, G4ThreeVector(), logicDetector, "PhysicalDetector", logicWorld, false, 0,fOverlapCheck);

  // TODO : Create your desired detectors here

  // Logic to Attach sensitive detector to a logical volume
  // Messenger_SensitiveDetector* detector = new Messenger_SensitiveDetector("SensitiveDetector");
  // G4SDManager::GetSDMpointer()->AddNewDetector(detector);
  // logicWorld->SetSensitiveDetector(detector);

  return physWorld;
}

void Messenger_DetectorConstruction::SetCommands()
{

  fMessenger = new G4GenericMessenger(this, "/detector/", "Change Detector Parameters");
  fMessenger->DeclareProperty("setTargetVolume", fMessengerTarget, "Setting the target logicalVolume");
  fMessenger->DeclareProperty("setTargetVolumeColor", fMessengerTargetColor, "Setting the target logicalVolume");
  fMessenger->DeclareProperty("enableOverlapCheck",fOverlapCheck,"Enable overlap check in geometries");
  fMessenger->DeclareProperty("setWorldSize",fWorldSize,"Set the world size");
  //fMessenger->DeclareMethod("enableOverlapCheck",&Messenger_DetectorConstruction::EnableOverlapCheck,"Enable overlap check in geometries");
  fMessenger->DeclareMethod("setHalfLengthX", &Messenger_DetectorConstruction::SetXHalfLength, "Set X HalfLength");
  fMessenger->DeclareMethod("setHalfLengthY", &Messenger_DetectorConstruction::SetYHalfLength, "Set Y HalfLength");
  fMessenger->DeclareMethod("setHalfLengthZ", &Messenger_DetectorConstruction::SetZHalfLength, "Set Z HalfLength");
  fMessenger->DeclareMethod("setColor", &Messenger_DetectorConstruction::SetColor, "Set Color as R G B A");
}

void Messenger_DetectorConstruction::SetXHalfLength(double size)
{
  G4Box *box = static_cast<G4Box *>(G4LogicalVolumeStore::GetInstance()->GetVolume(fMessengerTarget)->GetSolid());
  box->SetXHalfLength(size);
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void Messenger_DetectorConstruction::SetYHalfLength(double size)
{
  G4Box *box = static_cast<G4Box *>(G4LogicalVolumeStore::GetInstance()->GetVolume(fMessengerTarget)->GetSolid());
  box->SetYHalfLength(size);
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void Messenger_DetectorConstruction::SetZHalfLength(double size)
{
  G4Box *box = static_cast<G4Box *>(G4LogicalVolumeStore::GetInstance()->GetVolume(fMessengerTarget)->GetSolid());
  box->SetZHalfLength(size);
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void Messenger_DetectorConstruction::SetColor()
{
  std::cout << "Color String : " << fMessengerTargetColor << std::endl;
  std::istringstream ss(fMessengerTargetColor);
  double r =0, g=0, b=0, a=0, forceSolid=0;
  ss >> r >> g >> b >> a >> forceSolid;

  std::cout << "COLOR components : " << r << " : " << g << " : " << b << " : "<< a << std::endl;
  G4VisAttributes *vis       = new G4VisAttributes(G4Color(r,g,b,a));
  vis->SetForceSolid(forceSolid);
  G4LogicalVolume *logVolume = G4LogicalVolumeStore::GetInstance()->GetVolume(fMessengerTarget);
  logVolume->SetVisAttributes(vis);
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void Messenger_DetectorConstruction::EnableOverlapCheck(G4bool overlapCheck){
   std::cout << "OVERLAP Checker Triggered : " << overlapCheck << std::endl;
   std::cout << "OverChecker : before : " << fOverlapCheck << std::endl;
   fOverlapCheck = overlapCheck;
   std::cout << "OverChecker : after : " << fOverlapCheck << std::endl;
   G4RunManager::GetRunManager()->ReinitializeGeometry();
}
