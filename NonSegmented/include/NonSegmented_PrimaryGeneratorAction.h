#ifndef NONSEGMENTED_PRIMARYGENERATORACTION_HH
#define NONSEGMENTED_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class NonSegmented_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    NonSegmented_PrimaryGeneratorAction();
    virtual ~NonSegmented_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
