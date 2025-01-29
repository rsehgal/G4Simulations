#ifndef OPTICS_USERPHYSICSLIST_HH
#define OPTICS_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class Optics_UserPhysicsList : public G4VUserPhysicsList {
public:
    Optics_UserPhysicsList();
    virtual ~Optics_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess();
    virtual void SetCuts(); 
};

#endif
