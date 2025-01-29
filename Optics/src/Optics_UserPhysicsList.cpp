#include "Optics_UserPhysicsList.h"
// Particles
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OpticalPhoton.hh"
// Processes
//For Gamma
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"

//For Electron and position
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
//Process manager
#include "G4ProcessManager.hh"

#include "G4SystemOfUnits.hh"

Optics_UserPhysicsList::Optics_UserPhysicsList() {}

Optics_UserPhysicsList::~Optics_UserPhysicsList() {}

void Optics_UserPhysicsList::ConstructParticle()
{
  // std::cout <<"RAMAN : Construct Particle....." << std::endl;
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void Optics_UserPhysicsList::ConstructProcess()
{
  // std::cout <<"SEHGAL : Construct Process....." << std::endl;
  AddTransportation();

  G4ProcessManager *processManager = nullptr;

  //For Gamma
  processManager = G4Gamma::Gamma()->GetProcessManager();
  processManager->AddDiscreteProcess(new G4PhotoElectricEffect());
  processManager->AddDiscreteProcess(new G4ComptonScattering());
  processManager->AddDiscreteProcess(new G4GammaConversion());
  processManager->AddDiscreteProcess(new G4RayleighScattering());

  //For Electron
  processManager = G4Electron::Electron()->GetProcessManager();
  processManager->AddProcess(new G4eIonisation());
  processManager->AddProcess(new G4eBremsstrahlung());

  //For Position
  processManager = G4Positron::Positron()->GetProcessManager();
  processManager->AddProcess(new G4eIonisation());
  processManager->AddProcess(new G4eBremsstrahlung());

}

void Optics_UserPhysicsList::SetCuts() {
    G4double cutValue = 0.05 * mm;  // Define a global cut value

    // Apply cut values for different particles
    SetCutValue(cutValue, "gamma");    // Cut for gamma
    SetCutValue(cutValue, "e-");       // Cut for electrons
    SetCutValue(cutValue, "e+");       // Cut for positrons

    // Print cut values (optional)
    G4cout << "CUTT : Cut values set to " << cutValue / mm << " mm for gamma, e-, e+" << G4endl;
}
