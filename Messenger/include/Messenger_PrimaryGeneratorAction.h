#ifndef MESSENGER_PRIMARYGENERATORACTION_HH
#define MESSENGER_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class Messenger_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    Messenger_PrimaryGeneratorAction();
    virtual ~Messenger_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
