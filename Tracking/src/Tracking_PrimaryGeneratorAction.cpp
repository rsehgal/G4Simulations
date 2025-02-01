#include "Tracking_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
Tracking_PrimaryGeneratorAction::Tracking_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //Default we have setup geantino particles
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * GeV);
    
    
    // TODO : Add your desired particles
}

Tracking_PrimaryGeneratorAction::~Tracking_PrimaryGeneratorAction() {
    delete fParticleGun;
}

void Tracking_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event
   
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
