#include "Optics_ModularPhysicsList.h"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
Optics_ModularPhysicsList::Optics_ModularPhysicsList()
{
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
}

Optics_ModularPhysicsList::~Optics_ModularPhysicsList() {}
