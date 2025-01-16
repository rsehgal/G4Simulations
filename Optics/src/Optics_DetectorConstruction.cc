#include "Optics_DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "Optics_SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VisAttributes.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"

// Sensitive detector class
#include "PMT_SD.h"

Optics_DetectorConstruction::Optics_DetectorConstruction() {}

Optics_DetectorConstruction::~Optics_DetectorConstruction() {}

G4VPhysicalVolume *Optics_DetectorConstruction::Construct()
{

  // return ConstructNaIDetector();

  G4NistManager *nist  = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  G4Material *nai = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

  double crystalRadius = 1.27 * cm;
  double crystalHeight = 2 * 1.27 * cm;

  G4Box *solidWorld            = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld  = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  G4Tubs *crystal                 = new G4Tubs("NaI", 0, crystalRadius, crystalHeight / 2., 0., 2 * M_PI);
  G4LogicalVolume *logicalCrystal = new G4LogicalVolume(crystal, nai, "LogicalCrystal");
  G4VPhysicalVolume *physCrystal =
      new G4PVPlacement(nullptr, G4ThreeVector(), logicalCrystal, "PhysicalCrystal", logicWorld, false, 1);

  // Trying to add optical properties,
  // Change them based on the data sheet of your detector

// Energy array (photon energies) in eV

auto myMPT1 = new G4MaterialPropertiesTable();

// Photon energy array (in eV)
const G4int nEntries = 2;
G4double photonEnergy[nEntries] = {2.95 * eV, 3.26 * eV};  // 415 nm to 380 nm

// Refractive index for NaI(Tl)
G4double refractiveIndex[nEntries] = {1.85, 1.85};
myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);

// Absorption length (in mm)
G4double absorptionLength[nEntries] = {2600. * mm, 2600. * mm};
myMPT1->AddProperty("ABSLENGTH", photonEnergy, absorptionLength, nEntries);

// Emission spectrum for fast and slow components
G4double scintilFast[nEntries] = {0.1, 0.1};
G4double scintilSlow[nEntries] = {0.9, 0.9};
myMPT1->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintilFast, nEntries);
myMPT1->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintilSlow, nEntries);

// Set scintillation yield and time constants
myMPT1->AddConstProperty("SCINTILLATIONYIELD", 38000. / MeV);
myMPT1->AddConstProperty("RESOLUTIONSCALE", 1.0);
myMPT1->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250. * ns);
myMPT1->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 1.6 * us);
myMPT1->AddConstProperty("SCINTILLATIONYIELD1", 0.1);
myMPT1->AddConstProperty("SCINTILLATIONYIELD2", 0.9);
// Attach the material properties table to the NaI(Tl) material
nai->SetMaterialPropertiesTable(myMPT1);
//  nai->SetMaterialPropertiesTable(NaIMPT);

  G4Material *pmtMaterial = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
  G4double pmtRadius      = crystalRadius;
  G4double pmtThickness   = 1.0 * mm;

  G4double glassRefractiveIndex[nEntries] = {1.50, 1.52};
  G4MaterialPropertiesTable *mptGlass     = new G4MaterialPropertiesTable();
  mptGlass->AddProperty("RINDEX", photonEnergy, glassRefractiveIndex, nEntries);
  pmtMaterial->SetMaterialPropertiesTable(mptGlass);

  G4Tubs *solidPMT           = new G4Tubs("PMT", 0, pmtRadius, pmtThickness / 2, 0, 360 * deg);
  G4LogicalVolume *logicPMT  = new G4LogicalVolume(solidPMT, pmtMaterial, "LogicalPMT");
  G4VPhysicalVolume *physPMT = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, crystalHeight / 2 + pmtThickness / 2),
                                                 logicPMT, "PhysicalPMT", logicWorld, false, 0);

  AddOpticalProperties();

  Optics_SensitiveDetector *naiSD = new Optics_SensitiveDetector("SensitiveNai", "NaiHits");
  G4SDManager::GetSDMpointer()->AddNewDetector(naiSD);
  logicalCrystal->SetSensitiveDetector(naiSD);


  PMT_SD *pmtSD = new PMT_SD("SensitivePMT", "pmtCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(pmtSD);
  logicPMT->SetSensitiveDetector(pmtSD);


  G4MaterialPropertiesTable *worldMPT   = new G4MaterialPropertiesTable();
  G4double refractiveIndexAir[nEntries] = {1.00, 1.00};
  worldMPT->AddProperty("RINDEX", photonEnergy, refractiveIndexAir, nEntries);
  worldMat->SetMaterialPropertiesTable(worldMPT);

  return physWorld;
}

G4VPhysicalVolume* Optics_DetectorConstruction::GetPhysicalVolumeByName(const G4String& name) {
    G4PhysicalVolumeStore* pvStore = G4PhysicalVolumeStore::GetInstance();
    for (auto pv : *pvStore) {
        if (pv->GetName() == name) {
            return pv;
        }
    }
    G4cerr << "Error: Physical volume with name " << name << " not found!" << G4endl;
    return nullptr;
}

void Optics_DetectorConstruction::AddOpticalProperties()
{
  // Define optical surface between NaI crystal and PMT
  G4OpticalSurface *opticalSurface = new G4OpticalSurface("OpticalSurface");
  opticalSurface->SetType(dielectric_dielectric);
  opticalSurface->SetFinish(polished);
  opticalSurface->SetModel(unified);

  // Apply the surface to the PMT
  //new G4LogicalSkinSurface("CrystalSurface", G4LogicalVolumeStore::GetInstance()->GetVolume("LogicalCrystal"),
    //                       opticalSurface);

  G4LogicalBorderSurface *surface = new G4LogicalBorderSurface("NaIToPMTSurface", GetPhysicalVolumeByName("PhysicalCrystal"), GetPhysicalVolumeByName("PhysicalPMT"), opticalSurface);
}
