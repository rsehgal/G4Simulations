#include "NonSegmented_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
#include "CLHEP/Random/RandFlat.h"


NonSegmented_PrimaryGeneratorAction::NonSegmented_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //Default we have setup geantino particles
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * MeV);
    
    
    // TODO : Add your desired particles
}

NonSegmented_PrimaryGeneratorAction::~NonSegmented_PrimaryGeneratorAction() {
    delete fParticleGun;
}


void NonSegmented_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event

  double ypos = 500;
#define RANDOM_POS
#ifdef RANDOM_POS
  //double randX1 = CLHEP::RandFlat::shoot(-250.,250.);
  //double randZ1 = CLHEP::RandFlat::shoot(-250.,250.);

  double randX1 = CLHEP::RandFlat::shoot(-30.,30.);
  double randZ1 = CLHEP::RandFlat::shoot(-30.,30.);

  fParticleGun->SetParticlePosition(G4ThreeVector(randX1,ypos,randZ1));
#endif
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
