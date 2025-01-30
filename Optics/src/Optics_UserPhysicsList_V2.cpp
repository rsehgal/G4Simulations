#include "Optics_UserPhysicsList_V2.h"
//Particles
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4OpticalPhoton.hh"

//Processes for Gamma
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"

//Processes for Electron and positron
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

//Physics List Helper
#include "G4PhysicsListHelper.hh"

Optics_UserPhysicsList_V2::Optics_UserPhysicsList_V2() {}

Optics_UserPhysicsList_V2::~Optics_UserPhysicsList_V2() {}

void Optics_UserPhysicsList_V2::ConstructParticle()
{
  // std::cout <<"RAMAN : Construct Particle....." << std::endl;
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void Optics_UserPhysicsList_V2::ConstructProcess()
{
  // std::cout <<"SEHGAL : Construct Process....." << std::endl;

  AddTransportation(); // Mandatory

  G4PhysicsListHelper *ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // 🔹 Gamma processes (Discrete, no ordering needed)
  ph->RegisterProcess(new G4PhotoElectricEffect(), G4Gamma::GammaDefinition());
  ph->RegisterProcess(new G4ComptonScattering(), G4Gamma::GammaDefinition());
  ph->RegisterProcess(new G4GammaConversion(), G4Gamma::GammaDefinition());
  ph->RegisterProcess(new G4RayleighScattering(), G4Gamma::GammaDefinition());

  // 🔹 Electron processes (Automatically ordered)
  ph->RegisterProcess(new G4eIonisation(), G4Electron::ElectronDefinition());
  ph->RegisterProcess(new G4eBremsstrahlung(), G4Electron::ElectronDefinition());

  // 🔹 Positron processes (Automatically ordered)
  ph->RegisterProcess(new G4eIonisation(), G4Positron::PositronDefinition());
  ph->RegisterProcess(new G4eBremsstrahlung(), G4Positron::PositronDefinition());
  ph->RegisterProcess(new G4eplusAnnihilation(), G4Positron::PositronDefinition()); // 🔹 No need for manual ordering!
}
