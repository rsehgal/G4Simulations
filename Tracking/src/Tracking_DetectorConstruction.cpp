#include "Tracking_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "Tracking_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "string"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4SystemOfUnits.hh"
#include "Tracking_MagneticField.h"

G4bool Tracking_DetectorConstruction::fieldIsInitialized = false;

Tracking_DetectorConstruction::Tracking_DetectorConstruction() {}

Tracking_DetectorConstruction::~Tracking_DetectorConstruction() {}

G4VPhysicalVolume* Tracking_DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    //Modify the world volume dimension as required
    double worldXYZ = 2*m;
    G4Box* solidWorld = new G4Box("World", 0.5*worldXYZ, 0.5*worldXYZ, 0.5*worldXYZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);
    
    //TODO : Create your desired detectors here
    G4Material *layerMat = worldMat;    
    G4Box *layer = new G4Box("Layer", 10.*cm,10.*cm,0.5*mm);
    G4LogicalVolume *logicalLayer = new G4LogicalVolume(layer,layerMat,"LogicalLayer");
    
    G4bool checkOverlaps = true;

    for(unsigned int i = 0 ; i < 5 ; i++){
	double zpos = (i+1)*10.*cm;
 	G4String layerName = "PhysicalLayer_"+std::to_string(i);
	new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,zpos),logicalLayer,layerName,logicWorld,false,checkOverlaps);
    } 
        
    

    // Logic to Attach sensitive detector to a logical volume
    Tracking_SensitiveDetector* detector = new Tracking_SensitiveDetector("LayerSensitiveDetector","LayersHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    logicalLayer->SetSensitiveDetector(detector);

    //ConstructSDandField();

    return physWorld;
}

void Tracking_DetectorConstruction::ConstructSDandField() {
    //return;
    if (!fieldIsInitialized) {
        fieldIsInitialized = true;

        // Define a uniform magnetic field (1 Tesla along Z-axis)
        G4ThreeVector fieldValue = G4ThreeVector(0.0, 3.0 * tesla, 0.0);
        Tracking_MagneticField* magField = new Tracking_MagneticField(fieldValue);

        // Get the global field manager
        G4FieldManager* fieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
        
        // Set the field - Geant4 will automatically create a chord finder
        fieldManager->SetDetectorField(magField);
        fieldManager->CreateChordFinder(magField);
    }
}

