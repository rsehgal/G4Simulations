#ifndef OPTICS_PRIMARYGENERATORACTION_HH
#define OPTICS_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class Optics_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    Optics_PrimaryGeneratorAction();
    virtual ~Optics_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
