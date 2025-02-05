#include "NaI_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
NaI_PrimaryGeneratorAction::NaI_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //Default we have setup geantino particles
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * MeV);
    
    
    // TODO : Add your desired particles
}

NaI_PrimaryGeneratorAction::~NaI_PrimaryGeneratorAction() {
    delete fParticleGun;
}

void NaI_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event
   
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
