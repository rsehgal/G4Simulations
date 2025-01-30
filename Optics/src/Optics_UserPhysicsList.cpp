#include "Optics_UserPhysicsList.h"
// Particles
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OpticalPhoton.hh"
// Processes
// For Gamma
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"

// For Electron and Positron
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh" // Added for positrons

// Process manager
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"

Optics_UserPhysicsList::Optics_UserPhysicsList() {}
Optics_UserPhysicsList::~Optics_UserPhysicsList() {}

void Optics_UserPhysicsList::ConstructParticle()
{
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void Optics_UserPhysicsList::ConstructProcess()
{
  AddTransportation();

  G4ProcessManager *processManager = nullptr;

  // For Gamma
  processManager = G4Gamma::Gamma()->GetProcessManager();
  processManager->AddDiscreteProcess(new G4PhotoElectricEffect()); // Needed for 662 keV peak
  processManager->AddDiscreteProcess(new G4ComptonScattering());   // Compton scattering
  processManager->AddDiscreteProcess(new G4GammaConversion());     // Pair production (above 1.022 MeV)
  processManager->AddDiscreteProcess(new G4RayleighScattering());  // Optional but improves low-energy interactions

  // For Electron
  processManager = G4Electron::Electron()->GetProcessManager();
  processManager->AddProcess(new G4eIonisation(), -1, 1, 1);
  processManager->AddProcess(new G4eBremsstrahlung(), -1, 2, 2);

  // For Positron
  processManager = G4Positron::Positron()->GetProcessManager();
  processManager->AddProcess(new G4eIonisation(), -1, 1, 1);
  processManager->AddProcess(new G4eBremsstrahlung(), -1, 2, 2);
  processManager->AddProcess(new G4eplusAnnihilation(), 0, -1, 3); // Fix: Added positron annihilation
}

void Optics_UserPhysicsList::SetCuts()
{
  G4double cutValue = 0.005 * mm; // Reduced cut for better secondary tracking

  SetCutValue(cutValue, "gamma"); // Cut for gamma
  SetCutValue(cutValue, "e-");    // Cut for electrons
  SetCutValue(cutValue, "e+");    // Cut for positrons

  G4cout << "CUTT : Cut values set to " << cutValue / mm << " mm for gamma, e-, e+" << G4endl;
}
